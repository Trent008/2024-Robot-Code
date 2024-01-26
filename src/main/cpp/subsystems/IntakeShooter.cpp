// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/IntakeShooter.h"

IntakeShooter::IntakeShooter() = default;

bool IntakeShooter::SetAngle(float angle, float maxRPM = 1000, float tolerance = 3) {
    anglePID.SetSmartMotionMaxVelocity(maxRPM);
    anglePID.SetReference(angle, rev::CANSparkMax::ControlType::kSmartMotion);
    return abs(angle - e_angle.GetPosition()) < tolerance;
}

bool IntakeShooter::SetIntakeSpeed(float inPerMin) {
    intakePID.SetReference(inPerMin, rev::CANSparkMax::ControlType::kVelocity);
    return true; // todo: return value of note sensor
}

void IntakeShooter::Initialize() {
    m_intake.RestoreFactoryDefaults();
    m_intake.SetInverted(false);
    intakePID.SetP(6e-5);
    intakePID.SetI(1e-6);
    intakePID.SetD(0);
    intakePID.SetFF(0.000015);
    e_intake.SetPositionConversionFactor(intakeIPR);
    m_intake.BurnFlash();

    m1_shooter.RestoreFactoryDefaults();
    m1_shooter.SetInverted(false);
    shooterPID1.SetP(6e-5);
    shooterPID1.SetI(1e-6);
    shooterPID1.SetD(0);
    shooterPID1.SetFF(0.000015);
    e1_shooter.SetPositionConversionFactor(shooterIPR);
    m1_shooter.BurnFlash();

    m2_shooter.RestoreFactoryDefaults();
    m2_shooter.SetInverted(false);
    shooterPID2.SetP(6e-5);
    shooterPID2.SetI(1e-6);
    shooterPID2.SetD(0);
    shooterPID2.SetFF(0.000015);
    e2_shooter.SetPositionConversionFactor(shooterIPR);
    m2_shooter.BurnFlash();

    m_angle.RestoreFactoryDefaults();
    m_angle.SetInverted(false);
    anglePID.SetP(0.2);
    anglePID.SetI(0);
    anglePID.SetD(1);
    anglePID.SetFF(0);
    anglePID.SetSmartMotionMaxAccel(2000);
    e_angle.SetPositionConversionFactor(angleDPR);
    m_angle.BurnFlash();
}
