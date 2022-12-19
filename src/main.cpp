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
 *  ## Requirements
 *  
 *  1. Expose only 4 joystick buttons.
 *  2. Expose these buttons as "Button 0" .. "Button 3".
 *  3. Do not expose any axis'.
 *  4. Do not expose any hat switch.
 *  5. Switch the 4 joystick buttons according to the algorithm below.
 *     * **Fuel Selector Switch #1** is set to *on*: show **joystick button 0 as pressed**, otherwise as depressed,
 *     * **Fuel Selector Switch #1** is set to *off*: show **joystick button 1 as pressed**, otherwise as depressed,
 *     * **Fuel Selector Switch #2** is set to *on*: show **joystick button 2 as pressed**, otherwise as depressed,
 *     * **Fuel Selector Switch #2** is set to *off*: show **joystick button 3 as pressed**, otherwise as depressed.
 *  6. The board in use is @em Sparkfun Micro Pro which is compatible to the Arduino Leonardo.
 *  
 *  ## Wireing
 *  
 *  1. **Fuel Selector Switch #1** is connected to **"Arduino Pin" 3** of Micro Pro board.
 *  2. **Fuel Selector Switch #2** is connected to **"Arduino Pin" 2** of Micro Pro board. 
 *  
 *  ## Algorithm for Button-Setting
 *  
 *  ### Initialisation
 *  
 *  Set joystick buttons according to position of the Fuel Selector Switches;
 *  
 *  ### Fuel Selector Switch State Change
 *  
 *  if a Fuel Selector Switch position is changed then
 *      debounce new switch state (wait for max. 8 milliseconds until new state is stabilised);
 *  endif
 *  
 *  **Fuel Selector Switch 1**  
 *  ```
 *  if Fuel Selector Switch is set to upper position (Arduino pin 3 = "on") then
 *      set joystick button 1 to off;
 *      set joystick button 0 to on;
 *  endif
 *  
 *  if Fuel Selector Switch is set to down position (Arduino pin 3 = "off") then
 *      set joystick button 0 to off;
 *      set joystick button 1 to on;
 *  endif
 *  ```
 *  
 *  **Fuel Selector Switch 2**  
 *  Analogous to Fuel Selector Switch 1, but with joystick buttons 2 and 3 and Pin 2.
 * 
 *  ## Further information
 *  * Used Joystick-Library: https://github.com/MHeironimus/ArduinoJoystickLibrary
 * 
 **************************************************************************************************/


#include <Arduino.h>
#include <Joystick.h>

/// @brief  Constants for fuel selector switch #1
const int SELECTOR_SWITCH_1_PIN = 3;        /// Fuel Selector Switch 1 is connected to pin 3
const uint8_t SELECTOR_SWITCH_1_ON_BUTTON = 0;  /// Button number to trigger when Switch 1 is set to on
const uint8_t SELECTOR_SWITCH_1_OFF_BUTTON = 1; /// Button number to trigger when Switch 1 is set to off

/// @brief Constants for fuel selector switch #2
const int SELECTOR_SWITCH_2_PIN = 2;        /// Fuel Selector Switch 2 is connected to pin 2
const uint8_t SELECTOR_SWITCH_2_ON_BUTTON = 2;  /// Button number to trigger when Switch 2 is set to on
const uint8_t SELECTOR_SWITCH_2_OFF_BUTTON = 3; /// Button number to trigger when Switch 2 is set to off

/// @brief Array of pin numbers to which switches are connected.
/// @note PINS must be filled with pin numbers in ascending order
const int PIN_COUNT = 2;                    /// Number of active pins
const int PINS[PIN_COUNT] = { SELECTOR_SWITCH_2_PIN,
                              SELECTOR_SWITCH_1_PIN, 
                            };   /// Pin numbers to which switches are connected

/// @brief Array of last states of the pins
uint8_t lastPinState[PIN_COUNT] = {0, 0};

/// @brief Initialise Joystick object: Show only 4 buttons.
Joystick_ Joystick = {
                      JOYSTICK_DEFAULT_REPORT_ID,       //JOYSTICK_DEFAULT_REPORT_ID,
                      JOYSTICK_TYPE_JOYSTICK,           // JOYSTICK_TYPE_JOYSTICK,
                      PIN_COUNT * 2,    // buttonCount = 4,
                      0,                // hatSwitchCount = 0,
                      false,            // includeXAxis = false,
                      false,            // includeYAxis = false,
                      false,            // includeZAxis = false,
                      false,            // includeRxAxis = false,
                      false,            // includeRyAxis = false,
                      false,            // includeRzAxis = false,
                      false,            // includeRudder = false,
                      false,            // includeThrottle = false,
                      false,            // includeAccelerator = false,
                      false,            // includeBrake = false,
                      false             // includeSteering = false).
};


/// @brief Setup of @em Arduino @em Leonardo / @em Sparkfun @em Micro @em Pro
void setup() {
    /// Initialize Arduino pins
    for (const auto &pin : PINS) {
        pinMode(pin, INPUT_PULLUP);
    }

    /// Initialize Joystick Library
    Joystick.begin();
}

/// @brief Endless loop of @em Arduino @em Leonardo / @em Sparkfun @em Micro @em Pro.
/// 
/// Read state (on, off) for all defined pins and
/// set the joystick buttons accordingly
void loop() {
    /// repeat for all defined pins
    for (const auto &pin : PINS) {
        /// read the pin status
        int currentPinState = !digitalRead(PINS[pin - PIN_COUNT]);
        /// Memorize the pin status in @em lastPinState and
        /// set the joystick buttons
        if (currentPinState != lastPinState[pin - PIN_COUNT]) {
            lastPinState[pin - PIN_COUNT] = currentPinState;
            switch (pin) {
                case SELECTOR_SWITCH_1_PIN: {
                    if (currentPinState == 1) {
                        // Switch #1 is set to on (up position)
                        Joystick.setButton(SELECTOR_SWITCH_1_OFF_BUTTON, 0);
                        Joystick.setButton(SELECTOR_SWITCH_1_ON_BUTTON, 1);
                    } else {
                        // Switch #1 is set to off (down position)
                        Joystick.setButton(SELECTOR_SWITCH_1_ON_BUTTON, 0);
                        Joystick.setButton(SELECTOR_SWITCH_1_OFF_BUTTON, 1);
                    }
                    break;
                }
                case SELECTOR_SWITCH_2_PIN: {
                    if (currentPinState == 1) {
                        // Switch #2 is set to on (up position)
                        Joystick.setButton(SELECTOR_SWITCH_2_OFF_BUTTON, 0);
                        Joystick.setButton(SELECTOR_SWITCH_2_ON_BUTTON, 1);
                    } else {
                        // Switch #2 is set to off (down position)
                        Joystick.setButton(SELECTOR_SWITCH_2_ON_BUTTON, 0);
                        Joystick.setButton(SELECTOR_SWITCH_2_OFF_BUTTON, 1);
                    }
                    break;
                }
                default: {
                    ; // this should never happen
                }
            }
        }
    }

    /// Wait 50 milliseconds before next loop
    delay(50);
}
