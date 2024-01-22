#pragma once
#include <frc/TimedRobot.h>
#include "frc/XboxController.h"
#include "fmt/core.h"
#include "AHRS.h"
#include "SwerveModule.h"
using namespace std;
void limitAngle(float &angle) {
    if (angle < -M_PI) { angle += M_PI*2; }
    if (angle > M_PI) { angle -= M_PI*2; }
}

class Robot : public frc::TimedRobot {
 private:
  frc::XboxController xBoxC{0};
 public:
  SwerveModule modules[4] ={
    SwerveModule(1, complex<float>(-1, -1)),
    SwerveModule(2, complex<float>(1, -1)),
    SwerveModule(3, complex<float>(-1, 1)),
    SwerveModule(4, complex<float>(1, 1))};
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
};