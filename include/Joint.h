#ifndef _JOINT_H_
#define _JOINT_H_

#include <BigStepper.h>
#include <stdint.h>

class Joint : public BigStepper {
public:
  Joint();
  Joint(uint8_t _driverDIR, uint8_t _driverPUL, double _lowerLimit,
        double _upperLimit, double _len);
  void StepToTargetAngle(uint8_t _delay_ms);
  void SetTargetAngle(double _targetAngle);
  bool TargetOutOfBounds();
  double GetX();
  double GetY();
  double GetZ();

private:
  double len;
  double upperLimit;
  double lowerLimit;
  double x, y, z;
  double *vec3d[3] = {&x, &y, &z};
};

#endif
