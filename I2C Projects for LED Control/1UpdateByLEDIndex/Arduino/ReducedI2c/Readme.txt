Data Profile:

//Initialize global variables, currently 5 variables used as we expect 5 bytes of data from the RoboRIO. 
int ledindex = 0;  
int brightness = 0; 
int R = 0; 
int G = 0; 
int B = 0; 


READ FROM WIRE



  ledindex = Wire.read();    // receive byte as an integer
  R = Wire.read();
  G = Wire.read();
  B = Wire.read();  //Serial.println(x);         // print the integer
  brightness = Wire.read(); 