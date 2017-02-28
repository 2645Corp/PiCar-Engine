#include <Servo.h>
/*
   指令：
   S  停止
   F  前进
   B  后退
   L  左转
   R  右转
   Eaaabbb  设置速度，aaa和bbb分别为a通道和b通道的速度
   Cxxxyyy  设置舵机角度，xxx和yyy分别为x舵机和y舵机的速度
*/
char buff[6];
int a_1 = 2, a_2 = 3, a_e = 5;
int b_1 = 4, b_2 = 7, b_e = 6;
int servo_x = 9, servo_y = 10;
int testTime = 1000;
Servo servox, servoy;

void setup() {
  servox.attach(9);
  servoy.attach(10);
  pinMode(a_1, OUTPUT);
  pinMode(a_2, OUTPUT);
  pinMode(a_e, OUTPUT);
  pinMode(b_1, OUTPUT);
  pinMode(b_2, OUTPUT);
  pinMode(b_e, OUTPUT);

  Stop();
  SetSpeed(100, 100);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() >= 1)
  {
    Serial.readBytes(buff, 1);
    switch (buff[0])
    {
      case 'S':
        Serial.println("Stop");
        Stop();
        break;
      case 'F':
        Serial.println("Forward");
        Forward();
        break;
      case 'B':
        Serial.println("Backward");
        Backward();
        break;
      case 'L':
        Serial.println("Left");
        Left();
        break;
      case 'R':
        Serial.println("Right");
        Right();
        break;
      case 'C':
        delay(10);
        if (Serial.available() >= 6)
        {
          Serial.readBytes(buff, 6);
          int x = convert(buff, buff + 2), y = convert(buff + 3, buff + 5);
          if (x >= 0 && x <= 180 && y >= 0 && y <= 180)
          {
            servox.write(x);
            servoy.write(y);
            Serial.println("Servo driven");
          }
          else
            Serial.println("Angle out of range");
        }
        break;
      case 'E':
        delay(10);
        if (Serial.available() >= 6)
        {
          Serial.readBytes(buff, 6);
          int sa = convert(buff, buff + 2), sb = convert(buff + 3, buff + 5);
          if (sa >= 0 && sa <= 255 && sb >= 0 && sb <= 255)
          {
            SetSpeed(sa, sb);
            Serial.println("Speed set");
          }
          else
            Serial.println("Speed out of range");
        }
        break;
    }
  }
}

void SetSpeed(int a, int b)
{
  analogWrite(a_e, a);
  analogWrite(b_e, b);
}

void Forward()
{
  digitalWrite(a_1, 0);
  digitalWrite(a_2, 1);
  digitalWrite(b_1, 0);
  digitalWrite(b_2, 1);
}

void Backward()
{
  digitalWrite(a_1, 1);
  digitalWrite(a_2, 0);
  digitalWrite(b_1, 1);
  digitalWrite(b_2, 0);
}

void Left()
{
  digitalWrite(a_1, 0);
  digitalWrite(a_2, 1);
  digitalWrite(b_1, 1);
  digitalWrite(b_2, 0);
}

void Right()
{
  digitalWrite(a_1, 1);
  digitalWrite(a_2, 0);
  digitalWrite(b_1, 0);
  digitalWrite(b_2, 1);
}

void Stop()
{
  digitalWrite(a_1, 0);
  digitalWrite(a_2, 0);
  digitalWrite(b_1, 0);
  digitalWrite(b_2, 0);
}

int convert(char* bg, char* ed)
{
  int t = 0;
  while (bg <= ed)
  {
    t = t * 10 + *bg - '0';
    ++bg;
  }
  return t;
}

void Test()
{
  Forward();
  delay(testTime);
  Backward();
  delay(testTime);
  Left();
  delay(testTime);
  Right();
  delay(testTime);
}

