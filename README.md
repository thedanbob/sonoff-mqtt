# Sonoff-MQTT (Home Assistant)

This firmware is intended to allow a Sonoff Basic/4CH to be used as an MQTT light in Home Assistant. `platformio.ini` shows how to configure the project for multiple devices. The firmware uses [MQTT discovery](https://www.home-assistant.io/docs/mqtt/discovery/) so no special configuration in Home Assistant is necessary; just set up the MQTT integration.

Configuration values can be found in [config.h](include/config.h). It is better to define required constants in `platformio.ini` by passing additional build flags:

```ini
build_flags =
  '-DMQTT_SERVER="192.168.0.2"' ; string constants must be wrapped in single quotes
  -DMQTT_PORT=1883 ; integer and boolean constants don't need quotes
  ; etc
```
