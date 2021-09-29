#include <Arduino.h>
/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2021 Snowball's Chance
 *  
 *  
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *  
 ********************************************************************************/
 
/* ******************************************************************************
 * This project stands upon the shoulders of giants
 *
 * https://github.com/HomeSpan/HomeSpan (particularly Example 14)
 * 
 * http://fastled.io
 * 
 * https://www.arduino.cc
 * 
 * And countless others
 * 
 * Thank you all
 * *******************************************************************************/


#include "FastLED.h"
#define NUM_LEDS 3
#define LED_PIN 13
CRGB leds[NUM_LEDS];

#include "HomeSpan.h" 
#include "DEV_Switch.h"    
#include "DEV_Identify.h"       


void setup() {

  Serial.begin(115200);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
	FastLED.setBrightness(5);

  homeSpan.setStatusPin(2);
  homeSpan.setControlPin(0);
  homeSpan.begin(Category::Bridges,"HomeSpan Bridge");
  
  // Defines the Bridge Accessory
 
  new SpanAccessory();  
    new DEV_Identify("Virtual Switches","Snowball's Chance","123-ABC","Switch Bridge","0.9",10);
    new Service::HAPProtocolInformation();
      new Characteristic::Version("1.1.0");
  
    // We set individual names for the virtual switches - makes it easier to work out which is which in the home.app
  new SpanAccessory();                                                          
    new DEV_Identify("Switch 0","Snowballs Chance","123-ABC","Virtual Switch","0.9",0);
    new DEV_Switch(0, 12);      // DEV_Switch takes two arguments - index number (must be unique), and pin number of the button

new SpanAccessory();                                                          
    new DEV_Identify("Switch 1","Snowballs Chance","123-ABC","Virtual Switch","0.9",0);
    new DEV_Switch(1, 14);      // DEV_Switch takes two arguments - index number (must be unique), and pin number of the button

new SpanAccessory();                                                          
    new DEV_Identify("Switch 2","Snowballs Chance","123-ABC","Virtual Switch","0.9",0);
    new DEV_Switch(2, 27);   
} // end of setup()


void loop(){
  
  homeSpan.poll();
  FastLED.show();
  
} // end of loop()
