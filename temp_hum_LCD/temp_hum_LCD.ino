#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
#define I2C_ADDR 0x3F
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

long waitFor = 1800000; //30' 1800000
long last = millis() - waitFor;
String line1 = "";
String line2 = "";

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C  lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

void setup()
{
  dht.begin();
  lcd.begin (16, 2);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
}

void temp() {
  float t = dht.readTemperature();
  line1 = line1 + String(t, 1) + (char)223 + " ";
}

void hum() {
  float h = dht.readHumidity();
  line2 = line2 + String(h, 1) + "% ";
}

void loop()
{
  if (millis() - last > waitFor) {
    temp();
    hum();
    last = millis();
    lcd.home();
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }
}
