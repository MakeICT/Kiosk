/*     Simple Stepper Motor Control Exaple Code
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */

// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4; 
const int enPin = 5; 
const int stepPulseLength = 800;
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  Serial.begin(9600);
}
void loop() {
//  while(1) {
//    Serial.println(analogRead(A6));
//  }
  
  digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  int remainingSteps = 0;
  if(analogRead(A6) < 100)
    remainingSteps = 100;
  while(remainingSteps) {
    if(analogRead(A6) < 100)
      remainingSteps = 100;

    digitalWrite(enPin,LOW);
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(stepPulseLength); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(stepPulseLength);
    remainingSteps--;
  }
  digitalWrite(enPin,HIGH);
//  delay(3000); // One second delay
  
//  digitalWrite(dirPin,LOW); //Changes the rotations direction
//  // Makes 400 pulses for making two full cycle rotation
//  for(int x = 0; x < 400; x++) {
//    digitalWrite(stepPin,HIGH);
//    delayMicroseconds(stepPulseLength);
//    digitalWrite(stepPin,LOW);
//    delayMicroseconds(stepPulseLength);
//  }
//  delay(1000);
}
