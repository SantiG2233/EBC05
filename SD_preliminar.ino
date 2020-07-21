/*
 Name:		SD_preliminar.ino
 Created:	21/07/2020 10:54:43
 Author:	Santiago
*/


#include <Arduino_FreeRTOS.h>
#include <coop_threads.h>
#include <coop_config.h>
#include <SD.h>
#include <SPI.h>
File RaceData;
int SDpinCS = 53; // Pin 10 on Arduino Uno
int green = 4;
int red = 5;

//RTOS
void SD_write(void* parameter);

void setup() {

    Serial.begin(9600);
    pinMode(SDpinCS, OUTPUT);

    

    // SD Card Initialization
    if (SD.begin())
    {
        digitalWrite(green, HIGH);
    }
    else
    {
        digitalWrite(red,HIGH);
        return;
    }
}

void loop() {
 
}

void SD_write(void* parameeter) {
    RaceData = SD.open("Data.txt", FILE_WRITE);
    if (RaceData) {
        //RaceData.print(rtc.getTimeStr());
        RaceData.print(",");
        //RaceData.println(int(rtc.getTemp()));
        RaceData.close(); // close the file
    }
    // if the file didn't open, print an error:
    else {
        digitalWrite(red, HIGH);
    }
    delay(250);
}