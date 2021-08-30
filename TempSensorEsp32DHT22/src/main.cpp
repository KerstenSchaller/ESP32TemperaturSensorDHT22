

#include "Arduino.h"
#include "Sensor.hpp"

SensorDHT22 sensor(4);

void setup() {
  //sensor = SensorDHT22(4);
  Serial.begin(115200);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  sensor.readValues();


}
