#pragma once
#include <frc/TimedRobot.h>
#include "frc/XboxController.h"
#include "fmt/core.h"
#include "rev/CANSparkMax.h"
#include "ctre/phoenix6/CANcoder.hpp"
#include "ctre/phoenix6/TalonFX.hpp"
#include "AHRS.h"
using namespace std;
class SwerveModule {
private:
    ctre::phoenix6::hardware::TalonFX *dMotor;
    rev::CANSparkMax *sMotor;
    ctre::phoenix6::hardware::CANcoder *encoder;
    complex<float> turnVector;
public:
    SwerveModule(int moduleID, complex<float> turnVector) {
        dMotor = new ctre::phoenix6::hardware::TalonFX(10+moduleID, "rio");
        sMotor = new rev::CANSparkMax{30+moduleID, rev::CANSparkMax::MotorType::kBrushless};
        encoder = new ctre::phoenix6::hardware::CANcoder{20+moduleID};
        this->turnVector = turnVector;
    }
    void Set(complex<float> driveRate, float turnRate) {
        complex<float> moduleVector = driveRate+turnVector*turnRate;
        float error = arg(moduleVector) - encoder->GetAbsolutePosition().GetValue().value()*M_PI*2;
        if (error < -M_PI) { error += M_PI*2; }
        if (error > M_PI) { error -= M_PI*2; }

        dMotor->Set(abs(moduleVector));
        sMotor->Set(error / M_PI);
    }
};
class Robot : public frc::TimedRobot {
 private:
  frc::XboxController xBoxC{0};
 public:
  SwerveModule modules[4] ={
    SwerveModule{1, complex<float>(-1, -1)},
    SwerveModule{2, complex<float>(1, -1)},
    SwerveModule{3, complex<float>(-1, 1)},
    SwerveModule{4, complex<float>(1, 1)}};
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
