
// Rainbarrel valve and pump control module
// Extension of the Motor driver shield- 2012 Copyright (c) Seeed Technology Inc.
//
//  Original Author: Jimbo.we
//  Contribution: LG
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

int pinI1 = 8; //define I1 interface
int pinI2 = 11; //define I2 interface
int speedpinA = 9; //enable motor A
int pinI3 = 12; //define I3 interface
int pinI4 = 13; //define I4 interface
int speedpinB = 10; //enable motor B
int spead = 127; //define the spead of motor

int inPin2 = 2;  
int inPin3 = 3; 

//int inValue2 = 0;
//int inValue3 = 0;
//int inValue5 = 0;
  
volatile int inValue2 = HIGH;      // The input state toggle
volatile int inValue3 = HIGH;      // The input state toggle

void setup()
{
  pinMode(pinI1, OUTPUT);
  pinMode(pinI2, OUTPUT);
  pinMode(speedpinA, OUTPUT);
  pinMode(pinI3, OUTPUT);
  pinMode(pinI4, OUTPUT);
  pinMode(speedpinB, OUTPUT);

//use input pullup to keep stray electricity from causing problem
  pinMode(inPin2, INPUT_PULLUP);
  pinMode(inPin3, INPUT_PULLUP);
//  pinMode(inPin2, INPUT);
//  pinMode(inPin3, INPUT);
//  pinMode(inPin5, INPUT);

  Serial.begin(9600); 
}

void forward() // Pump forward
{
  digitalWrite(pinI4, LOW); //turn DC Motor B move clockwise
  digitalWrite(pinI3, LOW);
  analogWrite(speedpinA, spead); //input a simulation value to set the speed
  analogWrite(speedpinB, spead);
  digitalWrite(pinI2, LOW); //turn DC Motor A move anticlockwise
  digitalWrite(pinI1, HIGH);
}
void backward()// Pump Backward
{
  digitalWrite(pinI4, LOW); //turn DC Motor B move anticlockwise
  digitalWrite(pinI3, LOW);
  analogWrite(speedpinA, spead); //input a simulation value to set the speed
  analogWrite(speedpinB, spead);
  digitalWrite(pinI2, HIGH); //turn DC Motor A move clockwise
  digitalWrite(pinI1, LOW);
}
void vopen()// open valve
{
  digitalWrite(pinI2, LOW); //turn DC Motor A move clockwise
  digitalWrite(pinI1, LOW);
  analogWrite(speedpinA, spead); //input a simulation value to set the speed
  analogWrite(speedpinB, spead);
  digitalWrite(pinI4, HIGH); //turn DC Motor B move clockwise
  digitalWrite(pinI3, LOW);
}
void vclose()// close valve
{
  digitalWrite(pinI2, LOW); //turn DC Motor A move clockwise
  digitalWrite(pinI1, LOW);
  analogWrite(speedpinA, spead); //input a simulation value to set the speed
  analogWrite(speedpinB, spead);
  digitalWrite(pinI4, LOW); //turn DC Motor B move anticlockwise
  digitalWrite(pinI3, HIGH);
}
void stop()//
{
  digitalWrite(speedpinA, LOW); // Unenble the pin, to stop the motor. this should be done to avid damaging the motor.
  digitalWrite(speedpinB, LOW);
  delay(1000);
}

void loop()
{

   inValue2 = digitalRead(inPin2); // open valve
   inValue3 = digitalRead(inPin3); // close valve
//   inValue5 = digitalRead(inPin5); // run pump

Serial.println(inValue2);
Serial.println(inValue3);
//Serial.println(inValue5);

  if (inValue2 == LOW && inValue3 == HIGH) {
    delay (400);
      if (inValue2 == LOW && inValue3 == HIGH) {    
        vopen();
        delay(3000);
        stop(); //  stop includes delay
      }
  }
  if (inValue2 == LOW && inValue3 == LOW) {
    delay (400);
    if (inValue2 == LOW && inValue3 == LOW) {
      forward(); // RUN PUMP
      delay(1000);
    }
  }
  if (inValue5 == HIGH) {
    stop();
  }
  if (inValue2 == HIGH && inValue3 == LOW) {
      delay (400);
      if (inValue2 == HIGH && inValue3 == LOW) {  
        vclose();
        delay(3000);
        stop();
      }
  }

  // IF I WANTED TO RUN PUMP IN REVERSE
  //  backward();
  //  delay(3000);
  //  stop();

//Serial.println (inValue2);
//Serial.println (inValue3);
//Serial.println (inValue5);
//delay(1000);
}


