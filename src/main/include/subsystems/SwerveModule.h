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
	SwerveModule(int ID, complex<float> position);

	void Set(complex<float> robot_vel, float turn_rate);

    complex<float> GetVelocity(complex<float> robot_vel, float turn_rate);


private:
    // set the motor's velocity PID to a portion of its max velocity
    void SetMotorRate(float rate);

    // motor that drives the wheel
	ctre::phoenix6::hardware::TalonFX *m_drive;
    // encoder that measures wheel angle
    ctre::phoenix6::hardware::CANcoder *e_twist;
    // motor that drives wheel angle
    rev::CANSparkMax *m_twist;
    // velocity controller for the drive motor
    ctre::phoenix6::controls::VelocityTorqueCurrentFOC m_drive_PID{0_tps};
    // vector to make this module turn the robot about it's center
    complex<float> turn_vector;
};
