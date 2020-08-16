#define ANALOG_PIN_32 (32)
#define ANALOG_PIN_33 (33)
#define ANALOG_PIN_25 (25)

volatile byte half_revolutions;
volatile float rpm;
volatile float timeold;
const float  Pi = 3.1415926535897932384626433832795;
unsigned int time;
volatile byte half_revolutionsb;
volatile float rpmb;
volatile float timeoldb;
float reminder; 
float reminderb;
float t;
float  velmb;
    float velkb;
void setup()
{
  const int Pin = 14;
  Serial.begin(115200);
  pinMode(Pin, INPUT);
  attachInterrupt(Pin, magnet_detect, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)
  half_revolutions = 0;
  rpm = 0;
  timeold = 0;

  const int Pinb = 27;
  pinMode(Pinb, INPUT);
  attachInterrupt(Pinb, magnet_detectb, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)
  half_revolutionsb = 0;
  rpmb = 0;
  timeoldb = 0;  
}
void loop()
{
 time = millis();
 reminder = time % 3000;
 reminderb = time % 3000;
 
 
 if (half_revolutions >= 100) {
  rpm = 30 * 1000 / (time - timeold) * half_revolutions;
  t= rpm*.2820;
 

   rpmb = 30 * 1000 / (millis() - timeoldb) * half_revolutionsb;
    timeoldb = millis();
    half_revolutionsb = 0;
    velmb= rpmb*Pi*.254/60;
    velkb= velmb*3.6;
    if (isnan(rpm)){
      return;}
      
     half_revolutions = 0;
     half_revolutionsb = 0;
  timeold = time;
  timeoldb = millis();
  
   Serial.print("rpm motor: ");
   Serial.print(rpm);
   Serial.print("rpm eje teorico: ");
   
   Serial.print(t);
   Serial.print("  rpm eje: ");
   Serial.print(rpmb);
   Serial.print("  vel lineal m/s: ");
   Serial.print(velmb);
   Serial.print("  vel lineal km/h: ");
   Serial.print(velkb);
   
  }
void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
{
  half_revolutions++;
  //Serial.println("detect");
}
void magnet_detectb()//This function is called whenever a magnet/interrupt is detected by the arduino
{
  half_revolutionsb++;
  //Serial.println("detect");
}
