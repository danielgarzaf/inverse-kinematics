#include <Joint.h>

Joint::Joint() {}

Joint::Joint(uint8_t _driverDIR, uint8_t _driverPUL, double _lowerLimit,
             double _upperLimit, double _len) {
  driverDIR = _driverDIR;
  driverPUL = _driverPUL;
  lowerLimit = _lowerLimit;
  currentAngle = _lowerLimit;
  targetAngle = _lowerLimit;
  upperLimit = _upperLimit;
  len = _len;
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
