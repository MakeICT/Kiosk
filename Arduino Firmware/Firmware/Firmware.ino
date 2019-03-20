
/*
* Sean
* globalw2865@gmail.com
* 30JUL2012
* Bill validator/Arduino (second draft)
*/

/*
* RESOURCES:
* http://www.arduino.cc/en/Reference/PulseIn
* http://kegbot.blogspot.com/2004/11/coinco-magpro-mag50b-pinout.html
* http://www.coinco.com/coin/faq/servicematerials/921970_1.pdf
*/

/*
* Description:
* Arduino records and counts dollar bill received from pin 7 (billValidator).
*/

// Constants //
// pin for the bill validator's credit(-) line
const int billValidator = 2;

// Variables //

// recording the duration of pulse (milliseconds)
unsigned long duration;

// holding the total dollars recorded
int dollarCounter = 0;

volatile unsigned long bill_pulse_start = 0;
volatile unsigned long bill_pulse_length = 0;
volatile bool p_start = false;
volatile bool p_end = false;

void pulse_track() 
{
  if(digitalRead(billValidator)) {
    p_end=false;
    bill_pulse_start = micros();
  }
  else{
    p_end = true;
    bill_pulse_length = micros() - bill_pulse_start;
  }
}

void setup()
{
  // Pin setups for bill validator and button
  pinMode(billValidator, INPUT);
  attachInterrupt(digitalPinToInterrupt(billValidator), pulse_track, CHANGE);
 
  // Initialize serial ports for communication.
  Serial.begin(9600);
  Serial.println("Waiting for dollar...");
}

void loop()
{
if(p_start) Serial.println("pulse started");
p_start=false;
//  if(p_end) Serial.println("pulse ended");
  
  // get the duration of the pulse
//duration = pulseIn(billValidator, HIGH);
  
  duration = bill_pulse_length;
//Serial.println(bill_pulse_length);
   
  // Receiving a dollar bill will create a pulse
  // with a duration of 150000 - 160000.
  // NOTE: When there is no dollar bill pulse,
  // I will receive a pulse of 8400 - 8600
  // on every loop.
  // Dollar received
  if(p_end && duration > 12000)
  {
    // Count dollar
    dollarCounter++;
    // Checking for understanding
    Serial.print("Dollar detected.\n Total: ");
    // Display new dollar count
    Serial.println(dollarCounter);
    bill_pulse_length = 0;
  } 
     
}
