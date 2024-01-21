#pragma once
#include "rev/CANSparkMax.h"
#include "ctre/phoenix6/CANcoder.hpp"
#include "ctre/phoenix6/TalonFX.hpp"

using namespace std;

class SwerveModule
{

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
        if (error < -M_PI) {
        error += M_PI*2;
        }
        if (error > M_PI) {
            error -= M_PI*2;
        }
        dMotor->Set(abs(moduleVector));
        sMotor->Set(error / M_PI);
    }
};