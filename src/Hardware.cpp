#include <EEPROM.h>
#include "Hardware.h"

const size_t Hardware::_buttonPin[]{BUTTONS};
const size_t Hardware::_relayPin[]{RELAYS};
const bool Hardware::_restoreState[]{RESTORE_STATES};

Hardware::Hardware() :
  _lastState{SLICE(false, false, false, false)},
  _btnCount{SLICE(0, 0, 0, 0)},
  _btnTimer{SLICE(Ticker{}, Ticker{}, Ticker{}, Ticker{})}
{}

void Hardware::setup(bool &updateMode) {
  EEPROM.begin(CHANNELS);

  for (size_t ch{0}; ch < CHANNELS; ch++) {
    // Initialize relays
    pinMode(_relayPin[ch], OUTPUT);
    setState(ch, _restoreState[ch] ? EEPROM.read(ch) : LOW, false);
    _lastState[ch] = getState(ch);

    // Initialize buttons
    pinMode(_buttonPin[ch], INPUT);

    // Put device in update mode if first button is held while device starts
    if (ch == 0 && !digitalRead(_buttonPin[ch])) {
      updateMode = true;
      return;
    }

    _btnTimer[ch].attach_ms(50, [this, ch]() {
      if (!digitalRead(_buttonPin[ch])) { // LOW = pressed
        _btnCount[ch]++;
      } else {
        if (_btnCount[ch] > 1) {
          setState(ch, !getState(ch)); // Toggle relay
          _btnCount[ch] = 0;
        }
      }
    });
  }
}

bool Hardware::getState(size_t ch) {
  return digitalRead(_relayPin[ch]);
}

void Hardware::setState(size_t ch, bool on, bool write) {
  digitalWrite(_relayPin[ch], on);

  if (_restoreState[ch] && write) {
    EEPROM.write(ch, on);
    EEPROM.commit();
  }
}

bool Hardware::stateHasChanged(size_t ch) {
  bool newState = getState(ch);
  if (_lastState[ch] != newState) {
    _lastState[ch] = newState;
    return true;
  }
  return false;
}
