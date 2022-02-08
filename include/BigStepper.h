#ifndef _BIG_STEPPER_H_
#define _BIG_STEPPER_H_
#define BIG_STEPPER_DELAY 5

#include <Arduino.h>
#include <stdint.h>

class BigStepper {
public:
  BigStepper();
  BigStepper(uint8_t driverDIR, uint8_t driverPUL);
  double GetCurrentAngle();
  double GetTargetAngle();
  uint8_t GetDriverDIR();
  uint8_t GetDriverPUL();
  bool HasReachedTarget();
  void Rotate(double deg);
  void SetMicrostepsPerStep(uint16_t microstepsPerStep);
  void SetPinDIR(uint8_t pin);
  void SetPinPUL(uint8_t pin);
  void SetStepsPerRev(uint16_t stepsPerRev);
  void SetTargetAngle(double targetAngle);
  void StepToTargetAngle(uint8_t _delay_ms);

protected:
  uint16_t m_microstepsPerStep;
  uint16_t m_stepsPerRev;
  uint8_t m_driverDIR;
  uint8_t m_driverPUL;
  double m_currentAngle;
  double m_targetAngle;

  void Step(uint8_t _delay_ms);

private:
  bool m_cw;
};

#endif /* _BIG_STEPPER_H_ */
