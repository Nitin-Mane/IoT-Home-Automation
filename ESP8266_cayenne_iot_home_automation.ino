/*
This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.

The CayenneMQTT Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. If you have not already installed the ESP8266 Board Package install it using the instructions here: https://github.com/esp8266/Arduino#installing-with-boards-manager.
2. Select your ESP8266 board from the Tools menu.
3. Set the Cayenne authentication info to match the authentication info from the Dashboard.
4. Set the network name and password.
5. Compile and upload the sketch.
6. A temporary widget will be automatically generated in the Cayenne Dashboard. To make the widget permanent click the plus sign on the widget.
*/

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include "ESP8266WiFi.h"

// WiFi network info.
char ssid[] = "Redmi-12";
char wifiPassword[] = "Test@1234";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "0c6e8050-2b95-11e8-a353-951fa95ba610";
char password[] = "2aafaec51df9c46fa44b316272bb223c5ddf9c1d";
char clientID[] = "7650da90-6554-11ea-a38a-d57172a4b4d4";


void setup() {
	pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
	Serial.begin(9600);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
	Cayenne.loop();
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
//CAYENNE_OUT_DEFAULT()
//{
	// Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
//	Cayenne.virtualWrite(0, millis());
	// Some examples of other functions you can use to send data.
	//Cayenne.celsiusWrite(1, 22.0);
	//Cayenne.luxWrite(2, 700);
	//Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
//}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
//CAYENNE_IN_DEFAULT()
//{
//	CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
//}

CAYENNE_IN(V0)
{
  CAYENNE_LOG("Got a value: %s", getValue.asStr());
  int i = getValue.asInt();
  
  if (i == 0)
  {
    digitalWrite(D1, HIGH);
  }
  else
  {
    digitalWrite(D1, LOW);
  }  
}

CAYENNE_IN(V1)
{
  CAYENNE_LOG("Got a value: %s", getValue.asStr());
  int i = getValue.asInt();
  
  if (i == 0)
  {
    digitalWrite(D2, HIGH);
  }
  else
  {
    digitalWrite(D2, LOW);
  }  
}
