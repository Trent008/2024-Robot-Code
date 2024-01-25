// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "rev/CANSparkMax.h"

class IntakeShooter
{
public:
	IntakeShooter();
	void Initialize();
	void SetIntake();
	void SetAngle();
	void SetShooter();
	bool GetSensor();
	
private:
	rev::CANSparkMax m_intake{41, rev::CANSparkMax::MotorType::kBrushless};
	rev::SparkPIDController intakePID = m_intake.GetPIDController();
	rev::SparkRelativeEncoder e_intake = m_intake.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor);

	rev::CANSparkMax m1_shooter{42, rev::CANSparkMax::MotorType::kBrushless};
	rev::SparkPIDController shooterPID1 = m1_shooter.GetPIDController();
	rev::SparkRelativeEncoder e1_shooter = m1_shooter.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor);

	rev::CANSparkMax m2_shooter{43, rev::CANSparkMax::MotorType::kBrushless};
	rev::SparkPIDController shooterPID2 = m2_shooter.GetPIDController();
	rev::SparkRelativeEncoder e2_shooter = m2_shooter.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor);

	rev::CANSparkMax m_angle{44, rev::CANSparkMax::MotorType::kBrushless};
	rev::SparkPIDController anglePID = m_angle.GetPIDController();
	rev::SparkRelativeEncoder e_angle = m_angle.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor);
	
	const float IntakeGearboxReduction = 3;
	// inches per rotation of the intake motor
	const float intakeIPR = M_PI*2/IntakeGearboxReduction;
	// inches per rotation of the shooter motors
	const float shooterIPR = M_PI*4;

	const float IntakeGearboxReduction = 3;
	// degrees per rotation of the angle motor
	const float angleDPR = 1.0/360/3;
};
