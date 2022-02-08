#include <Arm.h>

Arm::Arm(const uint8_t nJoints, Joint joints[MAX_JOINTS]) {
  m_nJoints = nJoints;
  for (uint8_t i = 0; i < m_nJoints; i++) {
    Joint joint = joints[i];
    m_joints[i] = joint;
  }
  SetRotationMatrix();
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

void Arm::ReachTipperPosition(vec3 pos) {
  SetTipperPosition(pos);
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

void Arm::PrintJointsAngles() {
  Serial.println("----------------------ANGLES--------------------------");
  for (uint8_t i = 0; i < m_nJoints; i++) {
    Serial.print("Joint ");
    Serial.print(i);
    Serial.print(" Angle: ");
    Serial.println(m_joints[i].GetCurrentAngle());
  }
}

void Arm::PrintJointsPins() {
  Serial.println("-----------------------PINS--------------------------");
  for (uint8_t i = 0; i < m_nJoints; i++) {
    Serial.print("Joint ");
    Serial.print(i);
    Serial.println(":");
    Serial.print("\tdriverDIR: ");
    Serial.print(m_joints[i].GetDriverDIR());
    Serial.print("  driverPUL: ");
    Serial.println(m_joints[i].GetDriverPUL());
  }
}

void Arm::SetTipperPosition(vec3 pos) {
  // array of angles for every joint
  double angles[MAX_JOINTS];
  InverseKinematics(pos, angles);
  for (uint8_t i = 0; i < m_nJoints; i++)
    m_joints[i].SetTargetAngle(angles[i]);
}

void Arm::SetRotationMatrix() {
  Joint *currJoint = &m_joints[m_nJoints - 1]; // Start at tipper joint
  while (currJoint) {
    double currentAngle = currJoint->GetCurrentAngle();
    if (currJoint->m_axis == X) {
      mat3 rotX = ROT_MAT3_X(currentAngle);
      mult_mat3(rotX, m_rotMatrix);
    } else if (currJoint->m_axis == Y) {
      mat3 rotY = ROT_MAT3_Y(currentAngle);
      mult_mat3(rotY, m_rotMatrix);
    } else if (currJoint->m_axis == Z) {
      mat3 rotZ = ROT_MAT3_Z(currentAngle);
      mult_mat3(rotZ, m_rotMatrix);
    }
    currJoint = currJoint->m_parent;
  }
}

/* TODO: Most important method to implement */
void Arm::InverseKinematics(vec3 v3, double angles[MAX_JOINTS]) {}
