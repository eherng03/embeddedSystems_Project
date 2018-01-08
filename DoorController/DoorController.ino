
#include <ESP8266WiFi.h>
#include <Servo.h>

//Configuración de la red wifi y el host donde está el servidor
const char* ssid = "rasp";
const char* password = "raspberry";
const char* host = "192.168.43.247";

Servo servoMotor;

void setup() {

  servoMotor.attach(5);
  
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
  
  String url = "/IntelliHome/operations/getDoorStatus";
 
  Serial.print("Obteniendo URL: ");
  Serial.println(url);
  //Creamos la peticion al servidor
  client.println(String("GET ") + url);
  
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Se acabo el tiempo de espera !");
      client.stop();
      return;
    }
  }
  
  //Imprimimos lo que nos devuelve el servidor
  while (client.available()) {
    int stat = client.read();  //En stat guardamos lo que nos devuelve la llamada a la bbdd
    if(stat == 49){
      servoMotor.write(0);
    }else if(stat == 48){
      servoMotor.write(180);
    }
      
    Serial.print("Este es el dato: ");
    Serial.print(client.read());
    delay(3000);
  }

  Serial.println();
  Serial.println("Cerrando Conexión");
  delay(3000);
}
