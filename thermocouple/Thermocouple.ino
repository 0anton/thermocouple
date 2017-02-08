#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include "LowPower.h"
#include "PCD8544_SPI.h"

#define USE_FRAME_BUFFER

PCD8544_SPI_FB lcd;


// (c) Anton Golubev 2017

#define MAXCS   10
Adafruit_MAX31855 thermocouple(MAXCS);

void setup() {
  while (!Serial);
  Serial.begin(115200);
  Serial.println("MAX31855 test");
  lcd.begin();
  lcd.print(F("Welcome to thermosensor"));
  lcd.renderAll();
  LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
}

void loop() {
	size_t len=0;

	LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
	lcd.clear();

   Serial.print("Internal Temp = ");
   Serial.println(thermocouple.readInternal());

   len += lcd.print(F("Internal Temp = "));
   len += lcd.println(thermocouple.readInternal());

   double c = thermocouple.readCelsius();
   if (isnan(c)) {
     Serial.println("Something wrong with thermocouple!");
     len += lcd.print(F("Something wrong with thermocouple!"));
   } else {
     Serial.print("C = ");
     len += lcd.print(F("C = "));
     Serial.println(c);
     len += lcd.println(c);
   }

   lcd.renderString(0, 0, len);
}
