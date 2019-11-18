const int pinX = A0;
const int pinY = A1;
const int pinSW = A2;

const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int segSize = 8;
const int noOfDisplays = 4;
const int noOfDigits = 10;

int dpState = LOW;
int dpPlace = 0;
int dpRealPlace = 0;
int selection = 0;

int swState = LOW;
int lastSwState = LOW;
int xValue = 0;
int yValue = 0;

bool joyMoved = false;
int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int digit4 = 0;
const int minThreshold= 400;
const int maxThreshold= 600;

int segments[segSize] =
{pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP};

int digits[noOfDisplays] =
{pinD1, pinD2, pinD3, pinD4};

int digitValues[noOfDisplays] =
{digit1, digit2, digit3, digit4};

byte digitMatrix[noOfDigits][segSize - 1] =
{ {1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1},
  {1, 1, 1, 1, 0, 0, 1},
  {0, 1, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1} };

void displayNumber(byte digit, byte decimalPoint)
{
  for (int i = 0; i < segSize - 1; i++) {
  digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  digitalWrite(segments[segSize - 1], decimalPoint);
}

void showDigit(int num)
{
  for (int i = 0; i < noOfDisplays; i++) {
  digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num], LOW);
}

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const long interval = 500;

void setup()
{
  for (int i = 0; i < segSize; i++) {
  pinMode(segments[i], OUTPUT);
  }
  for (int i = 0; i < noOfDisplays; i++)
  {
    pinMode(digits[i], OUTPUT);  
  }
  pinMode(pinSW, INPUT_PULLUP);
  for (int i = 0; i < noOfDisplays; i++)
  {
    showDigit(i);
    if (i == dpPlace) dpState = HIGH;
    else dpState = LOW;
    displayNumber(0, dpState);
    delay (5);
  }
}

void loop()
{
  for (int i = 0; i < noOfDisplays; i++)
  {
    showDigit(i);
    if (i == dpPlace) dpState = HIGH;
    else dpState = LOW;
    displayNumber(digitValues[i], dpState);
    delay (5);
  }
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  if (yValue < minThreshold && joyMoved == false && selection == 0)
  {
    if (dpPlace < 3)
    {
      dpPlace++;
      dpRealPlace++;
    }
    else
    {
      dpPlace = 0;
      dpRealPlace = 0;
    }
    joyMoved = true;
  }
  if (yValue > maxThreshold && joyMoved == false && selection == 0)
  {
    if (dpPlace > 0)
    {
      dpPlace--;
      dpRealPlace--;
    }
    else
    {
      dpPlace = 3;
      dpRealPlace = 3;
    }
    joyMoved = true;
  }
  if (yValue >= minThreshold && yValue <= maxThreshold && selection == 0)
  {
    joyMoved = false;
  }
  
  if (xValue < minThreshold && joyMoved == false && selection == 1)
  {
    if (digitValues[dpRealPlace] > 0) digitValues[dpRealPlace]--;
    else digitValues[dpRealPlace] = 9;
    joyMoved = true;
  }
  if (xValue > maxThreshold && joyMoved == false && selection == 1)
  {
    if (digitValues[dpRealPlace] < 9) digitValues[dpRealPlace]++;
    else digitValues[dpRealPlace] = 0;
    joyMoved = true;
  }
  if (xValue >= minThreshold && xValue <= maxThreshold && selection == 1)
  {
    joyMoved = false;
  }

  swState = digitalRead(pinSW);
  if (swState !=  lastSwState && swState == LOW)
  {
    selection = !selection;
    dpPlace = dpRealPlace;
  }
  lastSwState = swState;

  currentMillis = millis();

  if (currentMillis - previousMillis >= interval && selection == 1)
  {
    previousMillis = currentMillis;
    if (dpPlace < 4) dpPlace = 4;
    else dpPlace = dpRealPlace;
  }
 
  delay(1);
}
