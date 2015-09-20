#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <avr/power.h>
#define PIN 6 //Your LED strip's DIN pin should be connected to PIN 6 on the microcontroller

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

//Initialize global variables, currently 5 variables used as we expect 5 bytes of data from the RoboRIO. 
int ledindex = 0;  
int brightness = 0; 
int R = 0; 
int G = 0; 
int B = 0; 

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Wire.begin(84);                // join i2c bus with address #84
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  Serial.print("init"); //initialize complete
  Wire.onRequest(requestEvent); //If you are interested in sending data back to the RoboRIO with (Use I2C Read in LabVIEW), you need to run this during setup. 
}
void loop() 
{
  
strip.setPixelColor(ledindex, R, G, B);
strip.setBrightness(brightness);
strip.show(); //this function actually updates the LEDs during every iteration. 

}


void receiveEvent(int howMany)//Executes only when a packet of data is send from the I2C Master (e.g., RoboRIO or another Arduino)
{

 //We are expecting 5 bytes of data. The bytes are read in order and stored as global variables. The first byte is read and is stored in ledindex. The second,
 //third, and fourth byte are stored in R, G, and B, respectively. The last byte is stored in brightness. Additional packets overwrite previous data. Meanwhile,
//the loop above is taking the latest data and updating the LED strip. 
  
  ledindex = Wire.read();    // receive byte as an integer
  R = Wire.read();
  G = Wire.read();
  B = Wire.read();  //Serial.println(x);         // print the integer
  brightness = Wire.read(); 
  Serial.println("Received");
  
}

// function that executes whenever data is requested by Master (e.g., RoboRIO or another Arduino)
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write("hello");
  
}

