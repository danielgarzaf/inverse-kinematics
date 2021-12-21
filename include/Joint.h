#ifndef _JOINT_H_
#define _JOINT_H_
#define JOINT_DELAY 200

#include <BigStepper.h>
#include <stdint.h>

typedef enum { XY, XZ } Plane_e;

class Joint : public BigStepper {
public:
  Joint();
  Joint(Joint *_parent, uint8_t _driverDIR, uint8_t _driverPUL,
        double _lowerLimit, double _upperLimit, double _len, Plane_e _plane);
  void StepToTargetAngle(uint8_t _delay_ms);
  void SetTargetAngle(double _targetAngle);
  bool TargetOutOfBounds();
  double x, y, z;

protected:
  Joint *parent = nullptr;
  Plane_e plane;

private:
  double len;
  double upperLimit;
  double lowerLimit;
  double *vec3d[3] = {&x, &y, &z};
  void UpdatePosition();
};

#endif /* _JOINT_H_ */
