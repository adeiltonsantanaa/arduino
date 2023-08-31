#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int sensorPin = A0;
const int backlightPin = 2;
const int ledPin = A4;
const int lcdColumns = 20;
const int lcdRows = 4;
const float betaValue = 3950.0;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(backlightPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(backlightPin, HIGH);
  
  int analogValue = analogRead(sensorPin);
  float resistance = (1023.0 / analogValue) - 1.0;
  resistance = 10000.0 / resistance;
  float celsius = 1.0 / (log(resistance / 10000.0) / betaValue + 1.0 / 298.15) - 273.15;
  
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(0, 1);
  lcd.print(celsius, 2);
  lcd.print(" C");
  
  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print(", Celsius: ");
  Serial.println(celsius, 2);
  
  delay(1000);
  
  digitalWrite(backlightPin, LOW);
  delay(1000);
}
