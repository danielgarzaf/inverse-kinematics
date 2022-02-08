#include <Joint.h>

Joint::Joint() {}

Joint::Joint(uint8_t driverDIR, uint8_t driverPUL, double lowerLimit,
             double upperLimit, double len, RotAxis_e axis) {
  SetupJoint(driverDIR, driverPUL, lowerLimit, upperLimit, len, axis);
}

Joint::Joint(Joint *parent, uint8_t driverDIR, uint8_t driverPUL,
             double lowerLimit, double upperLimit, double len, RotAxis_e axis) {
  m_parent = parent;
  SetupJoint(driverDIR, driverPUL, lowerLimit, upperLimit, len, axis);
}

void Joint::SetupJoint(uint8_t driverDIR, uint8_t driverPUL, double lowerLimit,
                       double upperLimit, double len, RotAxis_e axis) {
  m_driverDIR = driverDIR;
  m_driverPUL = driverPUL;
  m_lowerLimit = lowerLimit;
  m_currentAngle = lowerLimit;
  m_targetAngle = lowerLimit;
  m_upperLimit = upperLimit;
  m_len = len;
  m_axis = axis;
  UpdatePosition();
}

void Joint::StepToTargetAngle(uint8_t _delay_ms) {
  if (HasReachedTarget())
    return;

  if (m_currentAngle < m_targetAngle) {
    digitalWrite(m_driverDIR, LOW);
    m_currentAngle += 360 / (m_stepsPerRev + 0.0f);
  } else {
    digitalWrite(m_driverDIR, HIGH);
    m_currentAngle -= 360 / (m_stepsPerRev + 0.0f);
  }

  if (m_microstepsPerStep > 0)
    m_currentAngle /= (m_microstepsPerStep + 0.0f);

  UpdatePosition();
  Step(_delay_ms);
}

void Joint::SetTargetAngle(double targetAngle) {
  if (TargetOutOfBounds())
    return;
  m_targetAngle = targetAngle;
}

bool Joint::TargetOutOfBounds() {
  return (m_targetAngle < m_lowerLimit) || (m_targetAngle > m_upperLimit);
}

void Joint::UpdatePosition() {
  m_tipperPos[0] = m_len * cos(m_currentAngle);
  if (m_axis == Z) {
    m_tipperPos[1] = m_len * sin(m_currentAngle);
    m_tipperPos[2] = 0;
  } else if (m_axis == Y) {
    m_tipperPos[1] = 0;
    m_tipperPos[2] = m_len * sin(m_currentAngle);
  }

  Joint *tmpPar = m_parent;
  while (tmpPar) {
    vec3 tmpPos;
    tmpPar->GetPos(tmpPos);
    m_tipperPos[0] += tmpPar->m_tipperPos[0];
    m_tipperPos[1] += tmpPar->m_tipperPos[1];
    m_tipperPos[2] += tmpPar->m_tipperPos[2];
    tmpPar = tmpPar->m_parent;
  }
}

void Joint::GetPos(vec3 &pos) { copy_vec3(m_tipperPos, pos); }
