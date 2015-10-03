#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <avr/power.h>
#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int ledlevel = 0; 
int brightness = 0; 
int R = 0; 
int G = 0; 
int B = 0; 
int R_Off = 0; 
int G_Off = 0; 
int B_Off = 0; 

void setup() {
   strip.begin();
  
  strip.show(); // Initialize all pixels to 'off'
  Wire.begin(84);                // join i2c bus with address #84
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  Serial.print("init"); //initialize complete
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(R, G, B), 1); //Green
  
 Serial.print("Looping");
 Serial.print(ledlevel); 
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      
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
  }
}
      
      // Try to loop from i = 0 to i < strip.numPixels(), with the condition that the pixel colors are set to bright only while i < height (else turn LED off). 

void receiveEvent(int howMany)//Receive 5 bytes
{
 ledlevel = Wire.read();    // receive byte as an integer
  R = Wire.read();
  G = Wire.read();
  B = Wire.read();  //Serial.println(x);         // print the integer
  R_Off = Wire.read();
  G_Off = Wire.read();
  B_Off = Wire.read(); 
  brightness = Wire.read(); 
  Serial.println("Received");

}



