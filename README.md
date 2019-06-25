# LuxP1 - Luxembourg Smart Meter Reader for ESP8266/8285

This repository contains soft- and hardware files to send [Luxembourg smart meter](https://smarty.creos.net) readings via WiFi to an MQTT server. 

More information on this device and the P1 port, which is an open interface for meter readings:

* [P1 Port Specifications](https://smarty.creos.net/wp-content/uploads/P1PortSpecification.pdf)
* [Dutch Smart Meter Requirements](https://smarty.creos.net/wp-content/uploads/DutchSmartMeterRequirements.pdf)

## Preparation

Request from Creos (customer.care@creos.net) or your local grid provider your P1 encryption key by stating your address and smart meter number

## Software

Checkout the project and modify `config.h` to your needs. 

Then make sure to build for increased MQTT package size (Using `-DMQTT_MAX_PACKET_SIZE=2048` or directly editing the PubSubClient.h). Otherwise packages will be truncated.

## Hardware

(tbd) Fritzing files

## License

Copyright (c) B. Wilbertz. All rights reserved.

Licensed under the [MIT](LICENSE.txt) license.
