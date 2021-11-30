#ifndef _BIG_STEPPER_H_
#define _BIG_STEPPER_H_
#define BIG_STEPPER_DELAY 5

#include <Arduino.h>
#include <stdint.h>

class BigStepper {
public:
  BigStepper();
  BigStepper(uint8_t _driverPUL, uint8_t _driverDIR);
  void Rotate(double deg);
  void SetTargetAngle(double _targetAngle);
  void SetMicrostepsPerStep(uint16_t _microstepsPerStep);
  void SetStepsPerRev(uint16_t _stepsPerRev);
  void SetPinDIR(uint8_t pin);
  void SetPinPUL(uint8_t pin);
  void StepToTargetAngle(uint8_t delay_ms);
  bool HasReachedTarget();
  double GetCurrentAngle();
  double GetTargetAngle();
  uint8_t driverDIR;
  uint8_t driverPUL;

protected:
  double currentAngle;
  double targetAngle;
  uint16_t microstepsPerStep;
  uint16_t stepsPerRev;
  void Step(uint8_t delay_ms);

private:
  bool cw;
};

#endif
