// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "complex"

void Robot::RobotInit(){}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic(){}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic()
{
  complex<float> driveRate = complex<float>(xBoxC.GetLeftX(), -xBoxC.GetLeftY())*0.5f;
  float turnRate = -xBoxC.GetRightX()*0.5;
  for (int i = 0; i < 4; i++)
  {
      modules[i].Set(driveRate*polar<float>(1, navx.GetYaw()*M_PI/180), turnRate);
  }
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
