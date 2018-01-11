#include <DHT11.h>
#include <ESP8266WiFi.h>

//Configuración de la red wifi y el host donde está el servidor
const char* ssid = "rasp";
const char* password = "raspberry";
const char* host = "192.168.43.247";

const int LED = 16;
DHT11 dht11(D4);

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
  float temp, hum;
  String place = "bath";
  int state;

  Serial.print("conectando a: ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Coneccion Fallida");
    return;
  }

  String urlLight = "/IntelliHome/operations/getLightStatus.php?place=garage";

  //Luz

  Serial.print("Obteniendo URL: ");
  Serial.println(urlLight);
  //Creamos la peticion al servidor
  client.println(String("GET ") + urlLight);

  unsigned long timeout1 = millis();
  while (client.available() == 0) {
    if (millis() - timeout1 > 5000) {
      Serial.println(">>> Se acabo el tiempo de espera puerta !");
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

  //Presence

  if (!client.connect(host, httpPort)) {
    Serial.println("Coneccion Fallida");
    return;
  }

  client.flush();

  Serial.print("Estado del cliente: " + client.connected());
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


  String urlTemp = "/IntelliHome/operations/changeTemperature.php?";
  String urlHum = "/IntelliHome/operations/changeHumidity.php?";
  String dato1 = "temp=";
  String dato2 = "hum=";
  String dato3 = "&place=";
  Serial.print("Obteniendo URL: ");
  Serial.println(urlTemp);
  //Creamos la peticion al servidor
  client.print(String("GET ") + urlTemp + dato1 + temp + dato3 + place + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Coneccion: Cerrada\r\n\r\n");
  client.print(String("GET ") + urlHum + dato2 + hum + dato3 + place + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Coneccion: Cerrada\r\n\r\n");
  unsigned long timeout3 = millis();
  while (client.available() == 0) {
    if (millis() - timeout3 > 5000) {
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
  delay(3000);
}
