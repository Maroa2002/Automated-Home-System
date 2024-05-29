const int gasSensPin = A1;
const int ledPin = 4;
const int buzzerPin = 5;
const int gasThreshold = 500;
const int delayTime = 500;
int gasSensVal;

void setup()
{
  pinMode(gasSensPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
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
  
}
