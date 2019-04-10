#include <DistanceSensor_Lib.h>
#include <ArdumotoDriver_Lib.h>


// constants
#define LEFT_MOTOR_INIT 0
#define RIGHT_MOTOR_INIT 1
#define SENSORPIN 3


// motors
ArdumotoDriverClass MotorLeft(LEFT_MOTOR_INIT);
ArdumotoDriverClass MotorRight(RIGHT_MOTOR_INIT);

// sensors
DistanceSensorClass Sensor1(SENSORPIN);


void setup()
{
    MotorLeft.setSpeed(255);
    MotorRight.setSpeed(255);
    delay(1000);
    MotorLeft.setSpeed(-255);
    MotorRight.setSpeed(-255);
    delay(1000);
    MotorLeft.setSpeed(0);
    MotorRight.setSpeed(0);
	Serial.begin(9600);
}

void loop()
{
    Serial.print(Sensor1.getDistanceRaw());
    Serial.print("/n");
    Serial.print(Sensor1.getDistanceVolt());
    Serial.print("/n");
    Serial.print(Sensor1.getDistanceCentimeter());
    Serial.print("/n");
    Serial.print("/n");
    delay(1000);

  /* add main program code here */

}
