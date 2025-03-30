#include "Lights.h"

Lights::Lights(bool ss) {
    switchState = ss;
}

void Lights::changeState() {
    switchState = !switchState;
}

bool Lights::getState() const {
    return switchState;
}



