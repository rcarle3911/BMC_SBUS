#include <BMC_SBUS.h>

// Pass pointers for serial ports to the BMC bus
BMC_SBUS sbus1(&Serial);
BMC_SBUS sbus2(&Serial1);
BMC_SBUS sbus3(&Serial2);
BMC_SBUS sbus4(&Serial3);

// It seems that the delay between frames may be between 7ms and 15ms according to spec.
// The library had 4, but you may want to increase this if it doesn't work.
#define SBUS_WAIT 4
#define SBUS_LOW 0
#define SBUS_MID 1024
#define SBUS_HIGH 2048

// The SBus button data structure
struct ButtonMap {
  // GPIO pin
  uint8_t pin;

  // State of the button press
  bool state;
  
  // Sbus object mapped to a Serial device
  BMC_SBUS *dev;

  // Sbus channel to update
  uint8_t channel;

  // Array to change how the program responds dynamically
} buttons[] = {

  // Here's where you can pick buttons. I would avoid using buttons mapped to Serial ports. They are (19, 18, 17, 16, 15, 14, 1, 0).

  /******************** Camera 1 ********************/
  
  // Button S1B1
  {
    pin: 9,
    state: HIGH,
    dev: &sbus1,
    channel: 1
  },

  // Button S1B2
  {
    pin: 10,
    state: HIGH,
    dev: &sbus1,
    channel: 2
  },

  // Button S1B3
  {
    pin: 11,
    state: HIGH,
    dev: &sbus1,
    channel: 3
  },
  // Button S1B4
  {
    pin: 12,
    state: HIGH,
    dev: &sbus1,
    channel: 4
  },

  // Button S1B5
  {
    pin: 8,
    state: HIGH,
    dev: &sbus1,
    channel: 5
  },

  /******************** Camera 2 ********************/

  // Button S2B1
  {
    pin: 2,
    state: HIGH,
    dev: &sbus2,
    channel: 1
  },

  // Button S2B2
  {
    pin: 3,
    state: HIGH,
    dev: &sbus2,
    channel: 2
  },

  // Button S2B3
  {
    pin: 4,
    state: HIGH,
    dev: &sbus2,
    channel: 3
  },

  // Button S2B4
  {
    pin: 5,
    state: HIGH,
    dev: &sbus2,
    channel: 4
  },

  // Button S2B5
  {
    pin: 6,
    state: HIGH,
    dev: &sbus2,
    channel: 5
  },

  /******************** Camera 3 ********************/
  
  // Button S3B1
  {
    pin: 65,
    state: HIGH,
    dev: &sbus3,
    channel: 1
  },

  // Button S3B2
  {
    pin: 66,
    state: HIGH,
    dev: &sbus3,
    channel: 2
  },

  // Button S3B3
  {
    pin: 67,
    state: HIGH,
    dev: &sbus3,
    channel: 3
  },

  // Button S3B4
  {
    pin: 68,
    state: HIGH,
    dev: &sbus3,
    channel: 4
  },

  // Button S3B5
  {
    pin: 69,
    state: HIGH,
    dev: &sbus3,
    channel: 5
  },

  /******************** Camera 4 ********************/

  // Button S4B1
  {
    pin: 54,
    state: HIGH,
    dev: &sbus4,
    channel: 1
  },

  // Button S4B2
  {
    pin: 55,
    state: HIGH,
    dev: &sbus4,
    channel: 2
  },

  // Button S4B3
  {
    pin: 56,
    state: HIGH,
    dev: &sbus4,
    channel: 3
  },

  // Button S4B4
  {  
    pin: 57,
    state: HIGH,
    dev: &sbus4,
    channel: 4
  },

  // Button S4B5
  {
    pin: 58,
    state: HIGH,
    dev: &sbus4,
    channel: 5
  }

};

byte numOfButtons;

void setup() {

  // Get lenght of the array.
  numOfButtons = sizeof(buttons) / sizeof(ButtonMap);

  for (byte i = 0; i < numOfButtons; i++) {
    // Set pullup resistors for input buttons. Pressed is LOW
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }

  // Start the S.Bus objects
  sbus1.begin();
  sbus2.begin();
  sbus3.begin();
  sbus4.begin();
}

void loop() {

  // Check if buttons are pressed and perform an action. 1 Button press will trigger 1 action even if held.
  for (byte i = 0; i < numOfButtons; i++) {
    if (buttonPressed(buttons[i].pin, &buttons[i].state)) {
      buttons[i].dev->Servo(buttons[i].channel, SBUS_MID);
      buttons[i].dev->Update();
      buttons[i].dev->Send();

      delay(SBUS_WAIT);

      buttons[i].dev->Servo(buttons[i].channel, SBUS_HIGH);
      buttons[i].dev->Update();
      buttons[i].dev->Send();

    }
  }  
}

// Returns true if the state of the button changes from HIGH to LOW. False in all other cases.
bool buttonPressed (int pin, bool *val) {
  if( digitalRead(pin) == LOW ) {
    if ( *val == HIGH ) {
      *val = LOW;
      return true;
    }
  } else {
    *val = HIGH;
  }
  return false;
}