/*************************************************************************************************
**************************************************************************************************
Motion Follow
Created by Calvin Kielas-Jensen
Using an Arduino UNO, check Instructables.com for the circuit diagram.
This script allows two ultrasonic range sensors to follow movement while mounted on the top of a
servo. The distance threshold can be changed but should not be set too far as the sensors will
begin to fail.
Anyone is welcome to use and modify this code as long as I am given credit. Thank you for
respecting the open source movement! 
**************************************************************************************************
Nicu FLORICA aka niq_ro made some changes in sketch to use 2 sensors
see http://www.tehnic.go.ro &
http://arduinotehniq.com/
*************************************************************************************************/

const int Lecho = 12, Recho = 10, Ltrig = 11, Rtrig = 9, releu = 4; //setting sensor pins and relay pin

// establish variables for duration 
// and the distance result in inches
long Rduration, Lduration, Rinches, Linches, Rcm, Lcm;

int threshold = 25; //Sensor threshold in cm

//boolean debug = false; //Serial communication for debuging. Set to true for serial communication.
boolean debug = true; //Serial communication for debuging. Set to true for serial communication.

unsigned long tpactivare = 3000;

void setup() {
  // initialize serial communication:
  if (debug)
  {
    Serial.begin(9600);
  }
  Serial.println();
  Serial.println("Dual Gate...");
   pinMode(releu, OUTPUT);
  digitalWrite(releu, LOW); 
}

void loop()
{
  //Most of the sensor code has been taken from David Mellis's PING sensor code
  //I modified it for a 4 pin sensor as oppsed to the 3 pin sensor
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(Rtrig, OUTPUT);
  digitalWrite(Rtrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Rtrig, HIGH);
  delayMicroseconds(5);
  digitalWrite(Rtrig, LOW);
  Rduration = pulseIn(Recho, HIGH);
  Rcm = Rduration/58;
  
  pinMode(Ltrig, OUTPUT);
  digitalWrite(Ltrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ltrig, HIGH);   
  delayMicroseconds(5);
  digitalWrite(Ltrig, LOW);
  Lduration = pulseIn(Lecho, HIGH);
  Lcm = Lduration/58;
   
  if (debug)
  {
    Serial.print("Left: ");
    Serial.print(Lcm);
    Serial.println("cm");
    
    Serial.print("Right: ");
    Serial.print(Rcm);
    Serial.println("cm");
  }

if ((Rcm < threshold) or (Lcm < threshold))
{
  if (debug)
  {
    Serial.println("Relay activated !!");
  }
  digitalWrite(releu, HIGH);
  delay(tpactivare);
  digitalWrite(releu, LOW);
}

  
}  // end main loop
