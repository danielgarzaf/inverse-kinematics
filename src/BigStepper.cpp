#include <BigStepper.h>

BigStepper::BigStepper(uint8_t _driverPUL, uint8_t _driverDIR)
{
    currentAngle = 0;
    targetAngle = 0;
    microstepsPerStep = 0;
    stepsPerRev = 200;
    driverPUL = _driverPUL;
    driverDIR = _driverDIR;
    pinMode(driverPUL, OUTPUT);
    pinMode(driverDIR, OUTPUT);
}

bool BigStepper::HasReachedTarget()
{
    return lrint(currentAngle) == lrint(targetAngle);
}

void BigStepper::SetPinDIR(uint8_t pin)
{
    digitalWrite(driverDIR, LOW);
    driverDIR = pin;
    pinMode(pin, OUTPUT);
}

void BigStepper::SetPinPUL(uint8_t pin)
{
    digitalWrite(driverPUL, LOW);
    driverPUL = pin;
    pinMode(pin, OUTPUT);
}

void BigStepper::Rotate(double deg)
{
    SetTargetAngle(deg);
    while (!HasReachedTarget())
    {
        StepToTargetAngle();
    }
}

void BigStepper::StepToTargetAngle()
{
    if (HasReachedTarget())
        return;

    if (currentAngle < targetAngle)
    {
        digitalWrite(driverDIR, LOW);
        currentAngle += 360 / stepsPerRev;
    }
    else if (currentAngle > targetAngle)
    {
        digitalWrite(driverDIR, HIGH);
        currentAngle -= 360 / stepsPerRev;
    }

    if (currentAngle < 0)
        currentAngle *= -1;

    if (microstepsPerStep > 0)
        currentAngle /= microstepsPerStep;

    Step();
}

void BigStepper::Step()
{
    digitalWrite(driverPUL, HIGH);
    delay(20);
    digitalWrite(driverPUL, LOW);
    delay(20);
}

void BigStepper::SetMicrostepsPerStep(double _microstepsPerStep)
{
    microstepsPerStep = _microstepsPerStep;
}

void BigStepper::SetStepsPerRev(double _stepsPerRev)
{
    stepsPerRev = _stepsPerRev;
}

void BigStepper::SetTargetAngle(double angle)
{
    targetAngle = angle;
}

void BigStepper::PrintAnglesArduino()
{
    Serial.println("-----------------------------------------");
    Serial.print("currentAngle: ");
    Serial.print(currentAngle);
    Serial.print("\ttargetAngle: ");
    Serial.println(targetAngle);
}