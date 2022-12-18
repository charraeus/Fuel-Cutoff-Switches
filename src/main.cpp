/***************************************************************************************************
 * @file main.cpp
 * @author Christian Harraeus (christian@harraeus.de)
 * @author Matthew Heironimus (Arduino Joystick Library, Dynamic HID)
 * 
 * @version 0.2
 * @date 2022-12-18
 * 
 * @brief Main program.
 * 
 * ## Introduction
 * 
 * The Arduino Leonardo is recognised by Windows as a game controller with the name "Arduino Leonardo". 
 * 
 * I got an .ino file from the seller of the fuel selector switches. The 
 * following address is an etsy address -- I don't have another one.  
 * Sinan has asked to be sent the new software version.  
 * Sinan <2_3c7aa44149d6c314fc53fb174d465ad073edbc46_1121328563999@convos.etsy.com>
 *  
 * ## Actual state
 * 
 * The fuel selector switches are passed as joystick buttons.  
 * The problem is that there is no mechanism in X-Plane to fire a trigger when a 
 * joystick button is released. Therefore the following software solution in the Arduino 
 * would be helpful:
 *  
 * 1. when the fuel selector is switched on (i.e. switch up) - as before - a BTN is triggered, 
 * in my case these are BTN3 resp. BTN4.
 * 2. when switching off, another BTN is triggered, so for example BTN5 or BTN.
 * This way there are two joystick buttons that can be assigned a function in X-Plane.
 *  
 *  ## Target state
 *
 *  **Algorithm:**  
 *  **As up to now:**
 *  * Joystick button is pressed --> the Arduino sets BTN3 resp. BTN4 to "active",
 *  * joystick button is released --> the Arduino sets BTN3 resp. BTN4 to "inactive".
 *  
 *  **Additionally:**
 *  * Joystick button is pressed --> the Arduino sets BTN5 or BTN6 to "inactive".
 *  * Joystick button is released --> the Arduino sets BTN5 or BTN6 to "active".
 * 
 *  ## Next steps
 *  
 *  @todo ~~1. Arduino-Leonardo Entwicklungsumgebung aufsetzen.~~
 *  @todo 2. Auf dem Leonardo befindliche Firmware auslesen und als Backup archivieren.
 *  @todo 3. Diese \.ino-Datei übersetzen und auf den Leonardo aufspielen und testen.
 *  @todo 4. Dann erst mit der Softwareänderung beginnen.
 * 
 *  ## Further information
 *  * Used Joystick-Library: https://github.com/MHeironimus/ArduinoJoystickLibrary
 * 
 **************************************************************************************************/


#include <Arduino.h>
#include <Joystick.h>

Joystick_ Joystick;

/// @brief setup des Arduino Leonardo
void setup() {
  // Initialize Button Pins
  // for digitalRead pins A0-A5 = 18-23
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
}

/// defining the total [#] of buttons and their pins
const int ButtonToPinMap[22] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,18,19,20,21,22};

/// vorheriger Status des Buttons (?) --> ist noch zu verifizieren
int lastButtonState[22] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/// @brief loop des Arduino
void loop() {

  for (int index = 0; index < 22; index++)
  {
    int currentButtonState = !digitalRead(ButtonToPinMap[index]);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }

  delay(50);
}
