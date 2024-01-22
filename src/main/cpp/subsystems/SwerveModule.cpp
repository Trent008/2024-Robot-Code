// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SwerveModule.h"
#include "angleMath.h"
using namespace std;

SwerveModule::SwerveModule(int ID, complex<float> position) {
    m_drive = new ctre::phoenix6::hardware::TalonFX(10+ID, "rio");
    e_twist = new ctre::phoenix6::hardware::CANcoder{20+ID, "rio"};
    m_twist = new rev::CANSparkMax(30+ID, rev::CANSparkMax::MotorType::kBrushless);
    ctre::phoenix6::configs::TalonFXConfiguration configs{};
    configs.Slot1.kP = 5;
    configs.Slot1.kI = 0.1;
    configs.Slot1.kD = 0.001;
    m_drive->GetConfigurator().Apply(configs);
    turn_vector = position * complex<float>(0, 1) / abs(position);
}

void SwerveModule::Set(complex<float> robot_vel, float turn_rate) {
    complex<float> velocity = GetVelocity(robot_vel, turn_rate);
    float m_drive_rate = abs(velocity);
    if (m_drive_rate < 0.001) {
        float error = arg(velocity) - e_twist->GetAbsolutePosition().GetValueAsDouble();
        wrap(error);
        if (abs(error) > M_PI/2) {
            error += M_PI;
            wrap(error);
            m_drive_rate = -m_drive_rate;
        }
        SetMotorRate(m_drive_rate);
        m_twist->Set(error / M_PI);
    } else {
        SetMotorRate(0);
        m_twist->Set(0);
    }
}

complex<float> SwerveModule::GetVelocity(complex<float> robot_vel, float turn_rate) {
    return robot_vel + turn_vector * turn_rate;
}

void SwerveModule::SetMotorRate(float rate) {
    auto friction_torque = (rate > 0) ? 1_A : -1_A;
    m_drive->SetControl(m_drive_PID.WithVelocity(rate*101_tps).WithFeedForward(friction_torque));
}