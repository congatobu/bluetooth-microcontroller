#include <SoftwareSerial.h>
#include <Wire.h>
#include <ArduinoJson.h>

#define TX_PIN 4
#define RX_PIN 3

SoftwareSerial bluetooth(RX_PIN, TX_PIN);

long send_data_time_out = 1000;
long send_data_time = 0;

//---------------------------------------
long randomNumber;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {}

  bluetooth.begin(9600);
  randomSeed(analogRead(0));
  Serial.println("Init done ...");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (bluetooth.available() > 0) {
    String data = bluetooth.readStringUntil('\n');
    Serial.println(data);

    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, data);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    }else {
      double gx = doc["gx"];
      double gy = doc["gy"];
      double gz = doc["gz"];
      
      Serial.print("gx:");Serial.println(gx,4);
    }
    

  }

  if (millis() >= send_data_time + send_data_time_out) {
    send_data_time = send_data_time + send_data_time_out;

    // randomNumber = random(100);
    // bluetooth.println(randomNumber);
    // Serial.print("send: ");Serial.println(randomNumber);
  }
}
