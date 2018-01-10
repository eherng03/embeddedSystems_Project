
#include <ESP8266WiFi.h>
#include <Servo.h>

//Configuración de la red wifi y el host donde está el servidor
const char* ssid = "rasp";
const char* password = "raspberry";
const char* host = "192.168.43.247";

Servo servoMotor;
const int LED = 16;

void setup() {

  pinMode(LED, OUTPUT);
  servoMotor.attach(2);
  
  Serial.begin(9600);
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

  Serial.print("Obteniendo URL: ");
    Serial.println(urlLight);
    //Creamos la peticion al servidor
    client.println(String("GET ") + urlLight);
    
    unsigned long timeout1 = millis();
  while (client.available() == 0) {
    if (millis() - timeout1 > 5000) {
      Serial.println(">>> Se acabo el tiempo de espera puerta !");
      //client.stop();
      return;
    }
  }

  //Imprimimos lo que nos devuelve el servidor
 while (client.available()) {
    int stat1 = client.read();  //En stat guardamos lo que nos devuelve la llamada a la bbdd
    if(stat1 == 49){
      digitalWrite(LED, HIGH);
    }else if(stat1 == 48){
      digitalWrite(LED, LOW);
    }
    Serial.println("Este es el dato:");
    Serial.println(stat1);
    delay(300);
    break;
 }
 
  Serial.print("Obteniendo URL: ");
  Serial.println(url);
  //Creamos la peticion al servidor
  client.println(String("GET ") + url);
  
  
  //Imprimimos lo que nos devuelve el servidor
  while (client.available()) {
    int stat = client.read();  //En stat guardamos lo que nos devuelve la llamada a la bbdd
    if(stat == 49){
      servoMotor.write(0);
    }else if(stat == 48){
      servoMotor.write(180);
    }
    Serial.println("Este es el dato:");
    Serial.println(stat);
    delay(300);
  
  }

  Serial.println();
  Serial.println("Cerrando Conexión");
  delay(3000);
}
