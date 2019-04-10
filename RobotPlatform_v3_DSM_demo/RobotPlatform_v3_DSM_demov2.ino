#include <DistanceSensor_Lib.h>
#include <ArdumotoDriver_Lib.h>
		//motor A = 0
		//motor B = 1
		//PWM control for motor output A is on digital pin 3
		//PWM control for motor output B is on digital pin 11
		//direction control for motor outputs A is on digital pin 12
		//direction control for motor outputs B is on digital pin 13


// constants
// motor 
#define RIGHT_MOTOR_INIT 0
#define LEFT_MOTOR_INIT 1

// distance sensor
#define SENSORPIN A3
#define CLOSEENOUGH 30

// bumper sensors
#define SENSORPINLEFT 4
#define SENSORPINRIGHT 5

// speed
#define NORMALSPEED 150
#define TURNSPEED 200
#define LEFTSPEEDFACTOR 1.02

// timers
#define NORMALDELAY 100
#define TURNSDELAY 300

// debugging
int DEBUGGING = 0;


// motors
ArdumotoDriverClass MotorLeft(LEFT_MOTOR_INIT);
ArdumotoDriverClass MotorRight(RIGHT_MOTOR_INIT);

// sensors
DistanceSensorClass Sensor1(SENSORPIN);


void setup()
{
    Serial.begin(9600);
    pinMode(SENSORPINLEFT, INPUT_PULLUP);    
    pinMode(SENSORPINRIGHT, INPUT_PULLUP);    
}

void loop()
{
// Initialize sensors

  boolean LeftHit = ! digitalRead(SENSORPINLEFT);
  boolean RightHit = ! digitalRead(SENSORPINRIGHT);
  boolean ToClose = Sensor1.getDistanceCentimeter() <= CLOSEENOUGH;

  if (DEBUGGING == 1)
  {
    Serial.print(Sensor1.getDistanceRaw());
    Serial.print("--");
    Serial.print(Sensor1.getDistanceVolt());
    Serial.print("--");
    Serial.print(Sensor1.getDistanceCentimeter());
    Serial.print("\n");
    delay(300);
  }
  else
  {

  // While no hit, run
  
      while (!(LeftHit || RightHit || ToClose))
      {
        MotorLeft.setSpeed(NORMALSPEED*LEFTSPEEDFACTOR);
        MotorRight.setSpeed(NORMALSPEED);
        delay(NORMALDELAY);
        LeftHit = ! digitalRead(SENSORPINLEFT);
        RightHit = ! digitalRead(SENSORPINRIGHT);
        ToClose = Sensor1.getDistanceCentimeter() <= CLOSEENOUGH;
      }
      MotorLeft.setSpeed(0);
      MotorRight.setSpeed(0);
      delay(NORMALDELAY);
    
      if (LeftHit)
      {
        MotorLeft.setSpeed(-TURNSPEED);
        MotorRight.setSpeed(-TURNSPEED);
        delay(TURNSDELAY);
        MotorLeft.setSpeed(0);
        delay(TURNSDELAY);
        MotorRight.setSpeed(0);
        delay(TURNSDELAY);
      }
      else
      {
        MotorLeft.setSpeed(-TURNSPEED);
        MotorRight.setSpeed(-TURNSPEED);
        delay(TURNSDELAY);
        MotorRight.setSpeed(0);
        delay(TURNSDELAY);
        MotorLeft.setSpeed(0);
        delay(TURNSDELAY);
      }
  }


}
