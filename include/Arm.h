#ifndef _ARM_H_
#define _ARM_H_

#define MAX_JOINTS 6

#include <Joint.h>

class Arm
{
public:
    uint8_t N_JOINTS;

public:
    Arm(const uint8_t _N_JOINTS, Joint (&_joints)[MAX_JOINTS]);
    void PrintJointsPins();
    void MoveArmToPosition();
    void SetTipperPosition(double (&vec3d)[3]);
    void SetTipperPosition(double x, double y, double z);
    Joint *GetJoints();
    double *InverseKinematics(double x, double y, double z);

private:
    Joint joints[MAX_JOINTS];
};

#endif