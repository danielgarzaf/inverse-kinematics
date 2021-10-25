#include <Arm.h>

Arm::Arm(const uint8_t _N_JOINTS, Joint (&_joints)[MAX_JOINTS]) {
  N_JOINTS = _N_JOINTS;
  for (uint8_t i = 0; i < N_JOINTS; i++) {
    Joint joint = _joints[i];
    joints[i] = joint;
  }
}

Joint *Arm::GetJoints() { return joints; }

void Arm::ReachTipperPosition() {
  uint8_t jointsLeft = JointsLeft();
  while (jointsLeft > 0) {
    for (Joint &joint : joints)
      joint.StepToTargetAngle(JOINT_DELAY / (N_JOINTS - jointsLeft));
    jointsLeft = JointsLeft();
  }
}

uint8_t Arm::JointsLeft() {
  uint8_t result = 0;
  for (Joint &joint : joints) {
    if (!joint.HasReachedTarget())
      result++;
  }
  return result;
}

bool Arm::JointsReachedTarget() {
  bool result = true;
  for (Joint &joint : joints)
    result &= joint.HasReachedTarget();
  return result;
}

void Arm::PrintJointsAngle() {
  Serial.println("----------------------ANGLES--------------------------");
  for (uint8_t i = 0; i < N_JOINTS; i++) {
    Serial.print("Joint Current Angle ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(joints[i].GetCurrentAngle());
  }
}

void Arm::PrintJointsPins() {
  Serial.println("-----------------------PINS--------------------------");
  for (uint8_t i = 0; i < N_JOINTS; i++) {
    Serial.print("driverDIR: ");
    Serial.print(joints[i].driverDIR);
    Serial.print("\tdriverPUL: ");
    Serial.println(joints[i].driverPUL);
  }
}

void Arm::SetTipperPosition(double (&vec3d)[3]) {
  SetTipperPosition(vec3d[0], vec3d[1], vec3d[2]);
}

void Arm::SetTipperPosition(double x, double y, double z) {
  // array of angles for every joint
  double angles[MAX_JOINTS];
  InverseKinematics(x, y, z, angles);
  for (uint8_t i = 0; i < N_JOINTS; i++)
    joints[i].SetTargetAngle(angles[i]);
}

void Arm::InverseKinematics(double (&vec3d)[3], double (&angles)[MAX_JOINTS]) {}

void Arm::InverseKinematics(double x, double y, double z,
                            double (&angles)[MAX_JOINTS]) {}
