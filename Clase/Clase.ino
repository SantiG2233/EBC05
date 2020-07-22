/*
 Name:		Clase.ino
 Created:	14/07/2020 17:09:44
 Author:	angel
*/


#include <SoftwareSerial.h>
#include <Arduino_FreeRTOS.h>

SoftwareSerial Esp(2, 3); // RX TX

#define pin 15
#define led 8

int var = 0;

// RTOS
void led_op(void *parameter);
TaskHandle_t Task1, Task2;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(pin, INPUT_PULLUP);
	pinMode(led, OUTPUT);

	xTaskCreatePinnedToCore(
		led_op,
		"Led_operation",
		1000,
		NULL,
		0,
		&Task1,
		0
	);

	xTaskCreatePinnedToCore(
		led_op,
		"Led_operation",
		1000,
		NULL,
		0,
		&Task1,
		1
	);



	Serial.begin(115200);
	Esp.begin(115200);
}

// the loop function runs over and over again until power down or reset
void loop() {
	int data;

	if (Esp.available() > 0) {
		while (Esp.available() > 0) {
			data = Esp.read();

			Serial.println(data);
		}
   }

}

void led_op(void *parameter) {
	
	for (;;) {

		int lec = digitalRead(pin);

		if (lec == true) {
			digitalWrite(led);
		}
	}

	vTaskDelay(10);
}


