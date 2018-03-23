# ASME 2018 Goalie Team
This is the code for an omniwheel goalie.

The other code is for little distractor robot that is controlled by an
android phone.

## Omniwheel Instructions
The omniwheel robot is meant to be used with an [Arduino Mega](https://www.amazon.com/Elegoo-EL-CB-003-ATmega2560-ATMEGA16U2-Arduino/dp/B01H4ZLZLQ/ref=sr_1_1_sspa?s=electronics&ie=UTF8&qid=1521789455&sr=1-1-spons&keywords=arduino+mega&psc=1) containing a USB
Host Shield and [this library](https://github.com/felis/USB_Host_Shield_2.0)

**Step 1 is only done when pairing with that specific controller for the first time**
1. With code on a powered Arduino Mega, plug PS3 controller into the USB shield.
This registers the PS3 controller with the shield.
- Unplug PS3 Controller from shield, and plug Bluetooth Dongle into the shield.
- Press PS3 home button, wait for PS3 controller to connect.
- Upon connection, press the PS3 home button once again to activate the Arduino
movement
