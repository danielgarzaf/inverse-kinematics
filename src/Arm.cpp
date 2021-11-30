#include <Arm.h>

Arm::Arm(const uint8_t _N_JOINTS, Joint (&_joints)[MAX_JOINTS]) {
  N_JOINTS = _N_JOINTS;
  for (uint8_t i = 0; i < N_JOINTS; i++) {
    Joint joint = _joints[i];
    m_joints[i] = joint;
  }
}

Joint *Arm::GetJoints() { return m_joints; }

void Arm::ReachTipperPosition() {
  uint8_t jointsLeft = JointsLeft();
  while (jointsLeft > 0) {
    for (Joint &joint : m_joints)
      joint.StepToTargetAngle(ARM_DELAY(jointsLeft));
    jointsLeft = JointsLeft();
  }
}

void Arm::ReachTipperPosition(double x, double y, double z) {
  SetTipperPosition(x, y, z);
  ReachTipperPosition();
}

uint8_t Arm::JointsLeft() {
  uint8_t result = 0;
  for (Joint &joint : m_joints) {
    if (!joint.HasReachedTarget())
      result++;
  }
  return result;
}

bool Arm::JointsReachedTarget() {
  bool result = true;
  for (Joint &joint : m_joints)
    result &= joint.HasReachedTarget();
  return result;
}

void Arm::PrintJointsAngle() {
  Serial.println("----------------------ANGLES--------------------------");
  for (uint8_t i = 0; i < N_JOINTS; i++) {
    Serial.print("Joint ");
    Serial.print(i);
    Serial.print(" Current Angle: ");
    Serial.println(m_joints[i].GetCurrentAngle());
  }
}

void Arm::PrintJointsPins() {
  Serial.println("-----------------------PINS--------------------------");
  for (uint8_t i = 0; i < N_JOINTS; i++) {
    Serial.print("driverDIR: ");
    Serial.print(m_joints[i].driverDIR);
    Serial.print("\tdriverPUL: ");
    Serial.println(m_joints[i].driverPUL);
  }
}

void Arm::SetTipperPosition(double x, double y, double z) {
  // array of angles for every joint
  double angles[MAX_JOINTS];
  InverseKinematics(x, y, z, angles);
  for (uint8_t i = 0; i < N_JOINTS; i++)
    m_joints[i].SetTargetAngle(angles[i]);
}

void Arm::InverseKinematics(double x, double y, double z,
                            double (&angles)[MAX_JOINTS]) {}
