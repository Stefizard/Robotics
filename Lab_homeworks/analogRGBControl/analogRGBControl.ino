const int redPotPin = A2;
const int redLedPin = 9;
const int greenPotPin = A1;
const int greenLedPin = 10;
const int bluePotPin = A0;
const int blueLedPin = 11;
int redPotValue = 0;
int redLedValue = 0;
int greenPotValue = 0;
int greenLedValue = 0;
int bluePotValue = 0;
int blueLedValue = 0;
void setup()
{
  pinMode (redLedPin, OUTPUT);
  pinMode (greenLedPin, OUTPUT);
  pinMode (blueLedPin, OUTPUT);
}

void loop()
{
  redPotValue = analogRead (redPotPin);
  redLedValue = map (redPotValue, 0, 1023, 0, 255);
 
  greenPotValue = analogRead (greenPotPin);
  greenLedValue = map (greenPotValue, 0, 1023, 0, 255);

  bluePotValue = analogRead (bluePotPin);
  blueLedValue = map (bluePotValue, 0, 1023, 0, 255);
  
  setColor (redLedValue, greenLedValue, blueLedValue);
}

void setColor (int red, int green, int blue)
{
  analogWrite (redLedPin, red);
  analogWrite (greenLedPin, green);
  analogWrite (blueLedPin, blue);
}
