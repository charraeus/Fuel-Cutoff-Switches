/***************************************************************************************************
 * @file main.cpp
 * @author Christian Harraeus (christian@harraeus.de)
 * @author Matthew Heironimus (Arduino Joystick Library, Dynamic HID)
 * 
 * @version 1.0
 * @date 2022-12-20
 * 
 * @brief Main program.
 * 
 * ## Introduction
 * 
 *  The Fuel-Selector-Switches by Sinan's [Etsy-Shop][shop] are driven by an *Sparkfun Micro Pro* device 
 *  which is compatible to an *Arduino Leonardo* device.  
 *  The Arduino Leonardo is recognised by the PC operation system as a game controller with the name 
 *  *Arduino Leonardo*. Connected to this Leonardo are two "buttons" which are actuated by the two Fuel 
 *  Selector Switches.
 *  
 *  I got an .ino file from the seller of the fuel selector switches. The 
 *  following address is an etsy address -- I don't have another one.  
 *  Sinan has asked to be sent the new software version.  
 *  Sinan <2_3c7aa44149d6c314fc53fb174d465ad073edbc46_1121328563999@convos.etsy.com>
 *  
 *  ## Features
 *  
 *  1. Expose only 4 joystick buttons.
 *  2. Expose these buttons as "Button 0" .. "Button 3".
 *  3. Do not expose any axis'.
 *  4. Do not expose any hat switch.
 *  5. Switch the 4 joystick buttons according to the algorithm below.
 *     * **Fuel Selector Switch #1** is set to *on*: show **joystick button 0 as pressed**,
 *       otherwise as depressed,
 *     * **Fuel Selector Switch #1** is set to *off*: show **joystick button 1 as pressed**,
 *       otherwise as depressed,
 *     * **Fuel Selector Switch #2** is set to *on*: show **joystick button 2 as pressed**,
 *       otherwise as depressed,
 *     * **Fuel Selector Switch #2** is set to *off*: show **joystick button 3 as pressed**,
 *       otherwise as depressed.
 *  6. The board in use is @em Sparkfun Micro Pro which is compatible to the Arduino Leonardo.
 *  7. Works with all (flight) simulators which can detect a joystick.
 * 
 * ![Controller Properties](./Fuel-Selector-Properties.png "Properties Window in Windows 10")
 *  > Note: The internal joystick button count starts at zero (0), but in the Windows properties
 *  > window the count starts with 1.
 *  
 *  ## Wiring
 *  
 *  1. **Fuel Selector Switch #1** is connected to **Arduino Pin 3** of Micro Pro board.
 *  2. **Fuel Selector Switch #2** is connected to **Arduino Pin 2** of Micro Pro board. 
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
 *      debounce new switch state (wait for 8 milliseconds until new state is stabilised);
 *  endif
 *  
 *  **Fuel Selector Switch 1**  
 *  ```
 *  if Fuel Selector Switch is set to upper position (Arduino pin 3 = *on*) then
 *      set joystick button 1 to *off*;
 *      set joystick button 0 to *on*;
 *  endif
 *  
 *  if Fuel Selector Switch is set to down position (Arduino pin 3 = *off*) then
 *      set joystick button 0 to *off*;
 *      set joystick button 1 to *on*;
 *  endif
 *  ```
 *  
 *  **Fuel Selector Switch 2**  
 *  Analogous to Fuel Selector Switch 1, but with joystick buttons 2 and 3 and Arduino pin 2.
 * 
 *  ## Dependencies
 *  1. Joystick-Library: https://github.com/MHeironimus/ArduinoJoystickLibrary
 *  2. DynamicHID-Library: included in 1. 
 * 
 **************************************************************************************************/


#include <Arduino.h>
#include <Joystick.h>

// @brief  Constants for fuel selector switch #1
const int SELECTOR_SWITCH_1_PIN = 3;            ///< Fuel Selector Switch 1 is connected to pin 3
const uint8_t SELECTOR_SWITCH_1_ON_BUTTON = 0;  ///< Button number to trigger when Switch 1 is set to on
const uint8_t SELECTOR_SWITCH_1_OFF_BUTTON = 1; ///< Button number to trigger when Switch 1 is set to off

// @brief Constants for fuel selector switch #2
const int SELECTOR_SWITCH_2_PIN = 2;            ///< Fuel Selector Switch 2 is connected to pin 2
const uint8_t SELECTOR_SWITCH_2_ON_BUTTON = 2;  ///< Button number to trigger when Switch 2 is set to on
const uint8_t SELECTOR_SWITCH_2_OFF_BUTTON = 3; ///< Button number to trigger when Switch 2 is set to off

/***************************************************************************************************
 * @brief Pin-object - Holds all necessary data and provides the functionality.
 * 
 */
class ArduinoPin {
public:
    ArduinoPin(uint8_t pin, uint8_t joystickOnButton, uint8_t joystickOffButton);  ///< Constructor
    uint8_t readSwitchPosition() const;   ///< Read the switch position connected to this pin
    void setState(uint8_t newState);      ///< Set new pin state
    uint8_t getState() const;             ///< Returns the current pin state
    uint8_t getOnButtonNumber() const;    ///< Returns the number of the joystick button to set for switch on
    uint8_t getOffButtonNumber() const;   ///< Returns the number of the joystick button to set for switch off
    bool isChanged() const;               ///< Returns @em true if pin state has changed, otherwise @em false

private:
    uint8_t pin;                            ///< Arduino pin to which a fuel selector switch is connected
    uint8_t currentState;                   ///< Current state (on, off) of the Arduino pin (hardware)
    uint8_t lastState;                      ///< Previous state (on, off) of the Arduino pin (hardware)
    uint8_t joystickOnButton;               ///< Joystick button number to set when switch is set to on
    uint8_t joystickOffButton;              ///< Joystick button number to set when switch is set to off
    bool changed;                           ///< @em true if the pin state has changed, otherwise @em false
    const unsigned long DEBOUNCE_TIME = 8;  ///< Time for debouncing the switch in milliseconds
    unsigned long stateChangeTime;          ///< Time when the pin last changed state
};

/***************************************************************************************************
 * Methods for pin object
 **************************************************************************************************/

/**
 * @brief Construct a new ArduinoPin:: ArduinoPin object
 * 
 * @param pin 
 * @param joystickOnButton 
 * @param joystickOffButton 
 */
ArduinoPin::ArduinoPin(const uint8_t pin, 
                       const uint8_t joystickOnButton, 
                       const uint8_t joystickOffButton) {
    this->pin = pin;
    this->joystickOnButton = joystickOnButton;
    this->joystickOffButton = joystickOffButton;
    this->lastState = 0;
    this->changed = true;
    this->stateChangeTime = millis();
    pinMode(pin, INPUT_PULLUP);
    setState(readSwitchPosition());
}

/**
 * @brief Reads the state of the hardware Arduino pin.
 * 
 * @return uint8_t Value @em 1 is on, @em 0 is off
 */
uint8_t ArduinoPin::readSwitchPosition() const {
    return static_cast<uint8_t>(! static_cast<bool>(digitalRead(pin)));
} 

/**
 * @brief Debounce and set the new state of the pin.
 * 
 * @param newState 
 */
void ArduinoPin::setState(const uint8_t newState) {
    if (newState != lastState) {
        // new state for this pin detected
        // debounce the pin change
        if (millis() - stateChangeTime >= DEBOUNCE_TIME) {
            stateChangeTime = millis();     // when the pin state changes
            lastState = currentState;       // remember for next time 
            currentState = newState;
            changed = true;
        }
    } else {
        // no state change detected for this pin
        changed = false;
    }
}

inline uint8_t ArduinoPin::getState() const {
    return currentState;
}

inline bool ArduinoPin::isChanged() const {
    return changed;
}

inline uint8_t ArduinoPin::getOnButtonNumber() const {
    return joystickOnButton;
}

inline uint8_t ArduinoPin::getOffButtonNumber() const {
    return joystickOffButton;
}

/***************************************************************************************************
 * @brief Array with all pin with connected switches.
 * 
 */
ArduinoPin arduinoPins[] = {
                             {
                                SELECTOR_SWITCH_1_PIN, 
                                SELECTOR_SWITCH_1_ON_BUTTON, 
                                SELECTOR_SWITCH_1_OFF_BUTTON
                             },
                             { 
                                SELECTOR_SWITCH_2_PIN,
                                SELECTOR_SWITCH_2_ON_BUTTON, 
                                SELECTOR_SWITCH_2_OFF_BUTTON
                             }
};


/***************************************************************************************************
 * @brief Initialise Joystick object: Show only 4 buttons and no axis.
 * 
 *  Initialise with the following values:
 *  * JOYSTICK_DEFAULT_REPORT_ID, (defined in Joystick.h)
 *  * JOYSTICK_TYPE_JOYSTICK,  (defined in Joystick.h)
 *  * buttonCount = 4,
 *  * hatSwitchCount = 0,
 *  * includeXAxis = false,
 *  * includeYAxis = false,
 *  * includeZAxis = false,
 *  * includeRxAxis = false,
 *  * includeRyAxis = false,
 *  * includeRzAxis = false,
 *  * includeRudder = false,
 *  * includeThrottle = false,
 *  * includeAccelerator = false,
 *  * includeBrake = false,
 *  * includeSteering = false).
 */
Joystick_ joystick = {
            JOYSTICK_DEFAULT_REPORT_ID, // JOYSTICK_DEFAULT_REPORT_ID,
            JOYSTICK_TYPE_JOYSTICK,     // JOYSTICK_TYPE_JOYSTICK,
            // buttonCount = 4: per pin two joystick buttons
            static_cast<uint8_t>(sizeof(arduinoPins)/sizeof(arduinoPins[0]) * 2),
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


/***************************************************************************************************
 * @brief Set joystick buttons according to the fuel selector switch positions.
 * 
 * @param pin Pin-object
 */
void setJoystickButtons(ArduinoPin &pin) {
    uint8_t newState = pin.getState();
    if (newState == 1) {
         // newState is 1 ==> fuel switch is set to up position (on)
        joystick.setButton(pin.getOffButtonNumber(), 0);
        joystick.setButton(pin.getOnButtonNumber(), newState);
    } else {
        // newState is 0 ==> fuel switch is set to down position (off)
        joystick.setButton(pin.getOnButtonNumber(), newState);
        joystick.setButton(pin.getOffButtonNumber(), 1);
    }
}


/***************************************************************************************************
 * @brief Setup of @em Arduino @em Leonardo / @em Sparkfun @em Micro @em Pro
 * 
 */
void setup() {
    /// Initialize Joystick Library
    joystick.begin();
    
    /// Initialise joystick buttons
    for (auto &pin : arduinoPins) {
        /// set the joystick buttons according to the initial pin status.
        /// the initial pin status is read in the pin-constructor.
        setJoystickButtons(pin);
    }
}


/***************************************************************************************************
 * @brief Endless loop of @em Arduino @em Leonardo / @em Sparkfun @em Micro @em Pro.
 * 
 * Read state (on, off) for all defined pins and
 * set the joystick buttons accordingly
 */
void loop() {
    /// repeat for all defined pins
    for (auto &pin : arduinoPins) {
        /// read and set the pin status
        pin.setState(pin.readSwitchPosition());
        if (pin.isChanged()) {
            /// if pin status has changed change the status of the joystick buttons
            setJoystickButtons(pin);
        }
    }

    /// Wait 50 milliseconds before next loop
    delay(50);
}
