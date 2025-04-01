#include "Speaker.h"

Speaker::Speaker(int vol, bool ss = false) {
	switchState = ss;
	volume = vol;
}

void Speaker::switchButton() {
	switchState = !switchState;
}

void Speaker::setVolume(const int newVol) {
	volume = newVol;
}

float Speaker::getVolume() const {
	return volume;
}

bool Speaker::getState() const {
	return switchState;
}
