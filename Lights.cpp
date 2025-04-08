#include "Lights.h"

Lights::Lights(bool ss, int b) {
    switchState = ss;
    brightness = b;
}

void Lights::changeState() {
    switchState = !switchState;
}

void Lights::setBrightness(const int newBright) {
    brightness = newBright;
}

int Lights::getBrightness() const {
    return brightness;
}

bool Lights::getState() const {
    return switchState;
}
