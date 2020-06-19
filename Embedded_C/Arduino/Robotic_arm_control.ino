#include <VarSpeedServo.h>
#include <SoftwareSerial.h>



SoftwareSerial bluetooth(12, 13);

VarSpeedServo Left_Shoulder;// create servo object to control a servo
VarSpeedServo Left_Elbow;
VarSpeedServo Right_Shoulder;
VarSpeedServo Right_Elbow;
VarSpeedServo Head;



int bluetooth_data;
int i;
int j;
int AVR_DATA;
//-------------------Status LEDs------------------
int Green_LED = 7;
int Blue_LED = 2;
int RED_LED = 8;
int Deleveriy_LED = 0;

//-------------------Servo motors------------------
float Left_Arm_Angles_Ref = 90;
float Right_Shoulder_Ref = 0;
float Right_Elbow_Ref = 68;
float Servo_Motor_Speed[] = {0, 10.8, 34, 59, 77, 83, 77, 59, 34, 10, 0};
int Medium_Speed = 70;
float Left_Arm_Angles_Del[] = {90, 89.4, 87, 81, 74, 65, 56, 48, 43, 41, 40};
float Right_Shoulder_Angles_Del[] = {0, 0.43, 2.9, 8.2, 16, 25, 34.1, 42, 47, 49.5, 50};
float Right_Elbow_Angles_Del[] = {77, 77.5, 80, 85, 93, 102, 111, 119, 124, 126.5, 127};
float Left_Elbow_Angles_Elbow_Up[] = {40, 40.5, 44, 50.6, 60.6, 75.5, 84.4, 94.4, 101.2, 104.4, 105};
float Right_Elbow_Angles_Elbow_Up[] = {127, 126.5, 122, 115.4, 105.4, 90, 81, 71, 64, 62.2, 61.6};
int pose;
//--------------------Ultrasonic sensor--------------
const int trigPin = A1;
const int echoPin = A0;
long duration;
int distance;



void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  // pinMode(13, OUTPUT);
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);

  Left_Shoulder.attach(9);
  Left_Elbow.attach(10);
  Right_Shoulder.attach(3);
  Right_Elbow.attach(5);
  Head.attach(6);


  pinMode(Blue_LED, OUTPUT);
  pinMode(Green_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  Left_Shoulder.write(90, Medium_Speed , true);
  Left_Elbow.write(90, Medium_Speed , true);
  Right_Shoulder.write(0, Medium_Speed , true);
  Right_Elbow.write(70, Medium_Speed , true);
  Head.write(50, 40, true);



  digitalWrite(Blue_LED, HIGH);
  //--------------------Ultrasonic sensor--------------
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  delay(150);
  if (distance <= 50)
  {
    digitalWrite(Blue_LED, LOW); //Active state is running continously
    digitalWrite(Green_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    Serial.write('5');
    distance = 50;

  }
  else
  {
    digitalWrite(Blue_LED, HIGH); //Active state is running continously
    digitalWrite(Green_LED, LOW);
    digitalWrite(RED_LED, LOW);

  }

  if (Deleveriy_LED == 1 )
  {
    digitalWrite(Blue_LED, LOW); //Active state is running continously
    digitalWrite(Green_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }
 

  delay(20);
  if (bluetooth.available() > 0)
  {
    bluetooth_data = bluetooth.read();

    switch (bluetooth_data)
    {
      case '1':
        Serial.write('1');//move forward

        break;

      case '2':
        Serial.write('2');//move backward

        break;

      case '3':
        Serial.write('3');//rotate clock wise

        break;
      case '4':
        Serial.write('4');//rotate counter clock wise

        break;
      case '5':
        Serial.write('5');//Stop

        break;
      //-----------------Refrence Pose(General)-------------------_No Array_
      case 'R':
        Left_Shoulder.write(80, Medium_Speed , true);
        Left_Elbow.write(90, Medium_Speed , true);
        Right_Shoulder.write(0, Medium_Speed , true);
        Right_Elbow.write(70, Medium_Speed , true);

        break;
      //-----------------Refrence Pose_ After the Delivery pose-------------------
      case 'C':
        for (i = 0; i < 11; i++)
        {
          Left_Shoulder.write(80, Servo_Motor_Speed[i] , true);
          Left_Elbow.write(85, Servo_Motor_Speed[i] , true);
          Right_Shoulder.write(0, Servo_Motor_Speed[i] , true);
          Right_Elbow.write(77, Servo_Motor_Speed[i] , true);
        }

        break;
      //-----------------Delivery Path-------------------
      case 'D':
        for (i = 0; i < 11; i++)
        {
          Left_Shoulder.write((Left_Arm_Angles_Del[i] - 12), Servo_Motor_Speed[i] , true);
          Right_Shoulder.write(Right_Shoulder_Angles_Del[i], Servo_Motor_Speed[i] , true);
         
          Left_Elbow.write((Left_Arm_Angles_Del[i] + 10), Servo_Motor_Speed[i] , true);
          Right_Elbow.write((Right_Elbow_Angles_Del[i] - 20), Servo_Motor_Speed[i] , true);
          
        }

        Deleveriy_LED = 1;
        break;
      //-----------------Return Path----------------------------
      case 'B':
        for (i = 0; i < 11; i++)
        {
          Right_Shoulder.write(Right_Shoulder_Angles_Del[10 - i], Servo_Motor_Speed[i] , true);
          //delay(1000);
          Left_Shoulder.write(Left_Arm_Angles_Del[10 - i], Servo_Motor_Speed[i] , true);


          Right_Elbow.write((Right_Elbow_Angles_Del[10 - i]), Servo_Motor_Speed[i] , true);
          
          Left_Elbow.write((Left_Arm_Angles_Del[10 - i] - 8), Servo_Motor_Speed[i] , true);

        }

        
        Deleveriy_LED = 0;

        break;

      //-----------------Arms Down_ Greeting Mode-------------------
      case 'F':
        Left_Shoulder.write(90, Medium_Speed , true);
        Right_Shoulder.write(0, Medium_Speed , true);
        for (j = 0; j < 2; j++)
        {
          for (i = 0; i < 11; i++)
          {
            Left_Elbow.write((Left_Elbow_Angles_Elbow_Up[i]), Servo_Motor_Speed[i] , true);
            Right_Elbow.write((Left_Elbow_Angles_Elbow_Up[10 - i]), Servo_Motor_Speed[i] , true);
          }
          for (i = 0; i < 11; i++)
          {
            Left_Elbow.write((Left_Elbow_Angles_Elbow_Up[10 - i]), Servo_Motor_Speed[i] , true);
            Right_Elbow.write((Left_Elbow_Angles_Elbow_Up[i] + 30), Servo_Motor_Speed[i] , true);
          }


        }
        break;

      //-----------------Head Control-------------------_No Array_
      case 'H':


        for (pose = 10; pose <= 115; pose += 1) { // goes from 0 degrees to 180 degrees

          Head.write(pose, 80, true);            // tell servo to go to position in variable 'pos'
                              // waits 15ms for the servo to reach the position
        }
        for (pose = 115; pose >= 10; pose -= 1) { // goes from 180 degrees to 0 degrees
          Head.write(pose, 80, true);              // tell servo to go to position in variable 'pos'
                               // waits 15ms for the servo to reach the position
        }

        Head.write(50, 40, true);
        break;

        //---------------------Dancing Mode-------------------------
              case 'A':
                Serial.write('1');//move forward
        
                break;
        
              case 'B':
                Serial.write('1');//move forward
        
                break;
        
              case 'C':
                Serial.write('1');//move forward
        
                break;
        //--------------------------------------------------------



    }


  }



}
