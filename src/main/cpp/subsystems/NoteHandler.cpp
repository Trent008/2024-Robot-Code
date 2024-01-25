// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/NoteHandler.h"

NoteHandler::NoteHandler() = default;

void NoteHandler::Initialize() {
    // m_elevator.SetInverted(false);
    // elevatorPID.SetP(0.2);
    // elevatorPID.SetI(0);
    // elevatorPID.SetD(1);
    // elevatorPID.SetFF(0);
    // elevatorPID.SetSmartMotionAccelStrategy(rev::SparkMaxPIDController::AccelStrategy::kTrapezoidal);
    // elevatorPID.SetSmartMotionMaxAccel(2000);
    // elevatorPID.SetSmartMotionMaxVelocity(1000);
    // m_angle.SetInverted(false);
    // m_rollers.SetInverted(false);
}

bool NoteHandler::SetHeight(float height, float speed, float tolerance = 1) {
    // elevatorPID.SetReference(height/elevatorIPR, rev::ControlType::kSmartMotion);

}
