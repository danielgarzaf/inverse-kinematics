#ifndef _BIG_STEPPER_H_
#define _BIG_STEPPER_H_

#include <Arduino.h>
#include <stdint.h>

class BigStepper
{
public:
    uint8_t driverDIR;
    uint8_t driverPUL;

private:
    double currentAngle;
    double targetAngle;
    uint16_t microstepsPerStep;
    uint16_t stepsPerRev;

public:
    BigStepper();
    BigStepper(uint8_t _driverPUL, uint8_t _driverDIR);
    void Rotate(double deg);
    void SetTargetAngle(double angle);
    void SetMicrostepsPerStep(uint16_t _microstepsPerStep);
    void SetStepsPerRev(uint16_t _stepsPerRev);
    void SetPinDIR(uint8_t pin);
    void SetPinPUL(uint8_t pin);
    void StepToTargetAngle();
    bool HasReachedTarget();

private:
    void Step();
    void PrintAnglesArduino();
};

#endif