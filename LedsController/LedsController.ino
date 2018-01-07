
#include <ESP8266WiFi.h>

//Configuración de la red wifi y el host donde está el servidor
const char* ssid = "Orange-1596";
const char* password = "qRbTqHWkZEbZr";
const char* host = "192.168.1.106";

const int LED = 16;


void setup() {

  pinMode(LED, OUTPUT);
  
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
  String place = "room";
 
  Serial.print("conectando a: ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Coneccion Fallida");
    return;
  }
  
  String url = "/IntelliHome/operations/getLightStatusArduino.php?place=room";
 
  Serial.print("Obteniendo URL: ");
  Serial.println(url);
  //Creamos la peticion al servidor
  client.println(String("GET ") + url + " HTTP/1.1\r\n");
  client.println(String("Host: ") + host);
  client.println("Conection: close");
  
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
    //char* stat = client.read();  //En stat guardamos lo que nos devuelve la llamada a la bbdd
    Serial.print(client.read());
    //digitalWrite(LED, atoi(stat));
  }

  Serial.println();
  Serial.println("Cerrando Conexión");
  delay(30000);
}
