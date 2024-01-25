// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "rev/CANSparkMax.h"

class NoteHandler
{
public:
	NoteHandler();

	void Initialize();
	bool SetHeight(float height, float maxRPM, float tolerance);
	bool SetAngle(float angle, float maxRPM, float tolerance);
	bool SetRollerSpeed(float speed);
	void SetRollerPosition(float position);


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
