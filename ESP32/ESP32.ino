/*
 Name:		Dos_núcleos.ino
 Created:	11/07/2020
 Author:	angel
*/

#include <PubSubClient.h>
#include <WiFiUdp.h>
#include <WiFiType.h>
#include <WiFiSTA.h>
#include <WiFiServer.h>
#include <WiFiScan.h>
#include <WiFiMulti.h>
#include <WiFiGeneric.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ETH.h>


//***********************************
//*********** DEFINITIONS ***********
//***********************************
#define colorOut 19
#define S0 2
#define S1 4
#define S2 16
#define S3 17
#define B 0
#define Y 1
#define R 2
#define time 1000000


//***********************************
//*********** MQTT CONFIG ***********
//***********************************
const char* mqtt_server = "ioticos.org";
const int mqtt_port = 1883;
const char* mqtt_user = "VjclYKIMveCXbG0";
const char* mqtt_pass = "2xAfdxh1sV7owRE";
const char* root_topic_subscribe = "Fb91eInFO93GxEe";
const char* root_topic_publish = "Fb91eInFO93GxEe";


//***********************************
//*********** WIFI CONFIG ***********
//***********************************
const char* ssid = "";
const char* password = "";


//***********************************
//************* GLOBALS *************
//***********************************
WiFiClient esp;
PubSubClient client(esp);
char msg[25];
long count = 0;
uint8_t color;
int state = 0;
int countY = 0, countR = 0;
int ind = 0;
int dec = 0, uni = 0;
int num = 0;


//***********************************
//*************** RTOS **************
//***********************************
TaskHandle_t Task1, Task2;


//***********************************
//************ FUNCTIONS ************
//***********************************
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void setup_wifi();
void wifiLoop(void* parameter);
void errorCode(void* parameter);

//***********************************
//************** SETUP **************
//***********************************
void setup() {

	xTaskCreatePinnedToCore(
		wifiLoop, // Función elegida
		"Task 1",
		1000, // Stack
		NULL, // No parameters
		1, // Priority
		&Task1, // Created Task
		0 // Core
	);


	xTaskCreatePinnedToCore(
		errorCode, // Función elegida
		"Task 2",
		1000, // Stack
		NULL, // No parameters
		1, // Priority
		&Task2, // Created Task
		0 // Core
	);

	setup_wifi();
	client.setServer(mqtt_server, mqtt_port);
	client.setCallback(callback);

	pinMode(colorOut, INPUT);

	Serial.begin(115200);
}


//***********************************
//************** LOOPS **************
//***********************************
// Connection with server
void wifiLoop(void* parameter) {
	for (;;) {
		if (!client.connected()) {
			reconnect();
		}

		if (client.connected()) {
			String str = "La cuenta es ->" + String(count);
			str.toCharArray(msg, 25);
			client.publish(root_topic_publish, msg);
			count++;
			delay(1000);
		}

		client.loop();
	}

	vTaskDelay(10);
}

void errorCode(void* parameter) {
	for (;;) {
		state = pulseIn(colorOut, HIGH);

		if (state >= 700 && state <= 800) { // RED

			if (color == Y && ind == 0) { // First step
				// countR = 1;
				ind = 1;
			}

			if (color == Y && ind == 1) { // Second step
				ind = 2;
				dec = countY;
				countY = 0;
			}

			else if (color == R && ind == 2) { // Third step
				ind = 3;
			}

			else if (color == Y && ind == 3) { // Restart
				ind = 1;
				uni = countY;
				countY = 0;

				find_code();
			}

			color = R;
		}

		else if (state >= 500 && state <= 600) { // YELLOW

			if (ind == 1) {
				countY += 1;
			}

			if (ind == 3) {
				countY += 1;
			}

			else if (color != R && countY > 9) {
				countY = 0;
			}

			else if (color == R && ind == 2)
				ind = 1;

			color = Y;
		}

		else if (state >= 100 && state <= 200) { // OFF
			continue;
		}
	}

	vTaskDelay(10);
}


// Communication with Arduino Mega
void loop() {


}


//***********************************
//*********** WIFI CONNECT **********
//***********************************
void setup_wifi() {
	delay(10);

	Serial.println();
	Serial.println("Conectando a " + String(ssid));

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("Conectado a red WiFi");
	Serial.println("Dirección IP: " + String(WiFi.localIP()));
}


//***********************************
//************* CALLBACK ************
//***********************************
void callback(char* topic, byte* payload, unsigned int length) {
	String incoming = "";
	Serial.println("Mensaje recibido desde ->" + String(topic));

	for (int i = 0; i < length; i++) {
		incoming += (char)payload[i];
	}
	incoming.trim();
	Serial.println("Mensaje ->" + incoming);
}


//***********************************
//*********** MQTT CONNECT **********
//***********************************
void reconnect() {
	while (!client.connected()) {
		Serial.print("Intentando conexión MQTT...");

		// Creamos un cliente ID
		String clientId = "PRUEBA";
		clientId += String(random(0xffff), HEX);

		// Conectamos
		if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
			Serial.println("Conectado");

			// Nos suscribimos
			if (client.subscribe(root_topic_subscribe)) {
				Serial.println("Suscripción ok");
			}

			else
				Serial.println("Fallo en suscripción");
		}

		else {
			Serial.print("Falló conexión. Error ->" + String(client.state()));
			Serial.println("Reintentando en 5 segundos");
			delay(5000);
		}
	}
}

//***********************************
//************ FIND CODE ************
//***********************************
void find_code() {

	String d = (String)dec;
	String u = (String)uni;

	String code = d + u;

	num = code.toInt();

	switch (num) {
	case 12:;
		break;

	case 13:;
		break;

	case 14:;
		break;

	case 15:;
		break;

	case 16:;
		break;

	case 17:;
		break;

	case 18:;
		break;

	case 22:;
		break;

	case 23:;
		break;

	case 24:;
		break;

	case 25:;
		break;

	case 26:;
		break;

	case 27:;
		break;

	case 28:;
		break;

	case 29:;
		break;

	case 31:;
		break;

	case 32:;
		break;

	case 33:;
		break;

	case 34:;
		break;

	case 35:;
		break;

	case 36:;
		break;

	case 37:;
		break;

	case 38:;
		break;

	case 39:;
		break;

	case 41:;
		break;

	case 42:;
		break;

	case 43:;
		break;

	case 44:;
		break;

	case 45:;
		break;

	case 46:;
		break;

	case 47:;
		break;

	case 48:;
		break;

	case 49:;
		break;

	case 51:;
		break;

	case 52:;
		break;

	case 53:;
		break;

	case 54:;
		break;

	case 55:;
		break;

	case 56:;
		break;

	case 57:;
		break;

	case 58:;
		break;

	case 59:;
		break;

	case 60:;
		break;

	case 61:;
		break;

	case 62:;
		break;

	case 63:;
		break;

	case 64:;
		break;

	case 65:;
		break;

	case 66:;
		break;

	case 67:;
		break;

	case 68:;
		break;

	case 69:;
		break;

	case 71:;
		break;

	case 72:;
		break;

	case 73:;
		break;

	case 74:;
		break;

	case 75:;
		break;

	case 87:;
		break;

	case 89:;
		break;

	case 91:;
		break;

	case 92:;
		break;

	case 93:;
		break;

	case 94:;
		break;

	case 98:;
		break;

	case 99:;
		break;
	}

}