#include <math.h>
#define EULER 2.718281828459045235360287471352

float z = 0.868*1000;
bool pflag = false;
float total_program_duration = 420000;
float curveZero = 0;
float brightness = 0;
float brightness_previous = 0;
bool runProgram = true;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  runProgram = true;
  total_program_duration = round(((analogRead(2)/1023.0)*(1800000.0-420000))+420000);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  Serial.println(total_program_duration);


  //((analogRead(2)/1023)*(1800000-420000))+420000
}

// the loop function runs over and over again forever
void loop() {

  static bool endProgram = false;
  
  if (!endProgram) {
    endProgram = ModifyLedBrightness();
  }
}

bool ModifyLedBrightness() {
  
  static bool endProgram = false; //static variable to signal the end of the breathing cycles.
  
  brightness = (exp(sin(((millis()-curveZero)-z*(PI/2))/z))-(1/EULER))*(255/(EULER-(1/EULER))); //brightness of the LED is calculated
  
  if (brightness_previous>brightness && !pflag) { //checks to see if the top of the brightness curve has been hit
    
    pflag = true;
    Serial.println("High"); 
    
   }
   
   if (brightness_previous<brightness && pflag) { //checks to see if the bottom of the brightness curve has been hit

    pflag = false;
    brightness = 0;    
    z = 1.5915*1000.0-((total_program_duration-millis())/total_program_duration)*(1.5915*1000.0-0.868*1000.0); //changes the z paramter to make the next cycle longer
       
    if (total_program_duration <= millis()) { //if the program has reached the full amount of time, the endProgram flag is set to true
          endProgram = true;
          Serial.print(millis());
    }

    Serial.println(millis()-curveZero); //duration of cycle (debugging purposes)
    curveZero = millis(); //resets the zero of the curve to the current point in time
    
   }
  
   analogWrite(9, brightness); //writes the brightness to the LED
   brightness_previous = brightness; //saves the brightness in another value for comparison purposes later.
   return endProgram; //returns the boolean to see if the function will be called back again. 
}

