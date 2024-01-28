// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "rev/CANSparkMax.h"

class NoteHandler
{
public:
	bool SetHeight(float height, float maxRPM, float tolerance) {
		elevatorPID.SetSmartMotionMaxVelocity(maxRPM);
		elevatorPID.SetReference(height, rev::CANSparkMax::ControlType::kSmartMotion);
		return abs(height - e_elevator.GetPosition()) < tolerance;
	}

	bool SetAngle(float angle, float maxRPM, float tolerance) {
		anglePID.SetSmartMotionMaxVelocity(maxRPM);
		anglePID.SetReference(angle, rev::CANSparkMax::ControlType::kSmartMotion);
		return abs(angle - e_angle.GetPosition()) < tolerance;
	}

	void SetRollerSpeed(float inPerMin) {
		rollersPID.SetReference(inPerMin, rev::CANSparkMax::ControlType::kVelocity);
	}

	void Initialize() {
		m_elevator.RestoreFactoryDefaults();
		m_elevator.SetInverted(false);
		elevatorPID.SetP(0.2);
		elevatorPID.SetI(0);
		elevatorPID.SetD(1);
		elevatorPID.SetFF(0);
		elevatorPID.SetSmartMotionMaxAccel(2000);
		e_elevator.SetPositionConversionFactor(elevatorIPR);
		m_elevator.BurnFlash();

		m_angle.RestoreFactoryDefaults();
		m_angle.SetInverted(false);
		anglePID.SetP(0.2);
		anglePID.SetI(0);
		anglePID.SetD(1);
		anglePID.SetFF(0);
		anglePID.SetSmartMotionMaxAccel(2000);
		e_angle.SetPositionConversionFactor(angleDPR);
		m_angle.BurnFlash();

		m_rollers.RestoreFactoryDefaults();
		m_rollers.SetInverted(false);
		// PID for velocity control
		rollersPID.SetP(6e-5);
		rollersPID.SetI(1e-6);
		rollersPID.SetD(0);
		rollersPID.SetFF(0.000015);
		e_rollers.SetPositionConversionFactor(rollerIPR);
		m_rollers.BurnFlash();
	}

private:
	rev::CANSparkMax m_elevator{51, rev::CANSparkMax::MotorType::kBrushless};
	rev::SparkPIDController elevatorPID = m_elevator.GetPIDController();
	rev::SparkRelativeEncoder e_elevator = m_elevator.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor);

	rev::CANSparkMax m_angle{52, rev::CANSparkMax::MotorType::kBrushless};
	rev::SparkPIDController anglePID = m_angle.GetPIDController();
	rev::SparkRelativeEncoder e_angle = m_angle.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor);

	rev::CANSparkMax m_rollers{53, rev::CANSparkMax::MotorType::kBrushless};
	rev::SparkPIDController rollersPID = m_rollers.GetPIDController();
	rev::SparkRelativeEncoder e_rollers = m_rollers.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor);

	// elevator gearbox reduction
	const float elevatorGearboxReduction = 3;
	// inches per rotation of the motor
	const float elevatorIPR = 9/2.54/elevatorGearboxReduction;

	// note handler angle gearbox reduction
	const float angleGearboxReduction = 3;
	// degrees per rotation of the motor
	const float angleDPR = 1.0/360/3/elevatorGearboxReduction;

	const float rollerIPR = 1.225*M_PI;
};
