//
// Created by ririio on 29/03/25.
//

#ifndef LIGHTS_H
#define LIGHTS_H

class Lights {
    private:
        bool switchState;
    public:
        Lights(bool ss);
        void changeState();
        bool getState() const;
};

#endif //LIGHTS_H
