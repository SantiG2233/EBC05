/*
 Name:		SD_preliminar.ino
 Created:	21/07/2020 10:54:43
 Author:	Santiago
*/


#include <Arduino_FreeRTOS.h>
#include <SD.h>
#include <SPI.h>
File RaceData;
int SDpinCS = 53;
int green = 14;
int red = 15;

//RTOS
void SD_write(void* parameter);
TaskHandle_t Task1;

void setup() {

    Serial.begin(9600);
    pinMode(SDpinCS, OUTPUT);

    xTaskCreate(
        SD_write,
        "SD_data_login",
        1000,
        NULL,
        1,
        &Task1);

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
        // Ejemplo de escritura de datos en SD
        //RaceData.print(rtc.getTimeStr());
        //RaceData.print(",");
        //RaceData.print(int(rtc.getTemp()));
        //RaceData.print(",");
        //RaceData.print(velocidad);
        //RaceData.print(",");
        //RaceData.print(voltaje);
        //RaceData.print(",");
        //RaceData.print(corriente);
        //RaceData.print(",");
        //RaceData.println(distancia);
        //RaceData.close(); // close the file
    }
    // if the file didn't open, blinking red LED
    else {
        while (true);
        digitalWrite(red, HIGH);
        delay(1000);
        digitalWrite(red, LOW);
        delay(1000);
    }
    delay(250);
}