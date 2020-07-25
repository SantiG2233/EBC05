/*
    Name:       Sensor_Distancia.ino
    Created:	7/25/2020 9:24:32 AM
    Author:     Sara 
*/
#include "Adafruit_VL53L0X.h"

#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

// Pines desactivar
#define SHT_LOX1 7
#define SHT_LOX2 6

// Objetos para cada sensor 
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

// medidas
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;

void setID() {
    // all reset 
    digitalWrite(SHT_LOX1, LOW);
    digitalWrite(SHT_LOX2, LOW);
    delay(10);
    // all unreset
    digitalWrite(SHT_LOX1, HIGH);
    digitalWrite(SHT_LOX2, HIGH);
    delay(10);

    // activating LOX1 and reseting LOX2
    digitalWrite(SHT_LOX1, HIGH);
    digitalWrite(SHT_LOX2, LOW);

    // initing LOX1
    if (!lox1.begin(LOX1_ADDRESS)) {
        Serial.println(F("No se detecta el sensor 1"));
        while (1);
    }
    delay(10);

    // activating LOX2
    digitalWrite(SHT_LOX2, HIGH);
    delay(10);

    //initing LOX2
    if (!lox2.begin(LOX2_ADDRESS)) {
        Serial.println(F("No se detecta el sensor 2"));
        while (1);
    }
}

void read_dual_sensors() {

    lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
    lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
    // Evaluate sensor 1
    Serial.print("1: ");
    if (measure1.RangeStatus != 4) {
        if (measure1.RangeMilliMeter <= 300) {
            Serial.println("Objeto a 30cm de distancia");
        }
        if (measure1.RangeMilliMeter <= 500) {
            Serial.println("Objeto a 50cm de distancia");
        }
        if (measure1.RangeMilliMeter <= 1000) {
            Serial.println("Objeto a 1m de distancia");
        }
    }
    Serial.print("2: ");
    if (measure2.RangeStatus != 4) {
        if (measure2.RangeMilliMeter <= 300) {
            Serial.println("Objeto a 30cm de distancia");
        }
        if (measure1.RangeMilliMeter <= 500) {
            Serial.println("Objeto a 50cm de distancia");
        }
        if (measure1.RangeMilliMeter <= 1000) {
            Serial.println("Objeto a 1m de distancia");
        }
    }

    void setup() {
        Serial.begin(115200);
        while (!Serial) { delay(1); }
        pinMode(SHT_LOX1, OUTPUT);
        pinMode(SHT_LOX2, OUTPUT);
        digitalWrite(SHT_LOX1, LOW);
        digitalWrite(SHT_LOX2, LOW);
        setID();
    }

    void loop() {
        read_dual_sensors();
        delay(100);
    }
