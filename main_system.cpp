//library used for I2C communication
#include <Wire.h>
//simplifies the use of I2C LCD
#include <LiquidCrystal_I2C.h>
//simplifies the use of the servo motor
#include <Servo.h> 


Servo servo;
LiquidCrystal_I2C lcd(0x20, 16, 2);

// C++ code
//automated fan system parameters and variables
const int tempSensPin = A0;
const int dir1 = 2;
const int dir2 = 3;
 //const int motorPin = 3;
int motorSpeed;
int tempSensVal;
float tempSensVolt;
float tempC;
float tempF;

//gas sensor system parameters and variables
const int gasSensPin = A1;
const int ledPin = 4;
const int buzzerPin = 5;
const int gasThreshold = 500;
//const int delayTime = 500;
int gasSensVal;

//automated light sytem
const int lightSensPin = A2;
const int lightPin1 = 6;
//const int lightPin2 = 7;
//const int lightPin3 = 8;
int lightSensVal;
 //int delayTime = 500;
int lightThreshold1 = 400;
int lightThreshold2 = 600;
int lightThreshold3 = 300;

//automated door system

const int trigPin = 7;
const int echoPin = 8;
const int servoPin = 9;
int servoAngle = 90;
//int delayTime = 3000;
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

int delayTime = 500;

void setup()
{
  pinMode(tempSensPin, INPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  //pinMode(motorPin, OUTPUT);
  
  pinMode(gasSensPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  pinMode(lightSensPin, INPUT);
  pinMode(lightPin1, OUTPUT);
  //pinMode(lightPin2, OUTPUT);
  //pinMode(lightPin3, OUTPUT);
  
  lcd.init();//initializing the LCD
  lcd.backlight();//turn on the backlight
  lcd.setCursor(1,0);
  lcd.print("Hello World");
  
  Serial.begin(9600);
}

void loop()
{
  //automated fan system
  tempSensVal = analogRead(tempSensPin);
  tempSensVolt = (5./1023.) * tempSensVal;
  tempC = (97./845.) * tempSensVal + 2.8;
  tempF = (tempC * 9./5.) + 32;
  motorSpeed = (105./14.) * tempC;
  
  Serial.print(tempSensVal);
  Serial.print("; ");
  Serial.println(tempSensVolt);
  Serial.print("tempC = ");
  Serial.print(tempC);
  Serial.print("; tempF = ");
  Serial.println(tempF);
  Serial.println(motorSpeed);
  delay(delayTime);
  
  if (tempC > 30){
    digitalWrite(dir1, HIGH);
    digitalWrite(dir2, LOW);
    //analogWrite(motorPin, motorSpeed);
  }
  
  if (tempC < 30){
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, LOW);
    //analogWrite(motorPin, 0);
  }
  
  //gas detection system
  gasSensVal = analogRead(gasSensPin);
  Serial.println(gasSensVal);
  delay(delayTime);
  
  if (gasSensVal > gasThreshold){
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(delayTime); 
    digitalWrite(ledPin, LOW);
    delay(delayTime);
  }
  
  if (gasSensVal < gasThreshold){
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }
  
  //light automation system
  lightSensVal = analogRead(lightSensPin);
  Serial.println(lightSensVal);
  delay(delayTime);
  
  if (lightSensVal < lightThreshold1 && lightSensVal > lightThreshold2){
	digitalWrite(lightPin1, HIGH);
    //digitalWrite(lightPin2, LOW);
    //digitalWrite(lightPin3, LOW);
  }
  
  
  if (lightSensVal < lightThreshold2 && lightSensVal > lightThreshold3){
	digitalWrite(lightPin1, HIGH);
    //digitalWrite(lightPin2, HIGH);
    //digitalWrite(lightPin3, LOW);
  }
  
  
  if (lightSensVal < lightThreshold3){
	digitalWrite(lightPin1, HIGH);
    //digitalWrite(lightPin2, HIGH);
    //digitalWrite(lightPin3, HIGH);
  }
  
  if (lightSensVal > lightThreshold1){
	digitalWrite(lightPin1, LOW);
    //digitalWrite(lightPin2, LOW);
    //digitalWrite(lightPin3, LOW);
  }
  
  //automated door
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
