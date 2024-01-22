// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "rev/CANSparkMax.h"
#include "ctre/phoenix6/CANcoder.hpp"
#include "ctre/phoenix6/TalonFX.hpp"
#include "complex"
using namespace std;

class SwerveModule
{
public:
	SwerveModule(int moduleID, complex<float> turnVector);

	void Set(complex<float> driveRate, float turnRate);

private:
	ctre::phoenix6::hardware::TalonFX *dMotor;
    ctre::phoenix6::hardware::CANcoder *encoder;
    rev::CANSparkMax *sMotor;
    complex<float> turnVector;
};
