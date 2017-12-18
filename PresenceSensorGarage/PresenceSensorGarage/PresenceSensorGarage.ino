#include <DHT11.h>
#include <ESP8266WiFi.h>

const char* ssid = "rasp";
const char* password = "raspberry";
const char* host = "192.168.43.247";
int DOPin = 2;

void setup()
{
pinMode(DOPin, INPUT);
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
float temp, hum;
String place = "garage";
int state;

if (digitalRead(DOPin) ==HIGH){
   state = 1;
   Serial.println("Motion detected!"); 
   delay(1000);
}else {
   state = 0;
   delay(1000);
}
Serial.print(state);
Serial.print(place);
Serial.print("conectando a: ");
Serial.println(host);
WiFiClient client;
const int httpPort = 80;
if (!client.connect(host, httpPort)) {
Serial.println("Coneccion Fallida");
return;
}
String url = "/IntelliHome/operations/changePresence.php?";
String dato1 = "state=";
String dato3 = "&place=";
Serial.print("Obteniendo URL: ");
Serial.println(url);
//Creamos la peticion al servidor
client.print(String("GET ") + url + dato1 + state + dato3 + place + " HTTP/1.1\r\n" +
"Host: " + host + "\r\n" +
"Coneccion: Cerrada\r\n\r\n");
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
String line = client.readStringUntil('\r');
Serial.print(line);
}

Serial.println();
Serial.println("Cerrando Conexión");
delay(2000);
}
