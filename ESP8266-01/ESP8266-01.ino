#include <ESP8266WiFi.h>
#include "Gsender.h"

#pragma region Globals
const char* ssid = "Name of my WIFI";
const char* password = "Password of my WIFI";
uint8_t connection_state = 0;                    // Connected to WIFI or not
uint16_t reconnect_interval = 10000;             // If not connected wait time to try again
#pragma endregion Globals
int contador = 0;
uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
  static uint16_t attempt = 0;
  Serial.print("Connecting to ");
  if (nSSID) {
    WiFi.begin(nSSID, nPassword);
    Serial.println(nSSID);
  } else {
    WiFi.begin(ssid, password);
    Serial.println(ssid);
  }

  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 50)
  {
    delay(200);
    Serial.print(".");
  }
  ++attempt;
  Serial.println("");
  if (i == 51) {
    Serial.print("Connection: TIMEOUT on attempt: ");
    Serial.println(attempt);
    if (attempt % 2 == 0)
      Serial.println("Check if access point available or SSID and Password\r\n");
    return false;
  }
  Serial.println("Connection: ESTABLISHED");
  Serial.print("Got IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

void Awaits()
{
  uint32_t ts = millis();
  while (!connection_state)
  {
    delay(50);
    if (millis() > (ts + reconnect_interval) && !connection_state) {
      connection_state = WiFiConnect();
      ts = millis();
    }
  }
}

void setup()
{
  pinMode(2, INPUT_PULLUP);
  Serial.begin(115200);
  connection_state = WiFiConnect();
  if (!connection_state) // if not connected to WIFI
    Awaits();          // constantly trying to connect

  Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
  String subject = "Subject is optional!";
  if (gsender->Subject(subject)->Send("ajcarracedo@gmail.com", "Setup test")) {
    Serial.println("Message send.");
  } else {
    Serial.print("Error sending message: ");
    Serial.println(gsender->getError());
  }


}

void loop() {

  Serial.print("funciona ");
  Serial.println(contador);
  contador = contador + 1;
  int sensorValue = digitalRead(2);
  String stringValue = String(sensorValue, DEC);
  Serial.println(stringValue);

  if (stringValue == "0")
  {
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "Alimentoooooo!";
    if (gsender->Subject(subject)->Send("ajcarracedo@gmail.com", "Que me mueroooo")) {
      Serial.println("Message send.");
    } else {
      Serial.print("Error sending message: ");
      Serial.println(gsender->getError());
    }
  }

  delay(5000);
}




