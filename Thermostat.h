#ifndef THERMOSTAT_H
#define THERMOSTAT_H

class Thermostat {
  private:
    bool switchState;
    float temperature;
  public:
    Thermostat(float temp, bool ss);
    void switchButton();
    void setTemperature(const float newTemp);
    bool getState() const;
    float getTemperature() const;
};

#endif
