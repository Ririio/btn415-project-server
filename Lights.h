//
// Created by ririio on 29/03/25.
//

#ifndef LIGHTS_H
#define LIGHTS_H

class Lights {
    private:
        bool switchState;
        int brightness;
    public:
        Lights(bool ss, int b);
        void changeState();
        void setBrightness(const int newBright);
        int getBrightness() const;
        bool getState() const;
};

#endif //LIGHTS_H
