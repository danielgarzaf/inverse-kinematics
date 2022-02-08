#include <BigStepper.h>

/********************* CONSTRUCTORS **************************/
BigStepper::BigStepper() {}

BigStepper::BigStepper(uint8_t _driverDIR, uint8_t _driverPUL) {
  m_currentAngle = 0;
  m_targetAngle = 0;
  m_microstepsPerStep = 0;
  m_stepsPerRev = 200;
  m_driverDIR = _driverDIR;
  m_driverPUL = _driverPUL;
  m_cw = true;
  pinMode(m_driverPUL, OUTPUT);
  pinMode(m_driverDIR, OUTPUT);
}
/****************** CONSTRUCTORS END ***********************/

/********************* PUBLIC *******************************/
uint8_t BigStepper::GetDriverDIR() { return m_driverDIR; }

uint8_t BigStepper::GetDriverPUL() { return m_driverPUL; }

double BigStepper::GetCurrentAngle() { return m_currentAngle; }

double BigStepper::GetTargetAngle() { return m_targetAngle; }

bool BigStepper::HasReachedTarget() {
  return lrint(m_currentAngle) == lrint(m_targetAngle);
}

void BigStepper::Rotate(double deg) {
  SetTargetAngle(deg);
  while (!HasReachedTarget())
    StepToTargetAngle(BIG_STEPPER_DELAY);
}

void BigStepper::SetMicrostepsPerStep(uint16_t microstepsPerStep) {
  m_microstepsPerStep = microstepsPerStep;
}

void BigStepper::SetPinDIR(uint8_t pin) {
  digitalWrite(m_driverDIR, LOW);
  m_driverDIR = pin;
  pinMode(pin, OUTPUT);
}

void BigStepper::SetPinPUL(uint8_t pin) {
  digitalWrite(m_driverPUL, LOW);
  m_driverPUL = pin;
  pinMode(pin, OUTPUT);
}

void BigStepper::SetStepsPerRev(uint16_t stepsPerRev) {
  m_stepsPerRev = stepsPerRev;
}

void BigStepper::SetTargetAngle(double targetAngle) {
  m_targetAngle = targetAngle;
}

void BigStepper::StepToTargetAngle(uint8_t _delay_ms) {
  if (HasReachedTarget())
    return;

  // Set direction to shortest path
  double diffAnglesCW = m_currentAngle - m_targetAngle;
  double diffAnglesCCW = 360 - m_currentAngle + m_targetAngle;
  if (abs(diffAnglesCW) > abs(diffAnglesCCW))
    m_cw = true;
  else
    m_cw = false;

  if (m_cw) {
    digitalWrite(m_driverDIR, LOW);
    m_currentAngle += 360 / (m_stepsPerRev + 0.0f);
  } else {
    digitalWrite(m_driverDIR, HIGH);
    m_currentAngle -= 360 / (m_stepsPerRev + 0.0f);
  }

  if (m_currentAngle > 360)
    m_currentAngle = fmod(m_currentAngle, 360); // Loop forward
  else if (m_currentAngle < 0)
    m_currentAngle = 360 + m_currentAngle; // Loop backward

  if (m_microstepsPerStep > 0)
    m_currentAngle /= (m_microstepsPerStep + 0.0f);

  Step(_delay_ms);
}
/****************** PUBLIC END **************************/

/****************** PROTECTED **************************/
void BigStepper::Step(uint8_t _delay_ms) {
  digitalWrite(m_driverPUL, HIGH);
  delay(_delay_ms);
  digitalWrite(m_driverPUL, LOW);
  delay(_delay_ms);
}
/*************** PROTECTED END **************************/
