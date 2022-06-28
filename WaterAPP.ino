#define BLYNK_TEMPLATE_ID "TMPL4yb3N5Is"
#define BLYNK_DEVICE_NAME "WaterAmit"

#define BLYNK_PRINT SwSerial
#include <SoftwareSerial.h>
        
SoftwareSerial SwSerial(10, 11); // RX, TX
#include <BlynkSimpleStream.h>

char auth[] = "ME1xinkvEoF2Pp8ekkdlU0yCrfg1DxDm";

WidgetLCD lcd(V1);
long duration, distance;
int trig =4;
int eco = 5;
int Buzzer=2;
int Motor = 3;
int temp=0;
BlynkTimer timer;
void myTimerEvent()
{
  int data = analogRead(A2)*(3.20/1023.0)*100.0;
  Blynk.virtualWrite(V5, data);
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
  digitalWrite(2, pinValue);
  digitalWrite(3, pinValue);
}

void setup()
{
  SwSerial.begin(9600);
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
  timer.setInterval(1000L, myTimerEvent);

  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
  lcd.clear();
  lcd.print(0, 0, "Water Level");
}

void loop()
{
  lcd.clear();
  lcd.print(0, 0, "Water Level");
  
  digitalWrite(trig, LOW);
  delayMicroseconds(3);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  duration = pulseIn(eco, HIGH);
  distance = (duration/2) /322;
  lcd.print(7,1, distance);

if(distance>95 )
 {
     
     digitalWrite(Motor, LOW);
     
     digitalWrite(Buzzer, HIGH);
 }
 else
 {
   digitalWrite(Buzzer, LOW);
 }
  
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
  delay(1000);
}
