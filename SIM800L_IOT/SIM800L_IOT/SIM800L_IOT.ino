/*
 Name:		SIM800L_IOT.ino
 Created:	27/07/2020 17:24:11
 Author:	YARIB
*/
#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(3, 2);

#include <String.h>
#include <DHT.h> 

#define DHTPIN 4

DHT dht(DHTPIN, DHT11);
// the setup function runs once when you press reset or power the board
void setup() {

}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
