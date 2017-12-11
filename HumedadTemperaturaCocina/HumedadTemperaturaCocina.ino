#include <DHT11.h>
#include <ESP8266WiFi.h>

DHT11 dht11(D4);
const char* ssid = "rasp";
const char* password = "raspberry";
const char* host = "192.168.43.247";

void setup()
{
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
String place = "kitchen";
if ((err = dht11.read(hum, temp)) == 0)
{
Serial.print("Temperatura: ");
Serial.print(temp);
Serial.print(" Humedad: ");
Serial.print(hum);
Serial.print(place);
Serial.println();
}
else
{
Serial.print("Error Num :");
Serial.print(err);
Serial.println();
}
Serial.print("conectando a: ");
Serial.println(host);
WiFiClient client;
const int httpPort = 80;
if (!client.connect(host, httpPort)) {
Serial.println("Coneccion Fallida");
return;
}
String url = "/IntelliHome/operations/changeTemperature.php?";
String url2 = "/IntelliHome/operations/changeHumidity.php?";
String dato1 = "temp=";
String dato2 = "hum=";
String dato3 = "&place=";
Serial.print("Obteniendo URL: ");
Serial.println(url);
//Creamos la peticion al servidor
client.print(String("GET ") + url + dato1 + temp + dato3 + place + " HTTP/1.1\r\n" +
"Host: " + host + "\r\n" +
"Coneccion: Cerrada\r\n\r\n");
client.print(String("GET ") + url2 + dato2 + hum + dato3 + place + " HTTP/1.1\r\n" +
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
delay(30000);
}
