#ifndef _JOINT_H_
#define _JOINT_H_
#define JOINT_DELAY 200

#include "matrix.h"
#include <BigStepper.h>
#include <stdint.h>

typedef enum { X, Y, Z } RotAxis_e;

class Joint : public BigStepper {
public:
  RotAxis_e m_axis;
  Joint *m_parent = nullptr;

  Joint();
  Joint(uint8_t driverDIR, uint8_t driverPUL, double lowerLimit,
        double upperLimit, double len, RotAxis_e axis);
  Joint(Joint *parent, uint8_t driverDIR, uint8_t driverPUL, double lowerLimit,
        double upperLimit, double len, RotAxis_e axis);
  void SetupJoint(uint8_t driverDIR, uint8_t driverPUL, double lowerLimit,
                  double upperLimit, double len, RotAxis_e axis);
  void StepToTargetAngle(uint8_t _delay_ms);
  void SetTargetAngle(double targetAngle);
  bool TargetOutOfBounds();
  void GetPos(vec3 &pos);

private:
  vec3 m_tipperPos;
  double m_len;
  double m_upperLimit;
  double m_lowerLimit;

  void UpdatePosition();
};

#endif /* _JOINT_H_ */
