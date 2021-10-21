#include <Arduino.h>
#include <Arm.h>
#include <Joint.h>
#include <stdint.h>

// Main consts and variables
const uint8_t START_PIN = 22;
const uint8_t N_JOINTS = 3;
Joint joint1(22, 23, 0, 45, 15);
Joint joint2(24, 25, 30, 150, 10);
Joint joint3(26, 27, 45, 90, 12);
Joint joints[MAX_JOINTS] = {joint1, joint2, joint3};
Arm arm(N_JOINTS, joints);

// Prototype functions
void stepMotors();
bool motorsReachedTargets();

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  uint8_t i = 1;
  for (Joint &joint : joints)
    joint.SetTargetAngle(45 * i++);
  stepMotors();
  for (Joint &joint : joints)
    joint.SetTargetAngle(0);
  stepMotors();
}

void stepMotors()
{
  while (!motorsReachedTargets())
  {
    uint8_t i = 0;
    for (Joint &joint : joints)
    {
      // Delay must be inversely proportional to the number of motors left to reach target. This avoids motors fluctuating in speed
      if (joint.HasReachedTarget())
        i++;
      uint8_t delay = 200 / (N_JOINTS - i);
      joint.StepToTargetAngle(delay);
    }
  }
}

bool motorsReachedTargets()
{
  bool result = true;
  for (Joint &joint : joints)
    result &= joint.HasReachedTarget();
  return result;
}
