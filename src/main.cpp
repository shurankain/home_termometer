#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>

Adafruit_BME280 internalBME;
Adafruit_BME280 externalBME;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
const int motionPin = 8; // Motion sensor pin

void setup()
{
  Serial.begin(9600);
  pinMode(motionPin, INPUT_PULLUP);

  internalBME.begin(0x77);
  lcd.init();
}

// internalBME data
void printInternalTempData()
{
  // temperature
  float temp_val = internalBME.readTemperature() - 0.5; //compensate sensor float
  char outstr[3];

  dtostrf(temp_val, 3, 1, outstr);
  lcd.print(outstr);
  lcd.print((char)223);

  //humidity
  lcd.setCursor(7, 0);
  temp_val = internalBME.readHumidity();
  dtostrf(temp_val, 2, 0, outstr);
  lcd.print(outstr);
  lcd.print("% ");

  // pressure
  temp_val = internalBME.readPressure() * 0.0075F;
  dtostrf(temp_val, 3, 0, outstr);
  lcd.print(outstr);
  lcd.print("mm");
}

// externalBME data
void printExternalTempData()
{
  // temperature
  float temp_val = externalBME.readTemperature() + 0.5; //compensate sensor float
  char outstr[3];

  dtostrf(temp_val, 3, 1, outstr);
  lcd.print(outstr);
  lcd.print((char)223);

  //humidity
  lcd.setCursor(7, 1);
  temp_val = externalBME.readHumidity();
  dtostrf(temp_val, 2, 0, outstr);
  lcd.print(outstr);
  lcd.print("% ");

  // pressure
  temp_val = externalBME.readPressure() * 0.0075F;
  dtostrf(temp_val, 3, 0, outstr);
  lcd.print(outstr);
  lcd.print("mm");
}

void loop()
{
  if (digitalRead(motionPin) == HIGH)
  {
    // show data
    lcd.on();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0); // column, row
    printInternalTempData();
    lcd.setCursor(0, 1);
    if (externalBME.begin(0x76))
    {
      printExternalTempData();
    } else {
      lcd.print("ext disconnected");
    }
    delay(5000);
  }
  else
  {
    // goto sleep
    lcd.off();
    lcd.noBacklight();
  }
}