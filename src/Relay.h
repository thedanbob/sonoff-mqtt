#ifndef RELAY_H
#define RELAY_H

#include <Ticker.h>
#include "config.h"

class Relay {
  public:
    Relay();
    void setup(bool &updateMode);
    bool getState(size_t ch);
    void setState(size_t ch, bool on, bool write = true);
    bool stateHasChanged(size_t ch);

  private:
    static const size_t _buttonPin[CHANNELS];
    static const size_t _relayPin[CHANNELS];
    static const bool _restoreState[CHANNELS];

    bool _lastState[CHANNELS]; // Last state reported
    unsigned long _btnCount[CHANNELS];
    Ticker _btnTimer[CHANNELS];
};

#endif
