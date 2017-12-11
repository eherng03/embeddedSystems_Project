#include <DHT11.h>
#include <ESP8266WiFi.h>

DHT11 dht11(D4);
const char* ssid = "rasp";
const char* password = "raspberry";
const char* host = "192.168.43.247";

int DOPin = 2; // select the pin for the LED
int ledPin =13;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(DOPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop() {  
  float state;
  String place = "kitchen";

 if (digitalRead(DOPin) ==HIGH){
    digitalWrite(ledPin, LOW);
    state = 0;
  }else {
    digitalWrite(ledPin, HIGH);
    state = 1;
  }
  delay(1000);
  

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Coneccion Fallida");
    return;
  }

  String url = "/IntelliHome/operations/changeSmoke.php?";
  String dato1 = "&state =";
  String dato2 = "&place =";

  client.print(String("GET ") + url + dato1 + state + dato2 + place + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Coneccion: Cerrada\r\n\r\n");


  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
    Serial.println(">>> Se acabo el tiempo de espera !");
    client.stop();
    return;
  }

  //Imprimimos lo que nos devuelve el servidor
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  delay(3000);
}
