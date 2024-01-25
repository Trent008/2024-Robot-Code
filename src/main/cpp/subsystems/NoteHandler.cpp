// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/NoteHandler.h"

NoteHandler::NoteHandler() = default;

// set the elevator height (0 to 20 inches)
bool NoteHandler::SetHeight(float height, float maxRPM = 1000, float tolerance = 1) {
    elevatorPID.SetSmartMotionMaxVelocity(maxRPM);
    elevatorPID.SetReference(height, rev::ControlType::kSmartMotion);
    return abs(height - e_elevator.GetPosition()) < tolerance;
}

// set the angle in degrees of the note handler arm
bool NoteHandler::SetAngle(float angle, float maxRPM = 1000, float tolerance = 3) {
    anglePID.SetSmartMotionMaxVelocity(maxRPM);
    anglePID.SetReference(angle, rev::ControlType::kSmartMotion);
    return abs(angle - e_angle.GetPosition()) < tolerance;
}

bool NoteHandler::SetRollerSpeed(float speed) {
    m_rollers.Set(speed);
    return true; // todo: return the note sensor value
}

// set the position of the rollers relative to they're current position (only use once)
void NoteHandler::SetRollerPosition(float position) {
    e_rollers.SetPosition(0);
    rollersPID.SetReference(position, rev::ControlType::kPosition);
}

void NoteHandler::Initialize() {
    m_elevator.RestoreFactoryDefaults();
    m_elevator.SetInverted(false);
    elevatorPID.SetP(0.2);
    elevatorPID.SetI(0);
    elevatorPID.SetD(1);
    elevatorPID.SetFF(0);
    elevatorPID.SetSmartMotionAccelStrategy(rev::SparkMaxPIDController::AccelStrategy::kTrapezoidal);
    elevatorPID.SetSmartMotionMaxAccel(2000);
    e_elevator.SetPositionConversionFactor(elevatorIPR);
    m_elevator.BurnFlash();

    m_angle.RestoreFactoryDefaults();
    m_angle.SetInverted(false);
    anglePID.SetP(0.2);
    anglePID.SetI(0);
    anglePID.SetD(1);
    anglePID.SetFF(0);
    anglePID.SetSmartMotionAccelStrategy(rev::SparkMaxPIDController::AccelStrategy::kTrapezoidal);
    anglePID.SetSmartMotionMaxAccel(2000);
    e_angle.SetPositionConversionFactor(angleDPR);
    m_angle.BurnFlash();

    m_rollers.RestoreFactoryDefaults();
    m_rollers.SetInverted(false);
    rollersPID.SetP(0.2);
    rollersPID.SetI(0);
    rollersPID.SetD(1);
    rollersPID.SetFF(0);
    e_rollers.SetPositionConversionFactor(rollerIPR);
    m_rollers.BurnFlash();
}
