#ifndef SPEAKER_H
#define SPEAKER_H

class Speaker {
private:
    bool switchState;
    int volume;
public:
    Speaker(int volume, bool ss);
    void switchButton();
    void setVolume(const int newTemp);
    bool getState() const;
    float getVolume() const;
};

#endif
