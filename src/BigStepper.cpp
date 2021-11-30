#include <BigStepper.h>

BigStepper::BigStepper() {}

BigStepper::BigStepper(uint8_t _driverPUL, uint8_t _driverDIR) {
  currentAngle = 0;
  targetAngle = 0;
  microstepsPerStep = 0;
  stepsPerRev = 200;
  driverPUL = _driverPUL;
  driverDIR = _driverDIR;
  cw = true;
  pinMode(driverPUL, OUTPUT);
  pinMode(driverDIR, OUTPUT);
}

bool BigStepper::HasReachedTarget() {
  return lrint(currentAngle) == lrint(targetAngle);
}

void BigStepper::SetPinDIR(uint8_t pin) {
  digitalWrite(driverDIR, LOW);
  driverDIR = pin;
  pinMode(pin, OUTPUT);
}

void BigStepper::SetPinPUL(uint8_t pin) {
  digitalWrite(driverPUL, LOW);
  driverPUL = pin;
  pinMode(pin, OUTPUT);
}

void BigStepper::Rotate(double deg) {
  SetTargetAngle(deg);
  while (!HasReachedTarget())
    StepToTargetAngle(BIG_STEPPER_DELAY);
}

void BigStepper::StepToTargetAngle(uint8_t _delay_ms) {
  if (HasReachedTarget())
    return;

  // Set direction to shortest path
  double diffAnglesCW = currentAngle - targetAngle;
  double diffAnglesCCW = 360 - currentAngle + targetAngle;
  if (abs(diffAnglesCW) > abs(diffAnglesCCW))
    cw = true;
  else
    cw = false;

  if (cw) {
    digitalWrite(driverDIR, LOW);
    currentAngle += 360 / (stepsPerRev + 0.0f);
  } else {
    digitalWrite(driverDIR, HIGH);
    currentAngle -= 360 / (stepsPerRev + 0.0f);
  }

  if (currentAngle > 360)
    currentAngle = fmod(currentAngle, 360); // Loop forward
  else if (currentAngle < 0)
    currentAngle = 360 + currentAngle; // Loop backward

  if (microstepsPerStep > 0)
    currentAngle /= (microstepsPerStep + 0.0f);

  Step(_delay_ms);
}

void BigStepper::Step(uint8_t _delay_ms) {
  digitalWrite(driverPUL, HIGH);
  delay(_delay_ms);
  digitalWrite(driverPUL, LOW);
  delay(_delay_ms);
}

void BigStepper::SetMicrostepsPerStep(uint16_t _microstepsPerStep) {
  microstepsPerStep = _microstepsPerStep;
}

void BigStepper::SetStepsPerRev(uint16_t _stepsPerRev) {
  stepsPerRev = _stepsPerRev;
}

void BigStepper::SetTargetAngle(double _targetAngle) {
  targetAngle = _targetAngle;
}

double BigStepper::GetCurrentAngle() { return currentAngle; }

double BigStepper::GetTargetAngle() { return targetAngle; }
