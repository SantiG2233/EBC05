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
int HallSensor = 3;
int MaxRPM = 8000;
int rpmmaximum = 0;
int RaceTime = 3600000;

//General Variable/Function to obtain RPM´s 
int getRPM()
{
    int count = 0;
    boolean countFlag = LOW;
    unsigned long currentTime = 0;
    unsigned long startTime = millis();
    while (currentTime <= RaceTime)
    {
        if (digitalRead(HallSensor) == HIGH)
        {
            countFlag = HIGH;
        }
        if (digitalRead(HallSensor) == LOW && countFlag == HIGH)
        {
            count++;
            countFlag = LOW;
        }
        currentTime = millis() - startTime;
    }
    int countRpm = int(60000 / float(RaceTime)) * count;
    return countRpm;
}

//RTOS
void SD_write(void* parameter);
TaskHandle_t Task1;

void setup() {

    pinMode(SDpinCS, OUTPUT);
    pinMode(HallSensor, INPUT);
    Serial.begin(9600);
    

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

// Loop used to write all data on the SD card to post-race analysis
void SD_write(void* parameter) {
    RaceData = SD.open("Data.txt", FILE_WRITE);
    if (RaceData) {
        // Ejemplo de escritura de datos en SD
        //RaceData.print(rtc.getTimeStr());
        //RaceData.print(",");
        RaceData.print(int(getRPM()));  // writes RPM measures in the SD card
        RaceData.print(",");
        //RaceData.print(voltaje);
        //RaceData.print(",");
        //RaceData.print(corriente);
        //RaceData.print(",");
        //RaceData.println(distancia);
        RaceData.close(); // close the file
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

