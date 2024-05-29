const int tempSensPin = A0;
const int dir1 = 2;
const int dir2 = 3;
//const int motorPin = 3;
int motorSpeed;
int tempSensVal;
float tempSensVolt;
float tempC;
float tempF;

int delayTime = 500;

void setup()
{
  pinMode(tempSensPin, INPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  //pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
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
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, HIGH);
    //analogWrite(motorPin, motorSpeed);
  }
  
  if (tempC < 30){
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, LOW);
    //analogWrite(motorPin, 0);
  }
}
