#include "Robot.h"
void Robot::RobotInit(){}
void Robot::RobotPeriodic() {}
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}
void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  swerve.Set(complex<float>(0,0.25), 0);//complex<float>(xBoxC.GetRawAxis(0), -xBoxC.GetRawAxis(1)), -xBoxC.GetRawAxis(2));
}
void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}
void Robot::TestInit() {}
void Robot::TestPeriodic() {}
void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
