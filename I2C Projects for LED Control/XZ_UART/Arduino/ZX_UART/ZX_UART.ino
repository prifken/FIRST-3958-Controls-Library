/****************************************************************
UART_ZX_Demo.ino
XYZ Interactive ZX Sensor
Shawn Hymel @ SparkFun Electronics
May 6, 2015
https://github.com/sparkfun/SparkFun_ZX_Distance_and_Gesture_Sensor_Arduino_Library
Tests the ZX sensor's ability to read ZX data over UART using 
SoftwareSerial. The ZX_Sensor library is needed for the
UART constants. As a result, we have to link the Wire library,
even though it is not used.
Hardware Connections:
 
 Arduino Pin  ZX Sensor Board  Function
 ---------------------------------------
 5V           VCC              Power
 GND          GND              Ground
 10           TX               Data
Resources:
Include SoftwareSerial.h, Wire.h, and ZX_Constants.h
Development environment specifics:
Written in Arduino 1.6.3
Tested with a SparkFun RedBoard
This code is beerware; if you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, please
buy us a round!
Distributed as-is; no warranty is given.
****************************************************************/

#include <SoftwareSerial.h>
#include <Wire.h>
#include <ZX_Sensor.h>

// Global Variables
SoftwareSerial soft_serial(10, 11);  // RX, TX
uint8_t z;
uint8_t a;
uint8_t b;
uint8_t c;
uint8_t d;
int array[]={1,2,3};

void setup() {
  
  // Initialize hardware serial port. Note the baud rate.
  Wire.begin(84);                // join i2c bus with address #84
  Wire.onRequest(requestEvent); 
  Serial.print("init");
  Serial.begin(115200);
  Serial.println();
  Serial.println("------------------------------------");
  Serial.println("SparkFun/GestureSense - UART ZX Demo");
  Serial.println("------------------------------------");
  
  // Initialize software serial port
  soft_serial.begin(115200);
}



void loop() {
  
  // Read in a character from the UART
  if ( soft_serial.available() ) {
    z = soft_serial.read();
    
    // Determine type of message and print it
    switch ( z ) {
      case ZX_UART_END:
       // Serial.println("End of stream");
        break;
      case ZX_UART_RANGES:
        //Serial.print("Ranges: ");
        //z = soft_serial.read();
        a = soft_serial.read();
        //Serial.print(z, DEC);
        //Serial.print(", ");
        //z = soft_serial.read();
        b = soft_serial.read();
        //Serial.println(z, DEC);
        break;
      case ZX_UART_X:
        //Serial.print("X: ");
        //z = soft_serial.read();
        c = soft_serial.read();
        //Serial.println(z, DEC);
        break;
      case ZX_UART_Z:
       // Serial.print("Z: ");
        //z = soft_serial.read();
        d = soft_serial.read();
        //Serial.println(z, DEC);
        break;
      case ZX_UART_ID:
        //Serial.print("Sensor type: ");
       // z = soft_serial.read();
        //Serial.print(z, DEC);
        //Serial.print(" HW version: ");
        //z = soft_serial.read();
        //Serial.print(z, DEC);
        //Serial.print(" FW version: ");
       // z = soft_serial.read();
        //Serial.println(z, DEC);
        break;
      default:
        break;
    }
  }
} 

void requestEvent()
{
  byte myArray[3];
  myArray[0]=a;
  myArray[1]=b;
  myArray[2]=c;
  myArray[3]=d;
  //Serial.print(d); 
  //Wire.write(z);
 // Wire.write(a);
 // Wire.write(b);
  //Wire.write(c);
 
  Wire.write(myArray,4);
  
}
