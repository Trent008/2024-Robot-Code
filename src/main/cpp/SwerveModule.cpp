// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "SwerveModule.h"
#include "angleMath.h"
using namespace std;

SwerveModule::SwerveModule(int moduleID, complex<float> turnVector) {
    dMotor = new ctre::phoenix6::hardware::TalonFX(10+moduleID, "rio");
    encoder = new ctre::phoenix6::hardware::CANcoder{20+moduleID};
    sMotor = new rev::CANSparkMax{30+moduleID, rev::CANSparkMax::MotorType::kBrushless};
    this->turnVector = turnVector;
}

void SwerveModule::Set(complex<float> driveRate, float turnRate) {
    complex<float> moduleVector = driveRate+turnVector*turnRate;
    float error = arg(moduleVector) - encoder->GetAbsolutePosition().GetValueAsDouble();
    limitAngle(error);
    dMotor->Set(abs(moduleVector));
    sMotor->Set(error / M_PI);
}