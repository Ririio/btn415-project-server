#include "Thermostat.h"

Thermostat::Thermostat(float temp, bool ss = false) {
  switchState = ss;
  temperature = temp;
}

void Thermostat::switchButton(){
  switchState = !switchState;
}

void Thermostat::setTemperature(const float newTemp){
  temperature = newTemp;
}

float Thermostat::getTemperature() const {
  return temperature;
}

bool Thermostat::getState() const {
  return switchState;
}
