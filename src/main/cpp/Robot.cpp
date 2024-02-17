#include "Robot.h"
void Robot::RobotInit(){}
void Robot::RobotPeriodic() {}
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}
void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  if (!isShooting) {
    if (xc.GetAButtonPressed()) {
      isIntaking = !isIntaking;
    }
    else if (xc.GetBButton()) {
      isIntaking = false;
      isAiming = true;
    }
  }

  swerve.set(complex<float>(xc.GetLeftX(), -xc.GetLeftY()), -xc.GetRightX());
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
