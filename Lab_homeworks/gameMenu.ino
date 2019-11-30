#include <LiquidCrystal.h>
#include <EEPROM.h>

const int rsPin = 12;
const int ePin = 11;
const int d4Pin = 5;
const int d5Pin = 4;
const int d6Pin = 3;
const int d7Pin = 2;

LiquidCrystal lcd(rsPin, ePin, d4Pin, d5Pin, d6Pin, d7Pin);

const int pinSW = 8;
const int pinX = A0;
const int pinY = A1;

int swState = LOW;
int lastSwState = LOW;
int switchValue;
int xValue = 0;
int yValue = 0;

bool joyMovedX = false;
bool joyMovedY = false;
const int minThreshold = 400;
const int maxThreshold = 600;

int screenID = 0;
int selection = 0;
int highScore = 0;
int startingLevelValue = 0;
const int maxLevelValue = 10;
int level = 0;
bool selected = false;

unsigned long levelTime;
unsigned long gameTime;
unsigned long selectedTime;
bool levelStart = false;
bool gameStart = false;
bool selectedState = false;
const int levelLength = 2000;
const int gameLength = 10000;
const int selectedLength = 500;

void setup()
{
  lcd.begin (16, 2);

  lcd.print (" >Start  HiScore");
  lcd.setCursor (0,1);
  lcd.print ("    Settings    ");
  
  pinMode(pinSW, INPUT_PULLUP);

  highScore = EEPROM.read (0);
  EEPROM.write (0,0);
}

void loop()
{
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  if (xValue < minThreshold && joyMovedX == false) 
  {
    if (screenID == 0 && selection == 1)
    {
      lcd.setCursor (8, 0);
      lcd.print (" ");
      lcd.setCursor (1, 0);
      lcd.print (">");
      selection = 0;
    }
    else if (screenID == 0 && selection == 2)
    {
      lcd.setCursor (3, 1);
      lcd.print (" ");
      lcd.setCursor (8, 0);
      lcd.print (">");
      selection = 1;
    }
    else if (screenID == 3 && selected == false)
    {
      lcd.clear ();
      lcd.print (" >Start  HiScore");
      lcd.setCursor (0,1);
      lcd.print ("    Settings    ");
      selection = 0;
      screenID = 0;
    }
    joyMovedX = true;
  }
  if (xValue > maxThreshold && joyMovedX == false)
  {
    if (screenID == 0 && selection == 0)
    {
      lcd.setCursor (1, 0);
      lcd.print (" ");
      lcd.setCursor (8, 0);
      lcd.print (">");
      selection = 1;
    }
    else if (screenID == 0 && selection == 1)
    {
      lcd.setCursor (8, 0);
      lcd.print (" ");
      lcd.setCursor (3, 1);
      lcd.print (">");
      selection = 2;
    }
    joyMovedX = true;
  }
  if (xValue >= minThreshold && xValue <= maxThreshold)
  {
    joyMovedX = false;
  }
  
  if (yValue < minThreshold && joyMovedY == false) 
  {
    if (screenID == 3 && selection == 0 && selected == false)
    {
      lcd.setCursor (0, 0);
      lcd.print (" ");
      lcd.setCursor (0, 1);
      lcd.print (">");
      selection = 1;
    }
    else if (screenID == 3 && selection == 1 && selected == true)
    {
      if (startingLevelValue > 0) startingLevelValue--;
      lcd.setCursor (14, 1);
      lcd.print (startingLevelValue);
      lcd.print (" ");
    }
    joyMovedY = true;
  }
  if (yValue > maxThreshold && joyMovedY == false)
  {
    if (screenID == 3 && selection == 1 && selected == false)
    {
      lcd.setCursor (0, 1);
      lcd.print (" ");
      lcd.setCursor (0, 0);
      lcd.print (">");
      selection = 0;
    }
    else if (screenID == 3 && selection == 1 && selected == true)
    {
      if (startingLevelValue < maxLevelValue) startingLevelValue++;
      lcd.setCursor (14, 1);
      lcd.print (startingLevelValue);
    }
    joyMovedY = true;
  }
  if (yValue >= minThreshold && yValue <= maxThreshold)
  {
    joyMovedY = false;
  }


  swState = digitalRead(pinSW);
  if (swState !=  lastSwState && swState == LOW)
  {
    if (screenID == 0 && selection == 0)
    {
      lcd.clear ();
      lcd.print ("Lives: 3 Lvl: ");
      lcd.print (startingLevelValue);
      lcd.setCursor (0,1);
      lcd.print ("    Score: ");
      lcd.print (3 * startingLevelValue);
      level = startingLevelValue;
      gameTime = millis();
      levelTime = millis();
      gameStart = true;
      levelStart = true;
      screenID = 1;
    }
    else if (screenID == 0 && selection == 1)
    {
      lcd.clear ();
      lcd.print ("   STEFAN: ");
      lcd.print (highScore);
      lcd.setCursor (0,1);
      lcd.print ("Press to return.");
      screenID = 2;
    }
    else if (screenID == 0 && selection == 2)
    {
      lcd.clear ();
      lcd.print (">Name: STEFAN");
      lcd.setCursor (0,1);
      lcd.print (" Start level: ");
      lcd.print (startingLevelValue);
      selection = 0;
      screenID = 3;
    }
    else if (screenID == 1 && gameStart == false)
    {
      lcd.clear ();
      lcd.print (" >Start  HiScore");
      lcd.setCursor (0,1);
      lcd.print ("    Settings    ");
      screenID = 0;
    }
    else if (screenID == 2)
    {
      lcd.clear ();
      lcd.print (" >Start  HiScore");
      lcd.setCursor (0,1);
      lcd.print ("    Settings    ");
      selection = 0;
      screenID = 0;
    }
    else if (screenID == 3 && selection == 1 && selected == false)
    {
      selected = true;
      lcd.setCursor (0,1);
      lcd.print (" ");
      selectedTime = millis();
    }
    else if (screenID == 3 && selection == 1 && selected == true)
    {
      selected = false;
      lcd.setCursor (0,1);
      lcd.print (">");
    }
  }
  lastSwState = swState;

  if (screenID ==1)
  {
    if (millis() - levelTime >= levelLength && levelStart == true)
    {
      level++;
      lcd.setCursor (14,0);
      lcd.print (level);
      lcd.setCursor (11,1);
      lcd.print (3 * level);
      levelTime = millis();
    }
    if (millis() - gameTime >= gameLength && gameStart == true)
    {
      if (3 * level > highScore) highScore = 3 * level;
      EEPROM.write(0,highScore);
      levelStart = false;
      gameStart = false;
      lcd.clear();
      lcd.print ("Congrats! Press");
      lcd.setCursor (0,1);
      lcd.print ("button to exit.");
    }
  }
  if (screenID == 3 && selection == 1 && selected == true && (millis() - selectedTime > selectedLength))
  {
    lcd.setCursor (0,1);
    if (selectedState == true)
    {
      lcd.print (" ");
      selectedState = false;
    }
    else
    {
      lcd.print (">");
      selectedState = true;
    }
    selectedTime = millis();
  }
  delay(1);
}
