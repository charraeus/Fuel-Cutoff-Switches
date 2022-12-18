@tableofcontents

## Current Status

The Fuel-Selector-Switches by Sinan's [Etsy-Shop][shop] are driven by an Arduino Leonardo device. 
The Arduino Leonardo is recognised by Windows as a game controller with the name "Arduino Leonardo". Connected to this Leonardo are two "buttons" which are actuated by the Fuel Selector Switches.

The problem is that there is no mechanism in X-Plane to fire a trigger when a 
joystick button is released. Therefore the following software solution in the Arduino 
would be helpful:

1. When the fuel selector is switched on (i.e. switch up) - as before - a BTN is triggered, 
   in my case these are BTN3 resp. BTN4.
2. When switching off, another BTN is triggered, so for example BTN5 or BTN.
This way there are two joystick buttons that can be assigned a function in X-Plane.

[shop]: https://www.etsy.com/de/shop/Homecockpit?utm_source=transactional&utm_medium=email&utm_campaign=convo_notifications_010170_10683759063_0_0&campaign_label=convo_notifications&utm_content=&email_sent=1670917211&euid=krvzIIx63gGeMLYBZhJNqdGjoi3j&eaid=1118096026825&x_eaid=94976db736

## Target Status

The Leonardo operates two buttons per Fuel Selector Switch towards Windows / X-Plane.

**Algorithm:**  
**As up to now:**
* Joystick button is pressed --> the Arduino sets BTN3 resp. BTN4 to "active",
* joystick button is released --> the Arduino sets BTN3 resp. BTN4 to "inactive".

**Additionally:**
* Joystick button is pressed --> the Arduino sets BTN5 or BTN6 to "inactive".
* Joystick button is released --> the Arduino sets BTN5 or BTN6 to "active".

## Dependencies

### Libraries

1. **Arduino Joystick Library** by Matthew Heironimus
   * available on [Github][1]
2. **DynamicHID library** by Arduino LLC, modified by Matthew Heironimus
   * included in 1.
3. **Hardware**: Fuel Selector Switches connected to Leonardo:
   * Fuel Selector Switch 1 --> Leonardo Pin 2 ==> Button 3
   * Fuel Selector Switch 2 --> Leonardo Pin 3 ==> Button 4
   @todo to be verified

[1]: https://github.com/MHeironimus/ArduinoJoystickLibrary "Joystick Library by MHeironimus on Github"

### Installation of Libraries for PlatformIO

See [here][2].

#### Depend on it

* Open *platformio.ini*, a project configuration file located in the root of PlatformIO project.
* Add the following line to the lib_deps option of [env:] section:  
`mheironimus/Joystick@^2.1.1`
* Build a project, PlatformIO will automatically install dependencies.

#### Include it

* Joystick library provides the following header files that can be included in your project:  
  DynamicHID.hJoystick.h  
  `#include <DynamicHID.h>`

#### Command Line Interface (alternative to "Depend on it")

* Open PlatformIO Core CLI
* Change directory (cd) to the PlatformIO project where platformio.ini is located.
* Copy the following pio pkg install command and paste into the CLI shell, press Enter:
`pio pkg install --library "mheironimus/Joystick@^2.1.1"`

[2]: https://registry.platformio.org/libraries/mheironimus/Joystick/installation "PlatformIO - Library Installation"
