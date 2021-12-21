#include <Arduino.h>
#include <Arm.h>
#include <Joint.h>
#include <stdint.h>

// Main consts and variables
const uint8_t START_PIN = 22;
const uint8_t N_JOINTS = 3;
Joint base(nullptr, 22, 23, 0, 45, 15, XY);
Joint joint1(&base, 24, 25, 30, 150, 10, XZ);
Joint joint2(&joint1, 26, 27, 45, 90, 12, XZ);
Joint joint3(&joint2, 28, 29, 45, 90, 12, XZ);

Joint joints[MAX_JOINTS] = {base, joint1, joint2, joint3};
Arm arm(N_JOINTS, joints);

// Prototype functions
void stepMotors();
uint8_t motorsLeft();

void setup() { Serial.begin(9600); }

void loop() {
  arm.SetTipperPosition(1.0, 2.0, 3.0);
  arm.ReachTipperPosition();

  arm.SetTipperPosition(0.0, 0.0, 0.0);
  arm.ReachTipperPosition();
}
