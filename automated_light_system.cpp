const int lightSensPin = A2;
const int lightPin1 = 6;
const int lightPin2 = 7;
const int lightPin3 = 8;
int lightSensVal;
int delayTime = 500;
int lightThreshold1 = 900;
int lightThreshold2 = 600;
int lightThreshold3 = 300;

void setup()
{
  pinMode(lightSensPin, INPUT);
  pinMode(lightPin1, OUTPUT);
  pinMode(lightPin2, OUTPUT);
  pinMode(lightPin3, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  lightSensVal = analogRead(lightSensPin);
  Serial.println(lightSensVal);
  delay(delayTime);
  
  if (lightSensVal < lightThreshold1 && lightSensVal > lightThreshold2){
	digitalWrite(lightPin1, HIGH);
    digitalWrite(lightPin2, LOW);
    digitalWrite(lightPin3, LOW);
  }
  
  
  if (lightSensVal < lightThreshold2 && lightSensVal > lightThreshold3){
	digitalWrite(lightPin1, HIGH);
    digitalWrite(lightPin2, HIGH);
    digitalWrite(lightPin3, LOW);
  }
  
  
  if (lightSensVal < lightThreshold3){
	digitalWrite(lightPin1, HIGH);
    digitalWrite(lightPin2, HIGH);
    digitalWrite(lightPin3, HIGH);
  }
  
  if (lightSensVal > lightThreshold1){
	digitalWrite(lightPin1, LOW);
    digitalWrite(lightPin2, LOW);
    digitalWrite(lightPin3, LOW);
  }
  
}
