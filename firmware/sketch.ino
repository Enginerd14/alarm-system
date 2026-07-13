#include <LiquidCrystal_I2C.h>
#include <Wire.h>


const int irPin = 3;
const int buttonPin = 2;
const int micPin = A0;
const int vibPin = 4;
const int buzzPin = 6;
const int potPin = A1;

bool armed = false;
bool alarmTrig = false;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(vibPin, INPUT);
  pinMode(buzzPin, OUTPUT);

  Serial.begin(9600);
  

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Alarm system");
  lcd.setCursor(0,1);
  lcd.print("DISARMED");
}

void loop()
{

  if (digitalRead(buttonPin) == LOW)
  {
    alarmTrig = false;
    armed = !armed;
    display();
    delay(250);
  }

  if (armed == true)
  {
    int soundLevel = analogRead(micPin);
    int vib = digitalRead(vibPin);

    int sensitivity = analogRead(potPin);
    int soundThreshold = map(sensitivity, 0, 1023, 100, 900);

    if (soundLevel > soundThreshold || vib == HIGH)
    {
      alarmTrig = true;
      display();
    }
  }
  
  if (alarmTrig == true)
  {
    digitalWrite(buzzPin, HIGH);
    delay(250);
    digitalWrite(buzzPin, LOW);
    delay(250);
  }
  else
  {
    digitalWrite(buzzPin, LOW);
  }
}

void display()
{
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Alarm System");

  if (alarmTrig == true)
  {
    lcd.setCursor(0,1);
    lcd.print("!ALARM ALERT!");
  }
  else if (armed == true)
  {
    lcd.setCursor(0,1);
    lcd.print("ARMED");
  }
  else 
  {
    lcd.setCursor(0,1);
    lcd.print("DISARMED");
  }
}
