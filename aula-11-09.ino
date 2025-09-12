#include <WiFi.h>
#include <HTTPClient.h>
#include <DFRobot_Heartrate.h>
 
const int sensorPin = 25;
DFRobot_Heartrate heartrate(DIGITAL_MODE);
 
// Wi-Fi e ThingSpeak
const char* ssid = "FIAP-IOT";
const char* password = "F!@p25.IOT";
const char* apiKey = "4OV158QDHQHUOU7Y";
const char* server = "http://api.thingspeak.com";
 
void setup() {
  Serial.begin(115200);
 
  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" conectado!");
}
 
void loop() {
  heartrate.getValue(sensorPin);
  int rateValue = 80;
 

    Serial.print("Batimento cardíaco: ");
    Serial.println(rateValue);
 
    // Enviar ao ThingSpeak
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = String(server) + "/update?api_key=" + apiKey + "&field1=" + String(rateValue);
      http.begin(url);
      int httpCode = http.GET();
 
      if (httpCode > 0) {
        Serial.println("Dados enviados ao ThingSpeak com sucesso!");
      } else {
        Serial.print("Erro ao enviar dados. Código HTTP: ");
        Serial.println(httpCode);
      }
 
      http.end();
    } else {
      Serial.println("WiFi não conectado.");
    }
 
  delay(5000); // Aguarde 5 segundos entre envios
}
 