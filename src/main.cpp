#include <BigStepper.h>
#include <stdint.h>

// Main consts and variables
const uint8_t START_PIN = 22;
const uint8_t N_MOTORS = 3;
BigStepper stepperMotors[N_MOTORS];

// Prototype functions
void stepMotors();
bool motorsReachedTargets();

void setup()
{
  for (uint8_t i = START_PIN; i < START_PIN + 2 * N_MOTORS; i += 2)
    stepperMotors[i] = BigStepper(i, i + 1);
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
    for (BigStepper &motor : stepperMotors)
      motor.StepToTargetAngle();
  }
}

bool motorsReachedTargets()
{
  bool result = true;
  for (BigStepper &motor : stepperMotors)
    result &= motor.HasReachedTarget();
  return result;
}