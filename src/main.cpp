#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <DHT.h>;

const int motionPin = 8;
Adafruit_BME280 bme;

//Constants
#define dhtPIN 2          // what pin we're connected to
#define DHTTYPE DHT22     // DHT 22  (AM2302)
DHT dht(dhtPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

void setup()
{
  Serial.begin(9600);
  pinMode(motionPin, INPUT);

  bool status = bme.begin();
  if (!status)
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  dht.begin();
}

void loop()
{
  if (digitalRead(motionPin) == HIGH)
  {
    // show data
    printHomeTempData();
  }
  else
  {
    // goto sleep
  }
}

// BME 280 data
void printHomeTempData()
{
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
  delay(1000);
}

// DHT22 data
void printHomeTempData()
{
  Serial.print("Humidity: ");
  Serial.print(dht.readHumidity());
  Serial.print(" %, Temp: ");
  Serial.print(dht.readTemperature());
  Serial.println(" Celsius");
}