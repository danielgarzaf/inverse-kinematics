#include <Joint.h>

Joint::Joint() {}

Joint::Joint(Joint *_parent, uint8_t _driverDIR, uint8_t _driverPUL,
             double _lowerLimit, double _upperLimit, double _len,
             Plane_e _plane) {
  parent = _parent;
  driverDIR = _driverDIR;
  driverPUL = _driverPUL;
  lowerLimit = _lowerLimit;
  currentAngle = _lowerLimit;
  targetAngle = _lowerLimit;
  upperLimit = _upperLimit;
  len = _len;
  plane = _plane;
  UpdatePosition();
}

void Joint::StepToTargetAngle(uint8_t _delay_ms) {
  if (HasReachedTarget())
    return;

  if (currentAngle < targetAngle) {
    digitalWrite(driverDIR, LOW);
    currentAngle += 360 / (stepsPerRev + 0.0f);
  } else {
    digitalWrite(driverDIR, HIGH);
    currentAngle -= 360 / (stepsPerRev + 0.0f);
  }

  if (microstepsPerStep > 0)
    currentAngle /= (microstepsPerStep + 0.0f);

  UpdatePosition();
  Step(_delay_ms);
}

void Joint::SetTargetAngle(double _targetAngle) {
  if (TargetOutOfBounds())
    return;
  targetAngle = _targetAngle;
}

bool Joint::TargetOutOfBounds() {
  return (targetAngle < lowerLimit) || (targetAngle > upperLimit);
}

void Joint::UpdatePosition() {
  x = len * cos(currentAngle);
  if (plane == XY)
    y = len * sin(currentAngle);
  else if (plane == XZ)
    z = len * sin(currentAngle);

  if (parent) {
    x += parent->x;
    y += parent->y;
    z += parent->z;
  }
}
