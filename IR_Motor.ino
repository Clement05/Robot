/*
 Stepper Motor Control with Arduino Motor Control Shield V3.0.
 
 This program drives a bipolar stepper motor. The motor is controlled
 by Arduino pins 10, 11, 12, 13.
 
 The motor should do five revolutions into one and five into another direction.
 
 Using this sketch for longer is not recommended because it will keep the motor under current
 and can cause it to become quite hot.
 
 */
 
#include <Stepper.h>
#include <IRremote.h>

 
int enA  = 10;  // Enable pin 1 on Motor Control Shield  
int enB  = 11;  // Enable pin 2 on Motor Control Shield  
int dirA = 12;  // Direction pin dirA on Motor Control Shield
int dirB = 13;  // Direction pin dirB on Motor Control Shield
 
 
const int stepsPerRevolution = 48;  // Change this to fit the number of steps per revolution
                                     // for your motor
 
// Initialize the stepper library on pins 12 and 13:
Stepper myStepper(stepsPerRevolution, dirA, dirB); 

const char DIN_RECEPTEUR_INFRAROUGE = 14;
IRrecv monRecepteurInfraRouge (DIN_RECEPTEUR_INFRAROUGE);
decode_results messageRecu;
 
void setup() {
       monRecepteurInfraRouge.enableIRIn();
      monRecepteurInfraRouge.blink13(true);
  Serial.begin(9600);
  // set the speed at 60 rpm:
  myStepper.setSpeed(255);
 
  // Enable power to the motor
  pinMode(enA, OUTPUT);
  digitalWrite (enA, HIGH);
 
  pinMode(enB, OUTPUT);
  digitalWrite (enB, HIGH);  
}
 
void loop() {
  // Step five revolutions into one direction:
  
  if (monRecepteurInfraRouge.decode(&messageRecu))
  {
    Serial.println(messageRecu.value,HEX);
    myStepper.step(stepsPerRevolution*48);
    delay(500);
    monRecepteurInfraRouge.resume();
  }
 
//  // Step five revolutions in the other direction:
//  myStepper.step(-stepsPerRevolution*1);
//  delay(20000);
}
