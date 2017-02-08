#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include "LowPower.h"

// (c) Anton Golubev 2017

#define MAXCS   10
Adafruit_MAX31855 thermocouple(MAXCS);

void setup() {
  while (!Serial);

  Serial.begin(115200);

  Serial.println("MAX31855 test");
}

void loop() {
	LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
   Serial.print("Internal Temp = ");
   Serial.println(thermocouple.readInternal());

   double c = thermocouple.readCelsius();
   if (isnan(c)) {
     Serial.println("Something wrong with thermocouple!");
   } else {
     Serial.print("C = ");
     Serial.println(c);
   }
   //Serial.print("F = ");
   //Serial.println(thermocouple.readFarenheit());

   delay(1000);
}
