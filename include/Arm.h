#ifndef _ARM_H_
#define _ARM_H_

#define MAX_JOINTS 6
#define JOINT_DELAY 200

#include <Joint.h>

class Arm {
private:
  uint8_t N_JOINTS;
  Joint joints[MAX_JOINTS];

public:
  Arm(const uint8_t _N_JOINTS, Joint (&_joints)[MAX_JOINTS]);
  bool JointsReachedTarget();
  uint8_t JointsLeft();
  void PrintJointsAngle();
  void PrintJointsPins();
  void ReachTipperPosition();
  void SetTipperPosition(double (&vec3d)[3]);
  void SetTipperPosition(double x, double y, double z);
  Joint *GetJoints();

private:
  void *InverseKinematics(double (&vec3d)[3], double (&angles)[MAX_JOINTS]);
  void *InverseKinematics(double x, double y, double z,
                          double (&angles)[MAX_JOINTS]);
};

#endif
