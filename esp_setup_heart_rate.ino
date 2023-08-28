#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <ArduinoJson.h>


const char* ssid = "Harshith";   // Your Network SSID
const char* password = "harshith";       // Your Network Password

int val=0;
// int pin = A0; // LM35 Pin Connected at A0 Pin


WiFiClient client;

unsigned long myChannelNumber = 2245215; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "2O4GF5WPIOVF5RKU"; //Your Write API Key

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  ThingSpeak.begin(client);
}

// void loop()
// {
  
//   // int Signal = analogRead(pin);
//   // Serial.println(Signal);     
//   // ThingSpeak.writeField(myChannelNumber, 1,50, myWriteAPIKey);



// if (Serial.available()) {
   
//     // Serial.write(Serial.read());

//     float l=float(Serial.read());
//     Serial.println(l);


    
//   }
//       int k=(val%2)+1;
//     // ThingSpeak.writeField(myChannelNumber,k,Serial.read(), myWriteAPIKey);
//     val=val+1;
//   delay(3000);
// }


void loop() {
  if (Serial.available()) {
    String jsonString = Serial.readStringUntil('\n');  // Read the JSON string
    
    // Parse the JSON string
    DynamicJsonDocument jsonDocument(100);
    DeserializationError error = deserializeJson(jsonDocument, jsonString);
    
    if (!error) {
      // Get values from the JSON object
      float temperature = jsonDocument["temperature"];
      float pulse = jsonDocument["pulse"];
      float ecg = jsonDocument["ecg"];

      ThingSpeak.writeField(myChannelNumber,1,pulse, myWriteAPIKey);
      ThingSpeak.writeField(myChannelNumber,2,temperature, myWriteAPIKey);
      ThingSpeak.writeField(myChannelNumber,3,ecg, myWriteAPIKey);

      Serial.println("\nTemperature: ");
      Serial.println(temperature);
      Serial.println("\nPulse: ");
      Serial.println(pulse);
      Serial.println("\ECG: ");
      Serial.println(ecg);

      // Now you can use the temperature and humidity values in your ESP8266 code
    }
  }
}