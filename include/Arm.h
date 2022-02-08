#ifndef _ARM_H_
#define _ARM_H_

#define MAX_JOINTS 6
#define ARM_DELAY(jointsLeft) (JOINT_DELAY) / (m_nJoints - jointsLeft)

#include <Joint.h>
#include <matrix.h>

class Arm {
public:
  Arm(const uint8_t _nJoints, Joint _joints[MAX_JOINTS]);
  bool JointsReachedTarget();
  void PrintJointsAngles();
  void PrintJointsPins();
  void ReachTipperPosition();
  void ReachTipperPosition(vec3 pos);
  void SetTipperPosition(vec3 pos);
  void SetRotationMatrix();
  Joint *GetJoints();

private:
  void InverseKinematics(vec3 v3, double angles[MAX_JOINTS]);
  uint8_t JointsLeft();

  uint8_t m_nJoints;
  Joint m_joints[MAX_JOINTS];
  mat3 m_rotMatrix = MAT3_IDENTITY_INIT;
};

#endif /* _ARM_H_ */
