//Librerias 
#include <Arduino_FreeRTOS.h>
#include <virtuabotixRTC.h>
#include <Arduino_FreeRTOS.h>
#include <SD.h>
#include <SPI.h>

//  Objetos
//SD_Hall

File RaceData;
int SDpinCS = 53;
int green = 14;
int red = 15;
int HallSensor = 3;
int MaxRPM = 8000;
int rpmmaximum = 0;
unsigned long int RaceTime = 3600000;

virtuabotixRTC myRTC(6, 7, 8);

//General Variable/Function to obtain RPM�s 
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
    int countRpm = int(216000000 / float(RaceTime)) * count;
    return countRpm;
}

//RTOS
void Sensor_Corriente (void *parameter);
void SD_write(void* parameter);
void Sensor_Velocidad (void *parameter);
void Sensor_Voltaje(void *parameter);

TaskHandle_t Task1, Task2,Task3;

void setup() {
//Pin modes 

    pinMode(SDpinCS, OUTPUT);
    pinMode(HallSensor, INPUT);
    Serial.begin(9600);

// seconds, min, hour, day of week, day of month, month, year
    myRTC.setDS1302Time(0, 37, 19, 2, 21, 7, 2020);
    
// tasks definitions 
  xTaskCreate(
    Sensor_Corriente,
    "Operacion_sensor_corriente",
    1000, //Se necesita comprobar el dato 
    NULL,
    1,
    &Task1
    );
  
  xTaskCreate(
    SD_write,
    "SD_data_login",
    1000, //Se necesita comprobar el dato 
    NULL,
    2,
    &Task2
    );
  
   xTaskCreate(
    Sensor_Voltaje,
    "Operacion_sensor_corriente",
    1000, //Se necesita comprobar el dato 
    NULL,
    3,
    &Task3
    );
    
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
  // put your main code here, to run repeatedly:
  Serial.print("Did we won?");

}

//Sensor de Corriente 
void Sensor_Corriente (void *parameter){
  for(;;){
    
  }
}

//SD
void SD_write(void* parameter){
   RaceData = SD.open("Data.txt", FILE_WRITE);
    myRTC.updateTime();
    if (RaceData) {
        // Ejemplo de escritura de datos en SD
        RaceData.print(myRTC.year);
        RaceData.print("/");
        RaceData.print(myRTC.month);
        RaceData.print("/");
        RaceData.print(myRTC.dayofmonth);
        RaceData.print("/");
        RaceData.print(myRTC.hours);
        RaceData.print("/");
        RaceData.print(myRTC.minutes);
        RaceData.print("/");
        RaceData.print(myRTC.seconds);
        RaceData.print(",");
        RaceData.print(getRPM());  // writes RPM measures in the SD card
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

//Sensor voltaje 
void Sensor_Voltaje(void *parameter){
  for(;;){
    
  } 
}
