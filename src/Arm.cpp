#include <Arm.h>

Arm::Arm(const uint8_t _N_JOINTS, Joint (&_joints)[MAX_JOINTS])
{
    N_JOINTS = _N_JOINTS;
    for (uint8_t i = 0; i < N_JOINTS; i++)
    {
        Joint joint = _joints[i];
        joints[i] = joint;
    }
}

void Arm::PrintJointsPins()
{
    Serial.println("-----------------------------------------------------");
    for (uint8_t i = 0; i < N_JOINTS; i++)
    {
        Serial.print("driverDIR: ");
        Serial.print(joints[i].driverDIR);
        Serial.print("\tdriverPUL: ");
        Serial.println(joints[i].driverPUL);
    }
}

Joint *Arm::GetJoints()
{
    return joints;
}

void Arm::SetTipperPosition(double (&vec3d)[3])
{
    SetTipperPosition(vec3d[0], vec3d[1], vec3d[2]);
}

void Arm::SetTipperPosition(double x, double y, double z)
{
    double *angles = InverseKinematics(x, y, z); // array of angles for every joint
    for (uint8_t i = 0; i < N_JOINTS; i++)
    {
    }
}

double *Arm::InverseKinematics(double x, double y, double z)
{
}
