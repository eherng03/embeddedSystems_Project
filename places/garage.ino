#include <DHT11.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

//ConfiguraciÃ³n de la red wifi y el host donde estÃ¡ el servidor
const char* ssid = "rasp";
const char* password = "raspberry";
const char* host = "192.168.43.247";

Servo servoMotor;
const int LED = 16;
int smokePin = 5;
int presencePin = 4;
int zumbador = 14;

void setup() {

  pinMode(smokePin, INPUT);
  pinMode(LED, OUTPUT);
  servoMotor.attach(2);
  pinMode(presencePin, INPUT);
  pinMode(zumbador, OUTPUT);

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
  int state;
  int stateSmoke;
  Serial.print("conectando a: ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Coneccion Fallida");
    return;
  }

  String url = "/IntelliHome/operations/getDoorStatus.php?place=garage";
  String urlLight = "/IntelliHome/operations/getLightStatus.php?place=garage";
  String urlSmoke = "/IntelliHome/operations/changeSmoke.php?";

  String datoPresence = "state=";
  String datoPlace = "&place=";
  String datoSmoke = "state=";


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


  if (!client.connect(host, httpPort)) {
    Serial.println("Coneccion Fallida");
    return;
  }

  client.flush();

  Serial.print("Estado del cliente: " + client.connected());

  Serial.print("Obteniendo URL: ");
  Serial.println(url);
  //Creamos la peticion al servidor
  client.println(String("GET ") + url);

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

  client.flush();

  Serial.print("Estado del cliente: " + client.connected());

  //Smoke
  if (digitalRead(smokePin) == HIGH) {
    state = 0;
    Serial.print("No hay humo");
  } else {
    Serial.print("Hay humo");
    tone(zumbador, 440);
    delay(3000);
    noTone(zumbador);
    state = 1;
  }

  if (state == 1) {
    if (!client.connect(host, httpPort)) {
      Serial.println("Conexion Fallida");
      return;
    }

    client.flush();
    Serial.print("Estado del cliente: " + client.connected());


    Serial.print("Obteniendo URL: ");
    Serial.println(urlSmoke);
    //Creamos la peticion al servidor
    client.print(String("GET ") + urlSmoke + datoSmoke + state + datoPlace + place + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Coneccion: Cerrada\r\n\r\n");

    unsigned long timeout3 = millis();
    while (client.available() == 0) {
      if (millis() - timeout3 > 5000) {
        Serial.println(">>> Se acabo el tiempo de espera humo !");
        client.stop();
        return;
      }
    }

    //Imprimimos lo que nos devuelve el servidor
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }

  client.flush();

  //Presence
  Serial.print("Estado del cliente: " + client.connected());
  if (digitalRead(presencePin) == HIGH) {
    state = 1;
    Serial.println("Motion detected!");
    delay(1000);
  } else {
    state = 0;
    delay(1000);
  }


  String urlPresence = "/IntelliHome/operations/changePresence.php?";
  Serial.print("Obteniendo URL: ");
  Serial.println(urlPresence);
  //Creamos la peticion al servidor
  client.print(String("GET ") + urlPresence + datoPresence + state + datoPlace + place + " HTTP/1.1\r\n" +
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

  client.flush();
  Serial.println();
  Serial.println("Cerrando Conexión");
  delay(3000);
}

