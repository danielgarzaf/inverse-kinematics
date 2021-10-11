#include <BigStepper.h>
#include <stdint.h>

// Main consts and variables
const uint8_t START_PIN = 22;
const uint8_t N_MOTORS = 3;
BigStepper motor1(22, 23);
BigStepper motor2(24, 25);
BigStepper motor3(26, 27);
BigStepper stepperMotors[] = {motor1, motor2, motor3};

// Prototype functions
void stepMotors();
bool motorsReachedTargets();

void setup()
{
  // Serial.begin(9600);
}

void loop()
{
  uint8_t i = 1;
  for (BigStepper &motor : stepperMotors)
    motor.SetTargetAngle(45 * i++);
  stepMotors();
  for (BigStepper &motor : stepperMotors)
    motor.SetTargetAngle(0);
  stepMotors();
}

void stepMotors()
{
  while (!motorsReachedTargets())
  {
    uint8_t i = 1;
    for (BigStepper &motor : stepperMotors)
    {
      // Serial.print("\nStepping motor: ");
      // Serial.println(i++);

      motor.StepToTargetAngle();
    }
  }
}

bool motorsReachedTargets()
{
  bool result = true;
  for (BigStepper &motor : stepperMotors)
    result &= motor.HasReachedTarget();
  return result;
}