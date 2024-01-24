#pragma once
#include <frc/TimedRobot.h>
#include "fmt/core.h"
#include "subsystems/Swerve.h"
#include "frc/XboxController.h"
using namespace std;

class Robot : public frc::TimedRobot
{
private:
	Swerve swerve;

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
	frc::XboxController xBoxC{0};
};