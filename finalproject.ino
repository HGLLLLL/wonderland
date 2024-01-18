#include <SoftwareSerial.h>
#include <Wire.h>

char moterstatus;
SoftwareSerial BT(13 , 12);

int IR_Objects_Left = 7; //紅外線接
int IR_Objects_Mid = 6; //紅外線接
int IR_Objects_Right = 5; //紅外線接
int motor_Left1 = 4;
int motor_Left2 = 3;
int motor_Right1 = 9;
int motor_Right2 = 8;
int left_pwm = 11;
int right_pwm = 10;

int IR_Delay = 500;
int IR_Left = 0;
int IR_Mid = 0;
int IR_Right = 0;

int state = 0;

void setup() 
{
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(IR_Objects_Left, INPUT); //定義紅外線為輸入端
  pinMode(IR_Objects_Mid, INPUT); //定義紅外線為輸入端
  pinMode(IR_Objects_Right, INPUT); //定義紅外線為輸入端
  pinMode(motor_Left1,OUTPUT);
  pinMode(motor_Left2,OUTPUT);
  pinMode(motor_Right1,OUTPUT);
  pinMode(motor_Right2,OUTPUT);
  pinMode(left_pwm ,OUTPUT);
  pinMode(right_pwm ,OUTPUT);
}
void moveForward()
{
	digitalWrite(motor_Left2,HIGH);
	digitalWrite(motor_Left1,LOW);
  digitalWrite(motor_Right2,HIGH);
	digitalWrite(motor_Right1,LOW);
  analogWrite(right_pwm, 99);	
	analogWrite(left_pwm, 100);	
  delay(180);
  Stop();
}
void moveBack()
{
  digitalWrite(motor_Left2,LOW);
	digitalWrite(motor_Left1,HIGH);
  digitalWrite(motor_Right2,LOW);
	digitalWrite(motor_Right1,HIGH);
  analogWrite(right_pwm, 90);	
	analogWrite(left_pwm, 90);
  delay(140);
  Stop();	
}
void moveLeft()
{
	digitalWrite(motor_Left2,LOW);
	digitalWrite(motor_Left1,LOW);
  digitalWrite(motor_Right2,HIGH);
	digitalWrite(motor_Right1,LOW);
  analogWrite(right_pwm, 90);	
	analogWrite(left_pwm, 115);	
  delay(200);
  Stop();	
}
void moveLeftSmall()
{
	digitalWrite(motor_Left2,LOW);
	digitalWrite(motor_Left1,LOW);
  digitalWrite(motor_Right2,HIGH);
	digitalWrite(motor_Right1,LOW);
  analogWrite(right_pwm, 90);	
	analogWrite(left_pwm, 95);	
  delay(200);
  Stop();	
}
void moveRight()
{
	digitalWrite(motor_Left2,HIGH);
	digitalWrite(motor_Left1,LOW);
  digitalWrite(motor_Right2,LOW);
	digitalWrite(motor_Right1,LOW);
  analogWrite(right_pwm, 105);	
	analogWrite(left_pwm, 90);
  delay(200);
  Stop();	
}
void moveRightSmall()
{
	digitalWrite(motor_Left2,HIGH);
	digitalWrite(motor_Left1,LOW);
  digitalWrite(motor_Right2,LOW);
	digitalWrite(motor_Right1,LOW);
  analogWrite(right_pwm, 70);	
	analogWrite(left_pwm, 90);
  delay(150);
  Stop();	
}
void Stop()
{
	digitalWrite(motor_Left1,LOW);
  digitalWrite(motor_Left2,LOW);
	digitalWrite(motor_Right1,LOW);
  digitalWrite(motor_Right2,LOW);
} 

void loop()
{
  if(state == 0)
  {
    delay(IR_Delay); // 延遲時間等於IR作動時
  
    IR_Mid = digitalRead(IR_Objects_Mid); 
    IR_Left = digitalRead(IR_Objects_Left); 
    IR_Right = digitalRead(IR_Objects_Right);
  
    if(IR_Mid == LOW && IR_Left == HIGH && IR_Right == HIGH ) //假設紅外線等於高電平
    {
      Serial.println("Mid_yes");
      delay(IR_Delay);
      moveForward();
    }

    if(IR_Mid == HIGH && IR_Left == LOW && IR_Right == HIGH ) //假設紅外線等於高電平
    {
      Serial.println("Left_yes");
      delay(IR_Delay);
      moveLeft();
    }

    IR_Right = digitalRead(IR_Objects_Right); 
    if(IR_Mid == HIGH && IR_Left == HIGH && IR_Right == LOW ) //假設紅外線等於高電平
    {
      Serial.println("Right_yes");
      delay(IR_Delay);
      moveRight();
    }

    if(IR_Mid == LOW && IR_Left == LOW && IR_Right == LOW)
    {
      Serial.println("Stop");
      delay(IR_Delay);
      Stop();
      state = 1;
    }
    if(IR_Mid == LOW && IR_Left == LOW && IR_Right == HIGH)
    {
      Serial.println("Stop");
      delay(IR_Delay);
      Stop();
      state = 1;
    }
    if(IR_Mid == LOW && IR_Left == HIGH && IR_Right == LOW)
    {
      Serial.println("Stop");
      delay(IR_Delay);
      Stop();
      state = 1;
    }

    if(IR_Mid == HIGH && IR_Left == HIGH && IR_Right == HIGH)
    {
      Serial.println("back");
      delay(IR_Delay);
      moveRightSmall();
      delay(500);
    }
    if(IR_Mid == HIGH && IR_Left == HIGH && IR_Right == HIGH)
    {
      moveLeftSmall();
      delay(500);
    }

  }
  else if(state == 1)
  {
    if(BT.available())
    {
    moterstatus=BT.read();
    Serial.println(moterstatus);
    }
    switch(moterstatus)
    {
      case 'F':
      moveForward();
      Serial.println(moterstatus);
      break;

      case 'B':
      moveBack();
      Serial.println(moterstatus);
      break;

      case 'L':
      moveLeft();
      Serial.println(moterstatus);
      break;

      case 'R':
      moveRight();
      Serial.println(moterstatus);
      break;

      case '0':
      Stop();
      Serial.println(moterstatus);
      break;
      }
  }
}
