This script parses date and determines how to execute the function colorWipe(), part of the Arduino library for neoPixels. 

The script reads I2C packets to determine the index of the strip (how far to turn "ON"). LEDs beyond the index are turned "OFF". 

Variables

int ledlevel = 0; 
int brightness = 0; 
int R = 0; 
int G = 0; 
int B = 0; 
int R_Off = 0; 
int G_Off = 0; 
int B_Off = 0; 

Looping Code

 if (i<ledlevel)
      {
      strip.setPixelColor(i, c);
      }
      else
      {
      strip.setPixelColor(i, R_Off,G_Off,B_Off);
      }
      strip.show();
      delay(wait);