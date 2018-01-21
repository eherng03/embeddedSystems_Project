#include <DHT11.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

//ConfiguraciÃ³n de la red wifi y el host donde estÃ¡ el servidor
const char* ssid = "rasp";
const char* password = "raspberry";
const char* host = "192.168.43.247";

Servo servoMotor;
const int LED = 16;
int SmokePin = 5;
int PresencePin = 4;
int Zumbador = 14;

void setup() {

  pinMode(SmokePin, INPUT);
  pinMode(LED, OUTPUT);
  servoMotor.attach(2);
  pinMode(PresencePin, INPUT);
  pinMode(Zumbador, OUTPUT);

  Serial.begin(115200);
  Serial.print("Conectando a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi conectado");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}


void loop()
{
  int err;
  int status;
  String place = "garage";
  int statePresencia;
  int stateSmoke;
  Serial.print("conectando a: ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Coneccion Fallida");
    return;
  }

  String urlDoor = "/IntelliHome/operations/getDoorStatus.php?place=garage";
  String urlLight = "/IntelliHome/operations/getLightStatus.php?place=garage";
  String urlPresence = "/IntelliHome/operations/changePresence.php?";
  String urlSmoke = "/IntelliHome/operations/changeSmoke.php?";

  String datoPresence = "state=";
  String datoPlace = "&place=";
  String datoSmoke = "state=";


//Luz

  Serial.print("Obteniendo URL: ");
  Serial.println(urlLight);
  //Creamos la peticion al servidor
  client.println(String("GET ") + urlLight);

  unsigned long timeout1 = millis();
  while (client.available() == 0) {
    if (millis() - timeout1 > 5000) {
      Serial.println(">>> Se acabo el tiempo de espera luz !");
      client.stop();
      return;
    }
  }

  //Imprimimos lo que nos devuelve el servidor
  while (client.available()) {
    int stat1 = client.read();  //En stat guardamos lo que nos devuelve la llamada a la bbdd
    if (stat1 == 49) {
      digitalWrite(LED, HIGH);
    } else if (stat1 == 48) {
      digitalWrite(LED, LOW);
    }
    Serial.println("Este es el dato:");
    Serial.println(stat1);
  }


//Puerta

  if (!client.connect(host, httpPort)) {
    Serial.println("Coneccion Fallida");
    return;
  }

  client.flush();

  Serial.print("Estado del cliente: " + client.connected());

  Serial.print("Obteniendo URL: ");
  Serial.println(urlDoor);
  //Creamos la peticion al servidor
  client.println(String("GET ") + urlDoor);

  unsigned long timeout2 = millis();
  while (client.available() == 0) {
    if (millis() - timeout2 > 5000) {
      Serial.println(">>> Se acabo el tiempo de espera puerta !");
      client.stop();
      return;
    }
  }

  //Imprimimos lo que nos devuelve el servidor
  while (client.available()) {
    int stat = client.read();  //En stat guardamos lo que nos devuelve la llamada a la bbdd
    if (stat == 49) {
      servoMotor.write(0);
    } else if (stat == 48) {
      servoMotor.write(90);
    }
    Serial.println("Este es el dato:");
    Serial.println(stat);

  }


//Humo

  if (!client.connect(host, httpPort)) {
      Serial.println("Coneccion Fallida");
      return;
    }

  client.flush();

  Serial.print("Estado del cliente: " + client.connected());

  if (digitalRead(SmokePin) == HIGH) {
    stateSmoke  = 1;
    tone(Zumbador, 440, 3000);
    Serial.println("Smoke detected!");
  } else {tone(Zumbador, 440);
    delay(3000);
    noTone(Zumbador);
    Serial.println("NO HAY HUMO");

    stateSmoke = 0;
    delay(1000);
  }



    Serial.print("Detector de humo: ");
    Serial.println(stateSmoke);

    //solo manda los datos cuando detecta humo, si no se pierde tiempo
  if(stateSmoke == 1){
    client.print(String("GET ") + urlSmoke + datoSmoke + stateSmoke + datoPlace + place + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Coneccion: Cerrada\r\n\r\n");

    unsigned long timeout4 = millis();
    while (client.available() == 0) {
      if (millis() - timeout4 > 5000) {
        Serial.println(">>> Se acabo el tiempo de espera !");
        client.stop();
        return;
      }
    }
  }
  
//Presencia

  if (!client.connect(host, httpPort)) {
      Serial.println("Coneccion Fallida");
      return;
  }
  client.flush();

  Serial.print("Estado del cliente: " + client.connected());

  if (digitalRead(PresencePin) == HIGH) {
    statePresencia = 1;
    Serial.println("Presencia detectada");
  } else {
    Serial.println("No presencia");

    statePresencia = 0;
    delay(1000);
  }

  if(statePresencia == 1){
    Serial.print("Obteniendo URL: ");
    Serial.println(urlPresence);
    //Creamos la peticion al servidor
    client.println(String("GET ") + urlPresence + datoPresence + statePresencia + datoPlace + place + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Coneccion: Cerrada\r\n\r\n");

    unsigned long timeout3 = millis();
    while (client.available() == 0) {
      if (millis() - timeout3 > 5000) {
        Serial.println(">>> Se acabo el tiempo de espera presencia !");
        client.stop();
        return;
      }
    }
  }
  
  client.flush();
  Serial.println();
  Serial.println("Cerrando Conexión");
  delay(3000);
}

