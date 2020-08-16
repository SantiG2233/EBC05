/*
 Name:		SIM800L_IOT.ino
 Created:	27/07/2020 17:24:11
 Author:	YARIB
*/
#include <HardwareSerial.h> 
#include <String.h>
#include <DHTesp.h> 

#define DHTPIN 15
#define TIME 100

DHTesp dht;
HardwareSerial gprsSerial(2);

bool SIM800L_SetUp = true;
float h;
float t;

void setup()
{
	Serial.begin(115200);
	gprsSerial.begin(115200, SERIAL_8N1, 16, 17);
	dht.setup(DHTPIN, DHTesp::DHT11);
	delay(1000);

}

void loop()
{
	h = dht.getHumidity();
	t = dht.getTemperature();

	Serial.print("Temperature = " + String(t) + " °C");
	Serial.print("Humidity = " + String(h) + " %");

	if (SIM800L_SetUp) {
		SetUpConnection();
		SIM800L_SetUp = false;
	}

	gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\""); //Indicamos el tipo de conexión, url o dirección IP y puerto al que realizamos la conexión
	delay(1000);

	ShowSerialData();
	gprsSerial.println("AT+CIPSEND");//ENVÍA DATOS A TRAVÉS DE una CONEXIÓN TCP O UDP
	Serial.println();
	delay(1000);
	ShowSerialData();

	gprsSerial.println();
	String str = "GET https://api.thingspeak.com/update?api_key=ULT9XDI0JGNT8X77&field1=" + String(t) + "&field2=" + String(h);
	Serial.println(str);
	gprsSerial.println(str);//begin send data to remote server

	delay(1000);
	ShowSerialData();

	gprsSerial.println((char)26);//sending
	delay(1000);//waitting for reply, important! the time is base on the condition of internet 
	gprsSerial.println();

	ShowSerialData();
}
void ShowSerialData()
{
	while (gprsSerial.available() != 0)
		Serial.write(gprsSerial.read());
	delay(100);

}
void SetUpConnection()
{
	if (gprsSerial.available())
		Serial.write(gprsSerial.read());

	gprsSerial.println("AT");
	delay(1000);

	gprsSerial.println("AT+CPIN?");
	delay(1000);

	gprsSerial.println("AT+CREG?");
	delay(1000);

	gprsSerial.println("AT+CIPSTATUS"); //Consultar el estado actual de la conexión
	delay(2000);

	gprsSerial.println("AT+CIPMUX=0"); //comando configura el dispositivo para una conexión IP única o múltiple 0=única
	delay(2000);

	gprsSerial.println("AT+CSTT=\"internet.itelcel.com\""); //comando configura el APN, nombre de usuario y contraseña."gprs.movistar.com.ar","wap","wap"->Movistar Arg.
	delay(1000);
	ShowSerialData();

	gprsSerial.println("AT+CIICR");//REALIZAR UNA CONEXIÓN INALÁMBRICA CON GPRS O CSD
	delay(3000);
	ShowSerialData();

	gprsSerial.println("AT+CIFSR");// Obtenemos nuestra IP local
	delay(2000);

	ShowSerialData();

	gprsSerial.println("AT+CIPSPRT=0");  //Establece un indicador '>' al enviar datos
	delay(3000);

	ShowSerialData();


}