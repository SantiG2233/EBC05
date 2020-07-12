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
//*********** MQTT CONFIG ***********
//***********************************
const char *mqtt_server = "";
const int mqtt_port = 1883;
const char *mqtt_user = "";
const char *mqtt_pass = "";
const char *root_topic_subscribe = "";
const char *root_topic_publish = "";


//***********************************
//*********** WIFI CONFIG ***********
//***********************************
const char* ssid = "";
const char* password = "";


//***********************************
//************* GLOBALES ************
//***********************************
WiFiClient esp;
PubSubClient client(esp);
char msg[25];
long count = 0;


//***********************************
//*************** RTSO **************
//***********************************
TaskHandle_t Task1;


//***********************************
//************ FUNCTIONS ************
//***********************************
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void setup_wifi();
void loop1(void* parameter);


void setup() {
	setup_wifi();
	client.setServer(mqtt_server, mqtt_port);
	client.setCallback(callback);

	Serial.begin(115200);
}

void loop1(void* parameter) { // Corre en el Núcleo 0
	for (;;) {

	}

}

void loop() { // Corre en el Núcleo 1 (Principal)
	
	if (!client.connected()) {
		reconnect();
	}

	if (client.connected()) {
		String str = "La cuenta es ->" + String(count);
		str.toCharArray(msg, 25);
		client.publish(root_topic_publish, msg);
		count++;
		delay(300);
	}
	client.loop();
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