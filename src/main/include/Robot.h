// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include "frc/XboxController.h"
#include "fmt/core.h"
#include "Swerve.h"

class Robot : public frc::TimedRobot {
 public:
  SwerveModule modules[4] =
  {
    SwerveModule{1, {-1, -1}},
    SwerveModule{2, {1, -1}},
    SwerveModule{3, {-1, 1}},
    SwerveModule{4, {1, 1}}};

  AHRS navx{frc::SPI::Port::kMXP};

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
  int i = 0;
  Swerve swerve;
};
