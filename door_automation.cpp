#include <Servo.h>

Servo servo;

const int trigPin = 8;
const int echoPin = 9;
const int servoPin = 10;
int servoAngle = 90;
int delayTime = 3000;
int pingTravelTime;//variable to store the signal travel time
int distCm;
int distIn;

long readUltrasonicDistance(int trigPin, int echoPin){
  //Declare the modes of the pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //clear the trigger for 10 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  //set the trigger to HIGH for 10 micoseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  //clear the trigger for 10 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  
  //time taken for the signal to travel back and forth
  return pulseIn(echoPin, HIGH);
}

void openDoor(int servoPin){
  pinMode(servoPin, OUTPUT);
  servo.attach(servoPin);
  
  servo.write(servoAngle);
}

//void closeDoor(int servoPin){
  //pinMode(servoPin, OUTPUT);
  //servo.attach(servoPin);
  
  //servo.write(0);
//}

void setup()
{ 
  Serial.begin(9600);//establich communication with the serial monitor
}

void loop()
{
  //call the readUltrasonicDistance function and store the result
  pingTravelTime = readUltrasonicDistance(trigPin,echoPin);
  //calculating the distance in cm
  distCm = 0.01723 * pingTravelTime;
  //converting cm to inches
  distIn = distCm / 2.54;
  //Serial.println(pingTravelTime);
  Serial.print("Cm = ");
  Serial.print(distCm);
  Serial.print("; Inches = ");
  Serial.println(distIn);
  
  if (distCm <= 60){
  	openDoor(servoPin);
  } else {
	servo.write(0);  
  }
}
