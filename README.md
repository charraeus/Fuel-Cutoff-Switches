@todo Supplement this README-file.

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
