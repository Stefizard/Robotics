const int en1Pin = 11;
const int in1Pin = 10;
const int in2Pin = 9;
const int en2Pin = 3;
const int in3Pin = 5;
const int in4Pin = 6;
const int s[5] = {A0, A1, A2, A3, A4}; //there are only 5 sensors used
int val;
bool line[5];

const int threshold = 500;
const int fast = 250;
const int slow = 100;
bool last = 0;
bool moved = 0;

void isLine()
{
  for (int i = 0; i < 5; i++)
  {
    val = analogRead(s[i]);
    if (val > threshold) line[i] = 1;
    else line[i] = 0;
  }
  //Serial.println(" ");
}

void setup() {
  digitalWrite (in1Pin, LOW);
  digitalWrite (in2Pin, HIGH);
  digitalWrite (in3Pin, HIGH);
  digitalWrite (in4Pin, LOW);
  analogWrite (en1Pin, 0);
  analogWrite (en2Pin, 0);
  Serial.begin (9600);
}

void loop() {
  isLine(); //reading the line values and determining if there is a line at each sensor
  moved = 0;
  if (line[0] || line[4])
  {
    if (line[0] && !line[4])
    {
      hardLeft();
      last = 0;
      moved = 1;
    }

    if (!line[0] && line[4])
    {
      hardRight();
      last = 1;
      moved = 1;
    }
  }

  if ((line[1] || line[3]) && !moved)
  {
    if (line[1] && !line[3])
    {
      slightLeft();
      last = 0;
      moved = 1;
    }

    if (!line[1] && line[3])
    {
      slightRight();
      last = 1;
      moved = 1;
    }
  }

  if (line[2] && !moved)
  {
    forward();
    moved = 1;
  }
  if (!moved) //if there is no line on the sensor, repeat the last curve taken
  {
    if (last == 0){
      hardLeft();
    }
    if (last == 1){
      hardRight();
    }
  }
  delay (10);
}

void forward()
{
    digitalWrite (in1Pin, LOW);
    digitalWrite (in2Pin, HIGH);
    digitalWrite (in3Pin, HIGH);
    digitalWrite (in4Pin, LOW);
    analogWrite (en1Pin, fast);
    analogWrite (en2Pin, fast);
}

void slightRight()
{
    digitalWrite (in1Pin, LOW);
    digitalWrite (in2Pin, HIGH);
    digitalWrite (in3Pin, HIGH);
    digitalWrite (in4Pin, LOW);
    analogWrite (en1Pin, fast);
    analogWrite (en2Pin, slow);
}

 void hardRight()
 {
    digitalWrite (in1Pin, LOW);
    digitalWrite (in2Pin, HIGH);
    digitalWrite (in3Pin, LOW);
    digitalWrite (in4Pin, HIGH);
    analogWrite (en1Pin, fast); //forward
    analogWrite (en2Pin, slow); //backward
 }

void slightLeft()
{
    digitalWrite (in1Pin, LOW);
    digitalWrite (in2Pin, HIGH);
    digitalWrite (in3Pin, HIGH);
    digitalWrite (in4Pin, LOW);
    analogWrite (en1Pin, slow);
    analogWrite (en2Pin, fast);
}
void hardLeft()
{
    digitalWrite (in1Pin, HIGH);
    digitalWrite (in2Pin, LOW);
    digitalWrite (in3Pin, HIGH);
    digitalWrite (in4Pin, LOW);
    analogWrite (en1Pin, slow); //backward
    analogWrite (en2Pin, fast); //forward
}
