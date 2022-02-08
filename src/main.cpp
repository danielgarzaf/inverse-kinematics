#include <Arduino.h>
#include <Arm.h>
#include <Joint.h>
#include <matrix.h>
#include <stdint.h>

// Main consts and variables
const uint8_t N_JOINTS = 3;
Joint base(22, 23, 0, 45, 15, Z);
Joint joint1(&base, 24, 25, 30, 150, 10, Y);
Joint joint2(&joint1, 26, 27, 45, 90, 12, Y);
Joint joint3(&joint2, 28, 29, 45, 90, 12, Y);
Joint joints[MAX_JOINTS] = {base, joint1, joint2, joint3};
Arm arm(N_JOINTS, joints);

// Prototype functions
void stepMotors();
uint8_t motorsLeft();

void setup() { Serial.begin(9600); }

void loop() {
  vec3 pos = {1.0, 2.0, 3.0};
  arm.SetTipperPosition(pos);
  arm.ReachTipperPosition();
  vec3 pos2 = {0.0, 0.0, 0.0};
  arm.SetTipperPosition(pos2);
  arm.ReachTipperPosition();
}
