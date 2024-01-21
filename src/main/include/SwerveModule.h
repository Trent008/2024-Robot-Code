#pragma once
#include "rev/CANSparkMax.h"
#include "ctre/phoenix6/CANcoder.hpp"
#include "ctre/phoenix6/TalonFX.hpp"
#include "angleMath.h"
#include "Vector.h"

using namespace std;

class SwerveModule
{

private:
    ctre::phoenix6::hardware::TalonFX *dMotor;
    rev::CANSparkMax *sMotor;
    ctre::phoenix6::hardware::CANcoder *wheelAngleEncoder;
    Vector turnVector;

public:
    SwerveModule(int moduleID, Vector position)
    {
        dMotor = new ctre::phoenix6::hardware::TalonFX(10+moduleID, "rio");
        sMotor = new rev::CANSparkMax{30+moduleID, rev::CANSparkMax::MotorType::kBrushless};
        wheelAngleEncoder = new ctre::phoenix6::hardware::CANcoder{20+moduleID};
        turnVector = position.getRotatedCCW(90).getDivided(turnVector.getMagnitude());
    }

    Vector getModuleVector(Vector driveRate, float turnRate)
    {
        return driveRate.getAdded(turnVector.getScaled(turnRate));
    }

    void Set(Vector driveRate, float turnRate)
    {
        float wheelAngle = wheelAngleEncoder->GetAbsolutePosition().GetValue().value()*360;
        Vector targetVelocity = getModuleVector(driveRate, turnRate);
        float error = angleDifference(targetVelocity.getAngle()*180/M_PI, wheelAngle);
        float dMotorVelocity = targetVelocity.getMagnitude();
        dMotor->Set(dMotorVelocity);
        sMotor->Set(error / 180);
    }

    void initialize()
    {
        sMotor->SetInverted(false);
        sMotor->BurnFlash();
    }
};