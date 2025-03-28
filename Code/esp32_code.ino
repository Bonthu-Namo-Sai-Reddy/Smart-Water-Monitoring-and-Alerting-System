#include "twilio.hpp"

// Set these - but DON'T push them to GitHub!
static const char *ssid = "WIFI NAME HERE";
static const char *password = "WIFI PASSWORD HERE";

// Values from Twilio (find them on the dashboard)
static const char *account_sid = "ACC_SID FROM TWILIO";
static const char *auth_token = "AUTH TOKEN FROM TWILIO";
// Phone number should start with "+<countrycode>"
static const char *from_number = "NUMBER FROM TWILIO";

// You choose!
// Phone number should start with "+<countrycode>"
static const char *to_number = "TARGET(YOUR) MOBILE NUMBER"; //FILL xxxx WITH YOUR MOBILE NUMBER

Twilio *twilio;

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi network: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting...");
    delay(500);
  }
  Serial.println("Connected to WiFi");

  twilio = new Twilio(account_sid, auth_token);

  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {
    String dataReceived = Serial.readStringUntil('\n');
    Serial.print("Received TDS Value from Arduino: ");
    Serial.println(dataReceived);

    // Convert the received data to an integer
    int tdsValue = dataReceived.toInt();

    if (tdsValue > 250) {
      // If TDS value is above 250, send an SMS
      String message = "TDS value is above 250!"; // Modify the message as needed
      String response;
      bool success = twilio->send_message(to_number, from_number, message, response);
      if (success) {
        Serial.println("Sent message successfully!");
      } else {
        Serial.println("Failed to send message:");
        Serial.println(response);
      }
    }
  }
}
