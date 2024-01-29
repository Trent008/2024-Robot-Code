#pragma once
#include <frc/TimedRobot.h>
#include "fmt/core.h"
#include "subsystems/Swerve.h"
#include "subsystems/IntakeShooter.h"
#include "subsystems/NoteHandler.h"
#include "frc/XboxController.h"
using namespace std;

class Robot : public frc::TimedRobot
{
public:
	void RobotInit() override;
	void RobotPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void TestInit() override;
	void TestPeriodic() override;
	void SimulationInit() override;
	void SimulationPeriodic() override;
private:
	frc::Timer shooterTimer;
	// 0: stowed
	// 10: intaking
	// 20: shooter aiming
	// 21: shooting
	// 30: transferring
	// 40: climb step1
	// 41: climb step2
	// 42: climb step3
	int robotState = 0;
	Swerve swerve;
	IntakeShooter intakeShooter;
	NoteHandler noteHandler;
	frc::XboxController xc{0};
};