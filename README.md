# README

@tableofcontents

## Introduction

The Fuel-Selector-Switches by Sinan's [Etsy-Shop][shop] are driven by an *Sparkfun Micro Pro* device 
which is compatible to an *Arduino Leonardo* device.  
The Arduino Leonardo is recognised by the PC operation system as a game controller with the name 
*Arduino Leonardo*. Connected to this Leonardo are two "buttons" which are actuated by the two Fuel 
Selector Switches.

[shop]: https://www.etsy.com/de/shop/Homecockpit?utm_source=transactional&utm_medium=email&utm_campaign=convo_notifications_010170_10683759063_0_0&campaign_label=convo_notifications&utm_content=&email_sent=1670917211&euid=krvzIIx63gGeMLYBZhJNqdGjoi3j&eaid=1118096026825&x_eaid=94976db736

## Features

1. Expose only 4 joystick buttons.
2. Expose these buttons as "Button 0" .. "Button 3".
3. Do not expose any axis'.
4. Do not expose any hat switch.
5. Switch the 4 joystick buttons according to the algorithm below.
   * **Fuel Selector Switch #1** is set to *on*: show **joystick button 0 as pressed**, otherwise as depressed,
   * **Fuel Selector Switch #1** is set to *off*: show **joystick button 1 as pressed**, otherwise as depressed,
   * **Fuel Selector Switch #2** is set to *on*: show **joystick button 2 as pressed**, otherwise as depressed,
   * **Fuel Selector Switch #2** is set to *off*: show **joystick button 3 as pressed**, otherwise as depressed.
6. The board in use is @em Sparkfun Micro Pro which is compatible to the Arduino Leonardo.
7. Works with all (flight) simulators which can detect a joystick.

## Basic Algorithm
 
* Joystick button is pressed:
  1. the Arduino sets the joystick button, which indicates the off-position of the switch 
     to *not pressed/inactive/off*.
  2. the Arduino sets the joystick button, which indicates the on-position of the switch 
     to *pressed/active/on*.
* Joystick button is released:
  1. the Arduino sets the joystick button, which indicates the on-position of the switch 
     to *not pressed/inactive/off*.
  2. the Arduino sets the joystick button, which indicates the off-position of the switch 
     to *pressed/active/on*.

## Wireing

1. **Fuel Selector Switch #1** is connected to **Arduino Pin 3** of Micro Pro board.
2. **Fuel Selector Switch #2** is connected to **Arduino Pin 2** of Micro Pro board. 

## Dependencies

1. **Arduino Joystick Library** by Matthew Heironimus  
   available on [Github][1].
2. **DynamicHID library** by Arduino LLC, modified by Matthew Heironimus  
   included in 1.
3. **Hardware**: Fuel Selector Switches connected to Micro Pro board:
   * Fuel Selector Switch 1 --> Sparkfun Micro Pro pin 3
   * Fuel Selector Switch 2 --> Sparkfun Micro Pro pin 2

[1]: https://github.com/MHeironimus/ArduinoJoystickLibrary "Joystick Library by MHeironimus on Github"

### Installation of Libraries for PlatformIO

See [here][2] for a detailed description.

* Open *platformio.ini*, a project configuration file located in the root of PlatformIO project.
* Add the following line to the lib_deps option of [env:] section:  
`mheironimus/Joystick@^2.1.1`
* Build a project, PlatformIO will automatically install dependencies.

[2]: https://registry.platformio.org/libraries/mheironimus/Joystick/installation "PlatformIO - Library Installation"
