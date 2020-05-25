/*************************************************************************************************
sketch by Nicu FLORICA (niq_ro)
http://arduinotehniq.com/
*************************************************************************************************/

#define echo 12
#define trig 11
#define releu A3  // A3
#define potentiometru A0

// establish variables for duration 
// and the distance result in inches
long duration, cm;

int threshold = 25; //Sensor threshold in cm

//boolean debug = false; //Serial communication for debuging. Set to true for serial communication.
boolean debug = true; //Serial communication for debuging. Set to true for serial communication.

unsigned int tpactivare;
unsigned int tpmin = 3000;
unsigned int tpmax = 30000;
unsigned int pozitie = 0;


void setup() {
  // initialize serial communication:
  if (debug)
  {
    Serial.begin(9600);
  }
  Serial.println();
  Serial.println("Simple Gate...");
  pinMode(releu, OUTPUT);
  digitalWrite(releu, LOW); 
}

void loop()
{
  //Most of the sensor code has been taken from David Mellis's PING sensor code
  //I modified it for a 4 pin sensor as oppsed to the 3 pin sensor
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  cm = duration/58;
   
  if (debug)
  {
    Serial.print("Distance: ");
    Serial.print(cm);
    Serial.println("cm");
  }

pozitie = analogRead(potentiometru);
tpactivare = map (pozitie, 1023, 0, tpmin, tpmax);
 if (debug)
  {
    Serial.print("Cursor: ");
    Serial.print(pozitie); 
    Serial.print("/1023 => ");
    Serial.print(tpactivare/1000); 
    Serial.println("s "); 
  }

if (cm < threshold)
{
  digitalWrite(releu, HIGH);
  delay(tpactivare); // seconds
  digitalWrite(releu, LOW);
}
  
}  // end main loop
