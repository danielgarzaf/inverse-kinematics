#ifndef _ARM_H_
#define _ARM_H_

#define MAX_JOINTS 6
#define ARM_DELAY(jointsLeft) (JOINT_DELAY) / (N_JOINTS - jointsLeft)

#include <Joint.h>

class Arm {
private:
  uint8_t JointsLeft();
  void InverseKinematics(double x, double y, double z,
                         double (&angles)[MAX_JOINTS]);
  uint8_t N_JOINTS;
  Joint m_joints[MAX_JOINTS];

public:
  Arm(const uint8_t _N_JOINTS, Joint (&_joints)[MAX_JOINTS]);
  bool JointsReachedTarget();
  void PrintJointsAngle();
  void PrintJointsPins();
  void ReachTipperPosition();
  void ReachTipperPosition(double x, double y, double z);
  void SetTipperPosition(double x, double y, double z);
  Joint *GetJoints();
};

#endif
