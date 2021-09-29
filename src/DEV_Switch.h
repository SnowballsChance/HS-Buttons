////////////////////////////////////
//   DEVICE-SPECIFIC LED SERVICES //
////////////////////////////////////

struct DEV_Switch : Service::Switch
{ // LED Blinker
  int nSwitch;               // index number of the switch
  SpanCharacteristic *power; // reference to the On Characteristic

  DEV_Switch(int nSwitch, int buttonPin) : Service::Switch()
  { // constructor() method

    power = new Characteristic::On();

    this->nSwitch = nSwitch;
    new SpanButton(buttonPin, 2000, 5, 250); // create new SpanButton

    Serial.print("Configuring Switch: inded="); // initialization message
    Serial.print(nSwitch);
    Serial.print("  Button Pin="); // NEW! add output message for number of blinks
    Serial.print(buttonPin);
    Serial.print("\n");

  } // end constructor

  boolean update()
  { // update() method

    if (power->getNewVal())
    {
      leds[nSwitch] = CRGB::White;
    }

    if (!power->getNewVal())
    {
      leds[nSwitch] = CRGB::Black;
    }

    return (true); // return true

  } // update

  void button(int pin, int pressType) override
  {

    LOG1("Found button press on pin: "); // always a good idea to log messages
    LOG1(pin);
    LOG1("  type: ");
    LOG1(pressType == SpanButton::LONG ? "LONG" : (pressType == SpanButton::SINGLE) ? "SINGLE"
                                                                                    : "DOUBLE");
    LOG1("\n");

    if (pressType == SpanButton::SINGLE)
    {
      power->setVal(!power->getVal()); // toggle power status
      update();
    }
  } //end button
};

//////////////////////////////////

// HomeKit Bug Note:  There is an apparent bug in HomeKit uncovered during the development of this example.
// If you have an Accessory with three or more Services, and the Accessory receives a notification message
// from the device, AND the HomeKit interface is open to show the detailed control for this Service tile
// in the HomeKit app, then for some reason HomeKit sends an update() request back to the device asking to
// set the Characteristic to the value that it just received from an Event Notification.  HomeKit is not supposed
// to send update requests in response to an Event Notification.
