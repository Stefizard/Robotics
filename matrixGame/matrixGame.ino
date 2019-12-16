#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "LedControl.h"

const int rsPin = 7;
const int ePin = 4;
const int d4Pin = A2;
const int d5Pin = A3;
const int d6Pin = A4;
const int d7Pin = A5;

LiquidCrystal lcd(rsPin, ePin, d4Pin, d5Pin, d6Pin, d7Pin);

const int brightness = 2;
const int dinPin = 12;
const int clkPin = 11;
const int loadPin = 10;
const int noOfDrivers = 1;

const int redLedPin = 9;
const int greenLedPin = 6;
const int blueLedPin = 5;

const int activeBuzzer = 3;

const int pinJoySW = 8;
const int pinX = A0;
const int pinY = A1;

const int pinSW = 13;

int swState = LOW;
int lastSwState = LOW;
int switchValue;

int joySwState = LOW;
int lastJoySwState = LOW;
int joySwitchValue;

int xValue = 0;
int yValue = 0;

bool joyMovedX = false;
bool joyMovedY = false;
const int minThreshold = 300;
const int maxThreshold = 700;

short int screenID = 0;
int selection = 0;
int startingLevelValue = 0;
const int noOfLevels = 15;
bool selected = false;

int lives;
int time;
int score;
char name[10] = "PLAYER   ";
int letterPlace;

int hiScore1;
int hiScore2;
int hiScore3;
char hiName1[10];
char hiName2[10];
char hiName3[10];

unsigned long infoTime;
unsigned long levelTime;
unsigned long selectedTime;
unsigned long joyXTime;
unsigned long joyYTime;
bool infoState = false;
bool selectedState = false;
const int infoLength = 4000;
const int levelLength = 100;
const int selectedLength = 300;
const int joyResetTime = 300;

typedef struct
{
  char dotX ,dotY, objX, objY; // char because I needed memory
} level;

level levels[noOfLevels];

int levelID = 0;
int x, y;

const bool level0[8][8] = {
{1, 1, 1, 0, 0, 1, 1, 1},
{1, 1, 1, 0, 0, 1, 1, 1},
{1, 1, 1, 0, 0, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 0, 0, 1, 1, 1},
{1, 1, 1, 0, 0, 1, 1, 1},
{1, 1, 1, 0, 0, 1, 1, 1}
};

const bool level1[8][8] = {
{0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 0, 0},
{1, 1, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1, 1},
{0, 0, 1, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0}
};

const bool level2[8][8] = {
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1, 0},
{0, 0, 1, 1, 1, 0, 1, 0},
{0, 0, 1, 1, 1, 1, 1, 0},
{0, 0, 1, 1, 1, 0, 0, 0},
{0, 0, 1, 1, 1, 0, 0, 0}
};

const bool level3[8][8] = {
{0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 0, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 0, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 0, 1, 1},
{0, 1, 0, 0, 0, 0, 1, 0},
{0, 0, 0, 1, 0, 0, 0, 0}
};

const bool level4[8][8] = {
{1, 0, 0, 0, 0, 0, 1, 0},
{0, 1, 0, 0, 1, 0, 0, 1},
{0, 0, 1, 0, 0, 1, 0, 0},
{0, 0, 0, 1, 0, 0, 1, 0},
{0, 1, 0, 0, 1, 0, 0, 1},
{0, 0, 1, 0, 0, 1, 0, 0},
{1, 0, 0, 1, 0, 0, 1, 0},
{0, 1, 0, 0, 1, 0, 0, 0}
};

const bool level5[8][8] = {
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1},
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0}
};

const bool level6[8][8] = {
{0, 1, 1, 1, 0, 1, 1, 1},
{1, 1, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 0, 0},
{0, 0, 0, 1, 1, 1, 0, 0},
{0, 0, 1, 1, 1, 1, 1, 0},
{0, 1, 1, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 1, 0, 0, 0}
};

const bool level7[8][8] = {
{0, 0, 1, 0, 0, 1, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 1, 0, 0, 1, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 1, 0, 0, 1, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 1, 0, 0, 1, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0}
};

const bool level8[8][8] = {
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 0, 0, 1},
{1, 0, 1, 0, 0, 1, 0, 1}
};

const bool level9[8][8] = {
{0, 0, 1, 1, 1, 1, 0, 0},
{0, 1, 1, 0, 0, 1, 1, 0},
{1, 1, 0, 0, 0, 0, 1, 1},
{1, 0, 0, 1, 1, 0, 0, 1},
{1, 0, 0, 1, 1, 0, 0, 1},
{1, 1, 0, 0, 0, 0, 1, 1},
{0, 1, 1, 0, 0, 1, 1, 0},
{0, 0, 1, 1, 1, 1, 0, 0}
};

const bool level10[8][8] = {
{0, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 0, 0, 0}
};

const bool level11[8][8] = {
{0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1, 0},
{0, 1, 1, 1, 1, 0, 1, 0},
{0, 1, 1, 1, 1, 0, 1, 0},
{0, 1, 1, 1, 1, 0, 1, 0},
{0, 1, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 0, 0}
};

const bool level12[8][8] = {
{0, 0, 1, 1, 1, 1, 0, 0},
{0, 1, 0, 1, 1, 0, 1, 0},
{1, 1, 0, 1, 1, 0, 1, 1},
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 0, 0},
{1, 1, 0, 0, 0, 0, 1, 1},
{1, 1, 0, 0, 0, 0, 1, 1}
};

const bool level13[8][8] = {
{1, 0, 0, 0, 0, 0, 0, 1},
{0, 1, 0, 0, 0, 0, 1, 0},
{0, 0, 1, 0, 0, 1, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1},
{0, 0, 1, 0, 0, 1, 0, 0},
{0, 1, 0, 0, 0, 0, 1, 0},
{1, 0, 0, 0, 0, 0, 0, 1}
};

const bool level14[8][8] = {
{0, 0, 0, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 0, 0},
{0, 0, 0, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 0, 0},
{0, 1, 1, 1, 1, 1, 1, 0},
{0, 0, 1, 1, 1, 1, 0, 0},
{0, 0, 1, 1, 1, 1, 0, 0}
};

LedControl lc = LedControl (dinPin, clkPin, loadPin, noOfDrivers);

int bombX, bombY;
bool bombBlinkState = false, bombState = false;
unsigned long bombBlinkTime, bombTime;
const int bombBlinkLength = 500, bombLength = 3000;

bool detonationSound = false;
unsigned long detonationVariableSound, detonationBetweenBeepsSound;
const int detonationVariableSoundLength = 1000;
int detonationBetweenBeeps;

bool detonationBlinkState = false, detonationState = false;
unsigned long detonationBlinkTime, detonationTime;
const int detonationBlinkLength = 300, detonationLength = 2000;

unsigned long playerTime;
bool playerState = true;
const int playerLength = 200;

unsigned long ledTime;
bool ledState = true;
const int ledLength = 100;

bool death = false;
int deathAnimation[8][8];
int parcurgere;

void setColor (int red, int green, int blue)
{
  analogWrite (redLedPin, red);
  analogWrite (greenLedPin, green);
  analogWrite (blueLedPin, blue);
}

void dist (int x, int y, int a, int b)
{
  int S = abs (x - a) + abs (y - b);
  if (S == 0)
  {
    setColor (255, 0, 0);
    ledTime = millis ();
  }
  if (S > 0 && S < 3)
  {
    setColor (255, 0, 0);
  } 
  if (S > 2 && S < 5)
  {
    setColor (50, 0, 0);
  } 
  if (S > 4 && S < 7)
  {
    setColor (255, 25, 25);
  } 
  if (S > 6 && S < 9)
  {
    setColor (0, 0, 25);
  } 
  if (S > 8)
  {
    setColor (0, 0, 50);
  }
}

bool walls[8][8];

void setlevel (int levelID)
{
  bombState = false;
  detonationState = false;
  detonationSound = false;
  if (levelID == 0)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level0[row][col]);
          walls[row][col] = level0[row][col];
       }
  }
  if (levelID == 1)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level1[row][col]);
          walls[row][col] = level1[row][col];
       }
  }
  if (levelID == 2)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level2[row][col]);
          walls[row][col] = level2[row][col];
       }
  }
  if (levelID == 3)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level3[row][col]);
          walls[row][col] = level3[row][col];
       }
  }
  if (levelID == 4)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level4[row][col]);
          walls[row][col] = level4[row][col];
       }
  }
  if (levelID == 5)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level5[row][col]);
          walls[row][col] = level5[row][col];
       }
  }
  if (levelID == 6)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level6[row][col]);
          walls[row][col] = level6[row][col];
       }
  }
  if (levelID == 7)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level7[row][col]);
          walls[row][col] = level7[row][col];
       }
  }
  if (levelID == 8)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level8[row][col]);
          walls[row][col] = level8[row][col];
       }
  }
  if (levelID == 9)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level9[row][col]);
          walls[row][col] = level9[row][col];
       }
  }
  if (levelID == 10)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level10[row][col]);
          walls[row][col] = level10[row][col];
       }
  }
  if (levelID == 11)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level11[row][col]);
          walls[row][col] = level11[row][col];
       }
  }
  if (levelID == 12)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level12[row][col]);
          walls[row][col] = level12[row][col];
       }
  }
  if (levelID == 13)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level13[row][col]);
          walls[row][col] = level13[row][col];
       }
  }
  if (levelID == 14)
  {
    for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
       {
          lc.setLed (0, row, col, level14[row][col]);
          walls[row][col] = level14[row][col];
       }
  }

  x = levels[levelID].dotX;
  y = levels[levelID].dotY;
  lc.setLed (0, levels[levelID].dotX, levels[levelID].dotY, 1);
  dist (levels[levelID].dotX, levels[levelID].dotY, levels[levelID].objX, levels[levelID].objY);
  time = 350;
  lcd.setCursor (14, 1);
  lcd.print (time);
  levelTime = millis();
}

void winSound()
{
  setColor (0, 0, 0);
  tone (activeBuzzer, 880);
  delay (100);
  tone (activeBuzzer, 988);
  delay (100);
  tone (activeBuzzer, 523);
  delay (100);
  tone (activeBuzzer, 988);
  delay (100);
  tone (activeBuzzer, 523);
  delay (100);
  tone (activeBuzzer, 587);
  delay (100);
  tone (activeBuzzer, 659);
  delay (200);
  noTone (activeBuzzer);
}

void loseSound()
{
  setColor (0, 0, 0);
  tone (activeBuzzer, 392);
  delay (250);
  tone (activeBuzzer, 262);
  delay (500);
  noTone (activeBuzzer);
}

byte heart[] = {
  0x00,
  0x0A,
  0x1F,
  0x1F,
  0x0E,
  0x04,
  0x00,
  0x00
};

void setup()
{
  lcd.createChar (1, heart);
  lcd.begin (16, 2);

  lcd.print (" Welcome to my");
  lcd.setCursor (0,1);
  lcd.print (" game! Enjoy! ");
  lcd.write (1);

  screenID = -1;
  infoTime = millis();
  
  lc.shutdown (0, false);
  lc.setIntensity (0, brightness);
  lc.clearDisplay (0);
  
  pinMode (pinSW, INPUT_PULLUP);
  pinMode (pinJoySW, INPUT_PULLUP);

  levels[0].dotX = 3;
  levels[0].dotY = 0;
  levels[0].objX = 6;
  levels[0].objY = 4;

  levels[1].dotX = 0;
  levels[1].dotY = 0;
  levels[1].objX = 7;
  levels[1].objY = 5;

  levels[2].dotX = 7;
  levels[2].dotY = 0;
  levels[2].objX = 6;
  levels[2].objY = 5;
  
  levels[3].dotX = 0;
  levels[3].dotY = 0;
  levels[3].objX = 4;
  levels[3].objY = 0;

  levels[4].dotX = 3;
  levels[4].dotY = 7;
  levels[4].objX = 1;
  levels[4].objY = 0;

  levels[5].dotX = 0;
  levels[5].dotY = 0;
  levels[5].objX = 7;
  levels[5].objY = 2;

  levels[6].dotX = 7;
  levels[6].dotY = 3;
  levels[6].objX = 5;
  levels[6].objY = 7;

  levels[7].dotX = 5;
  levels[7].dotY = 7;
  levels[7].objX = 0;
  levels[7].objY = 3;

  levels[8].dotX = 0;
  levels[8].dotY = 7;
  levels[8].objX = 7;
  levels[8].objY = 3;

  levels[9].dotX = 0;
  levels[9].dotY = 0;
  levels[9].objX = 1;
  levels[9].objY = 7;

  levels[10].dotX = 0;
  levels[10].dotY = 0;
  levels[10].objX = 7;
  levels[10].objY = 4;

  levels[11].dotX = 0;
  levels[11].dotY = 0;
  levels[11].objX = 4;
  levels[11].objY = 3;

  levels[12].dotX = 0;
  levels[12].dotY = 0;
  levels[12].objX = 7;
  levels[12].objY = 6;

  levels[13].dotX = 1;
  levels[13].dotY = 7;
  levels[13].objX = 0;
  levels[13].objY = 0;

  levels[14].dotX = 0;
  levels[14].dotY = 0;
  levels[14].objX = 7;
  levels[14].objY = 4;

  hiScore1 = EEPROM.read (0) * 256 + EEPROM.read (1);
  EEPROM.write (0, 0);
  EEPROM.write (1, 0);
  hiScore2 = EEPROM.read (2) * 256 + EEPROM.read (3);
  EEPROM.write (2, 0);
  EEPROM.write (3, 0);
  hiScore3 = EEPROM.read (4) * 256 + EEPROM.read (5);
  EEPROM.write (4, 0);
  EEPROM.write (5, 0);
  for (int i = 0; i < 10; i++)
  {
    hiName1[i] = EEPROM.read (6 + i);
    hiName2[i] = EEPROM.read (16 + i);
    hiName3[i] = EEPROM.read (26 + i);
    EEPROM.write (6 + i, name[i]);
    EEPROM.write (16 + i, name[i]);
    EEPROM.write (26 + i, name[i]);
  }
}

void loop()
{
  xValue = analogRead (pinX);
  yValue = analogRead (pinY);
  if (xValue < minThreshold && joyMovedX == false) 
  {
    if (screenID == 0 && selection == 1)
    {
      lcd.setCursor (7, 0);
      lcd.print (" ");
      lcd.setCursor (0, 0);
      lcd.print (">");
      selection = 0;
    }
    else if (screenID == 0 && selection == 2)
    {
      lcd.setCursor (0, 1);
      lcd.print (" ");
      lcd.setCursor (7, 0);
      lcd.print (">");
      selection = 1;
    }
    else if (screenID == 0 && selection == 3)
    {
      lcd.setCursor (10, 1);
      lcd.print (" ");
      lcd.setCursor (0, 1);
      lcd.print (">");
      selection = 2;
    }
    else if (screenID == 2)
    {
      lcd.clear ();
      lcd.print (" Start >HiScore");
      lcd.setCursor (0, 1);
      lcd.print (" Settings  Info");
      selection = 1;
      screenID = 0;
    }
    else if (screenID == 3 && selection == 0 && selected == true && letterPlace > 0)
    {
      lcd.setCursor (7 + letterPlace, 0);
      lcd.print (name[letterPlace]);
      letterPlace--;
      lcd.setCursor (7 + letterPlace, 0);
      lcd.print (" ");
    }
    else if (screenID == 3 && selected == false)
    {
      lcd.clear ();
      lcd.print (" Start  HiScore");
      lcd.setCursor (0, 1);
      lcd.print (">Settings  Info");
      selection = 2;
      screenID = 0;
    }
    else if (screenID == 1 && y > 0 && walls[x][y-1]==0)
    {
      lc.setLed (0, x, y, 0);
      y--;
      dist (x, y, levels[levelID].objX, levels[levelID].objY);
    }
    else if (screenID == 6 && selection == 1)
    {
      lcd.setCursor (9, 1);
      lcd.print (" ");
      lcd.setCursor (1, 1);
      lcd.print (">");
      selection = 0;
    }
    joyMovedX = true;
    joyXTime = millis();
  }
  if (xValue > maxThreshold && joyMovedX == false)
  {
    if (screenID == 0 && selection == 0)
    {
      lcd.setCursor (0, 0);
      lcd.print (" ");
      lcd.setCursor (7, 0);
      lcd.print (">");
      selection = 1;
    }
    else if (screenID == 0 && selection == 1)
    {
      lcd.setCursor (7, 0);
      lcd.print (" ");
      lcd.setCursor (0, 1);
      lcd.print (">");
      selection = 2;
    }
    else if (screenID == 0 && selection == 2)
    {
      lcd.setCursor (0, 1);
      lcd.print (" ");
      lcd.setCursor (10, 1);
      lcd.print (">");
      selection = 3;
    }
    else if (screenID == 1 && y < 7 && walls[x][y+1]==0)
    {
      lc.setLed (0, x, y, 0);
      y++;
      dist (x, y, levels[levelID].objX, levels[levelID].objY);
    }
    else if (screenID == 3 && selection == 0 && selected == true && letterPlace < 8)
    {
      lcd.setCursor (7 + letterPlace, 0);
      lcd.print (name[letterPlace]);
      letterPlace++;
      lcd.setCursor (7 + letterPlace, 0);
      lcd.print (" ");
    }
    else if (screenID == 6 && selection == 0)
    {
      lcd.setCursor (1, 1);
      lcd.print (" ");
      lcd.setCursor (9, 1);
      lcd.print (">");
      selection = 1;
    }
    joyMovedX = true;
    joyXTime = millis();
  }
  if (millis() - joyXTime > joyResetTime)
  {
    joyMovedX = false;
  }
  
  if (yValue < minThreshold && joyMovedY == false) 
  {
    if (screenID == 2 && selection == 1)
    {
      lcd.clear ();
      lcd.print ("#1 ");
      lcd.print (hiName1);
      lcd.print (" ");
      lcd.print (hiScore1);
      lcd.setCursor (0,1);
      lcd.print ("#2 ");
      lcd.print (hiName2);
      lcd.print (" ");
      lcd.print (hiScore2);
      selection = 0;
    }
    else if (screenID == 3 && selection == 1 && selected == false)
    {
      lcd.setCursor (0, 1);
      lcd.print (" ");
      lcd.setCursor (0, 0);
      lcd.print (">");
      selection = 0;
    }
    else if (screenID == 3 && selection == 0 && selected == true && name[letterPlace] != '9')
    {
      if (name[letterPlace] == ' ') name[letterPlace] = 'A';
      else if (name[letterPlace] == 'Z') name[letterPlace] = '0';
      else name[letterPlace]++;
    }
    else if (screenID == 3 && selection == 1 && selected == true)
    {
      if (startingLevelValue < noOfLevels - 1) startingLevelValue++;
      lcd.setCursor (14, 1);
      lcd.print (startingLevelValue);
    }
    else if (screenID == 1 && x > 0 && walls[x-1][y]==0)
    {
      lc.setLed (0, x, y, 0);
      x--;
      dist (x, y, levels[levelID].objX, levels[levelID].objY);
    }
    joyMovedY = true;
    joyYTime = millis();
  }
  if (yValue > maxThreshold && joyMovedY == false)
  {
    if (screenID == 2 && selection == 0)
    {
      lcd.clear ();
      lcd.print ("#2 ");
      lcd.print (hiName2);
      lcd.print (" ");
      lcd.print (hiScore2);
      lcd.setCursor (0, 1);
      lcd.print ("#3 ");
      lcd.print (hiName3);
      lcd.print (" ");
      lcd.print (hiScore3);
      selection = 1;
    }
    else if (screenID == 3 && selection == 0 && selected == false)
    {
      lcd.setCursor (0, 0);
      lcd.print (" ");
      lcd.setCursor (0, 1);
      lcd.print (">");
      selection = 1;
    }
    else if (screenID == 3 && selection == 0 && selected == true && name[letterPlace] != ' ')
    {
      if (name[letterPlace] == 'A') name[letterPlace] = ' ';
      else if (name[letterPlace] == '0') name[letterPlace] = 'Z';
      else name[letterPlace]--;
    }
    else if (screenID == 3 && selection == 1 && selected == true)
    {
      if (startingLevelValue > 0) startingLevelValue--;
      lcd.setCursor (14, 1);
      lcd.print (startingLevelValue);
      lcd.print (" ");
    }
    else if (screenID == 1 && x < 7 && walls[x+1][y]==0)
    {
      lc.setLed (0, x, y, 0);
      x++;
      dist (x, y, levels[levelID].objX, levels[levelID].objY);
    }
    joyMovedY = true;
    joyYTime = millis();
  }
  if (millis() - joyYTime > joyResetTime)
  {
    joyMovedY = false;
  }

  joySwState = digitalRead(pinJoySW);
  if (joySwState !=  lastJoySwState && joySwState == LOW)
  {
    if ((screenID == 0 && selection == 0) || (screenID == 6 && selection == 0))
    {
      lcd.clear ();
      lcd.print ("Lives:");
      lcd.write (1);
      lcd.write (1);
      lcd.write (1);
      lcd.print (" Lvl:");
      lcd.print (startingLevelValue);
      lcd.setCursor (0, 1);
      lcd.print ("Score:0  Time:");
      setlevel (startingLevelValue);
      levelID = startingLevelValue;
      lives = 3;
      score = 0;
      screenID = 1;
    }
    else if (screenID == 0 && selection == 1)
    {
      lcd.clear ();
      lcd.print ("#1 ");
      lcd.print (hiName1);
      lcd.print (" ");
      lcd.print (hiScore1);
      lcd.setCursor (0, 1);
      lcd.print ("#2 ");
      lcd.print (hiName2);
      lcd.print (" ");
      lcd.print (hiScore2);
      selection = 0;
      screenID = 2;
    }
    else if (screenID == 0 && selection == 2)
    {
      lcd.clear ();
      lcd.print (">Name: ");
      lcd.print (name);
      lcd.setCursor (0, 1);
      lcd.print (" Start level: ");
      lcd.print (startingLevelValue);
      selection = 0;
      screenID = 3;
    }
    else if (screenID == 0 && selection == 3)
    {
      lcd.clear ();
      lcd.print ("   Bomberman");
      selection = 0;
      infoTime = millis();
      screenID = 4;
    }
    else if (screenID == 3 && selection == 0 && selected == false)
    {
      selected = true;
      letterPlace = 0;
      lcd.setCursor (7, 0);
      lcd.print (" ");
      selectedTime = millis();
    }
    else if (screenID == 3 && selection == 1 && selected == false)
    {
      selected = true;
      lcd.setCursor (0, 1);
      lcd.print (" ");
      selectedTime = millis();
    }
    else if (screenID == 3 && selection == 0 && selected == true)
    {
      selected = false;
      lcd.setCursor (7 + letterPlace, 0);
      lcd.print (name[letterPlace]);
    }
    else if (screenID == 3 && selection == 1 && selected == true)
    {
      selected = false;
      lcd.setCursor (0, 1);
      lcd.print (">");
    }
    else if (screenID == 1 && bombState == false)
    {
      bombX = x;
      bombY = y;
      bombBlinkState = true;
      bombState = true;
      bombTime = millis();
      bombBlinkTime = millis();

      detonationSound = true;
      detonationBetweenBeepsSound = millis();
      detonationVariableSound = millis();
      detonationBetweenBeeps = 500;
      tone (activeBuzzer, 700, 50);
    }
    else if (screenID == 6 && selection == 1)
    {
      lcd.clear ();
      lcd.print (">Start  HiScore");
      lcd.setCursor (0, 1);
      lcd.print (" Settings  Info");
      selection = 0;
      screenID = 0;
    }
  }
  lastJoySwState = joySwState;

  if (screenID == 3 && selection == 0 && selected == true && (millis() - selectedTime > selectedLength))
  {
    lcd.setCursor (7 + letterPlace, 0);
    if (selectedState == true)
    {
      lcd.print (" ");
      selectedState = false;
    }
    else
    {
      if (name[letterPlace] == ' ') lcd.print ('_');
      else lcd.print (name[letterPlace]);
      selectedState = true;
    }
    selectedTime = millis();
  }
  
  if (screenID == 3 && selection == 1 && selected == true && (millis() - selectedTime > selectedLength))
  {
    lcd.setCursor (0, 1);
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

  if (screenID == -1 && millis() - infoTime > infoLength)
  {
    lcd.clear ();
    lcd.print (">Start  HiScore");
    lcd.setCursor (0, 1);
    lcd.print (" Settings  Info");
    selection = 0;
    screenID = 0;
  }
  
  if (screenID == 4)
  {
    if (millis() - infoTime > infoLength)
    {
      if (selection == 0)
      {
        lcd.clear ();
        lcd.print ("     Stefan");
        lcd.setCursor (0, 1);
        lcd.print ("   Teodorescu");
      }
      else if (selection == 1)
      {
        lcd.clear ();
        lcd.print ("github.com/Stefi");
        lcd.setCursor (0, 1);
        lcd.print ("zard/Robotics");
      }
      else if (selection == 2)
      {
        lcd.clear ();
        lcd.print ("@UnibucRobotics");
      }
      else if (selection == 3)
      {
        lcd.clear ();
        lcd.print (" Start  HiScore");
        lcd.setCursor (0,1);
        lcd.print (" Settings >Info");
        selection = 2;
        screenID = 0;
      }
      selection++;
      infoTime = millis();
    }
  }
      
  if (screenID == 1)
  {
    if (millis() - playerTime > playerLength)
    {
      playerTime = millis();
      playerState = !playerState;
    }
    lc.setLed (0, x, y, playerState);
    
    if (x == levels[levelID].objX && y == levels[levelID].objY && millis() - ledTime > ledLength)
    {
      if (ledState == true)
      {
        setColor (0, 0, 0);
      }
      else setColor (255, 0, 0);
      ledState = !ledState;
      ledTime = millis ();
    }
  
    swState = digitalRead(pinSW);
    if (swState !=  lastSwState && swState == LOW)
    {
      lc.setLed (0, x, y, 1);
      if (x == levels[levelID].objX && y == levels[levelID].objY)
      {
        winSound();
        score = score + (1+ levelID/5) * time / 10;
        lcd.setCursor (6, 1);
        lcd.print (score);
        setlevel (++levelID);
        lcd.setCursor (14, 0);
        lcd.print (levelID);
      }
      else
      {
        loseSound();
        setlevel (levelID);
        lcd.setCursor (5 + lives--, 0);
        lcd.print (" ");
      }
    }
    lastSwState = swState;

    if (millis() - levelTime > levelLength)
    {
      time--;
      lcd.setCursor (14, 1);
      if (time < 90) lcd.print (" ");
      lcd.print (time + 10);
      levelTime = millis();
    }

    if (time == 0)
    {
      lcd.setCursor (15, 1);
      lcd.print (time);
      loseSound();
      setlevel (levelID);
      lcd.setCursor (5 + lives--, 0);
      lcd.print (" ");
    }
    
    if (bombState == true && millis() - bombBlinkTime > bombBlinkLength)
    {
      bombBlinkTime = millis();
      bombBlinkState = !bombBlinkState;
    }
    if (bombState == true && detonationState == false) lc.setLed (0, bombX, bombY, bombBlinkState);
    if (bombState == true && detonationState == false && millis() - bombTime > bombLength)
    {
      noTone (activeBuzzer);
      tone (activeBuzzer, 350, 200);
      detonationBetweenBeeps = 500;
      detonationSound = false;
    
      detonationState = true;
      detonationBlinkState = true;
      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          if (abs (bombX - i) + abs (bombY - j) <= 1)
          {
            walls[i][j] = 0;
          }
        }
      }
      detonationTime = millis();
      detonationBlinkTime = millis();
    }
  
    if (detonationSound == true && millis() - detonationBetweenBeepsSound > detonationBetweenBeeps)
    {
      noTone (activeBuzzer);
      tone (activeBuzzer, 700, 50);
      detonationBetweenBeepsSound = millis();
    }
    if (detonationSound == true && millis() - detonationVariableSound > detonationVariableSoundLength)
    {
      if (detonationBetweenBeeps == 500) detonationBetweenBeeps = 250;
      else if (detonationBetweenBeeps == 250) detonationBetweenBeeps = 100;
      detonationVariableSound = millis();
      noTone (activeBuzzer);
      tone (activeBuzzer, 700, 50);
      detonationBetweenBeepsSound = millis();
    }
    
    if (detonationState == true)
    {
      if (millis() - detonationBlinkTime > detonationBlinkLength)
      {
        detonationBlinkTime = millis();
        detonationBlinkState = !detonationBlinkState;
      }
      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          if (abs (bombX - i) + abs (bombY - j) <= 1)
          {
            lc.setLed (0, i, j, detonationBlinkState);
            if (i == x && j == y)
            {
              death = true;
              parcurgere = 1;
              for (int row = 0; row < 8; row++)
                for (int col = 0; col < 8; col++)
                  deathAnimation[row][col] = 0;
              deathAnimation[x][y] = parcurgere;
              while (death == true)
              {
                death = false;
                for (int row = 0; row < 8; row++)
                  for (int col = 0; col < 8; col++)
                  {
                    if (deathAnimation[row][col] == parcurgere) lc.setLed (0, row, col, 0);
                    if (deathAnimation[row][col] == 0 && ((col != 7 && deathAnimation[row][col+1] == parcurgere) || (col != 0 && deathAnimation[row][col-1] == parcurgere) || (row != 7 && deathAnimation[row+1][col] == parcurgere) || (row != 0 && deathAnimation[row-1][col] == parcurgere)))
                    {
                      lc.setLed (0, row, col, 1);
                      deathAnimation[row][col] = parcurgere + 1;
                      death = true;
                    }
                  }
                parcurgere++;
                delay (100);
              }
              loseSound();
              lcd.setCursor (5 + lives--, 0);
              lcd.print (" ");
              bombState = false;
              detonationState = false;
              setlevel (levelID);
              i = 7;
              j = 7;
            }
          }
        }
      }
      if (detonationState == true && millis() - detonationTime > detonationLength)
      {
        for (int i = 0; i < 8; i++)
        {
          for (int j = 0; j < 8; j++)
          {
            if (abs (bombX - i) + abs (bombY - j) <= 1)
            {
              lc.setLed (0, i, j, 0);
            }
          }
        }
        bombState = false;
        detonationState = false;
      }
    }
    
    if (lives == 0)
    {
      lc.clearDisplay (0);
      lcd.clear ();
      lcd.print ("   Game Over!");
      screenID = 5;
    }
    if (levelID == noOfLevels)
    {
      lc.clearDisplay (0);
      lcd.clear ();
      lcd.print (" Game Complete!");
      screenID = 5;
    }
  }

  if (screenID == 5)
  {
    if (infoState == false)
    {
      setColor (0, 0, 0);
      lcd.setCursor (0, 1);
      if (score > hiScore1)
      {
        lcd.print ("Yay! #1 HiScore!");
        hiScore3 = hiScore2;
        hiScore2 = hiScore1;
        hiScore1 = score;
        strcpy (hiName3, hiName2);
        strcpy (hiName2, hiName1);
        strcpy (hiName1, name);
      }
      else if (score > hiScore2)
      {
        lcd.print ("Yay! #2 HiScore!");
        hiScore3 = hiScore2;
        hiScore2 = score;
        strcpy (hiName3, hiName2);
        strcpy (hiName2, name);
      }
      else if (score > hiScore3)
      {
        lcd.print ("Yay! #3 HiScore!");
        hiScore3 = score;
        strcpy (hiName3, name);
      }
      else
      {
        lcd.print ("Wanna try again?");
      }
      EEPROM.write (0, hiScore1 / 256);
      EEPROM.write (1, hiScore1 % 256);
      EEPROM.write (2, hiScore2 / 256);
      EEPROM.write (3, hiScore2 % 256);
      EEPROM.write (4, hiScore3 / 256);
      EEPROM.write (5, hiScore3 % 256);
      for (int i = 0; i < 10; i++)
      {
        EEPROM.write (6 + i, hiName1[i]);
        EEPROM.write (16 + i, hiName2[i]);
        EEPROM.write (26 + i, hiName3[i]);
      }
      infoTime = millis();
      infoState = true;
    }
    if (infoState == true && millis() - infoTime > infoLength)
    {
      lcd.clear ();
      lcd.print ("Lvl:");
      lcd.print (levelID);
      lcd.setCursor (7, 0);
      lcd.print ("Score:");
      lcd.print (score);
      lcd.setCursor (0, 1);
      lcd.print (" >Again?  Menu");
      selection = 0;
      screenID = 6;
      infoState = false;
    }
  }
  delay (1);
}
