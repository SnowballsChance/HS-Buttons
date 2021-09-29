# HS-Buttons
Homekit enabled RX480E RF module Via ESP32, Arduino, Homespan


I have some lights that are connected to Homekit by smart switches. This means the original light switches don't work as usual. We can speak and ask Siri to operate them. But sometimes it is just easier to press a button on the wall.... (I might have just come full circle)!

So I have some RF modules and an ESP32 plus the awesome [HomeSpan] (https://github.com/HomeSpan) library. 

Homespan enables  the setup in Apple's homekit of several virtual switches. These can be turned on by Siri and Homekit or by the press of the remote button. When triggered a Homekit automation runs and turns on/off the particular light/s we want toggled. 

In this configuration it still allows the lights to be operated individualy through Siri, the home app or other automations. The small downside is if not all lights in a group are in the same state when the RF remote button is pushed it may need to be done a second time to get all the lights all on or all off depending...

A LED provides visual indication of the switch state.
