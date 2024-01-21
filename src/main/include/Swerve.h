#pragma once
#include "AHRS.h"
#include "SwerveModule.h"

using namespace std;

// runs a swerve chassis
class Swerve
{

private:
    // array of four swerve module objects with their positions relative to the center specified
    SwerveModule modules[4] =
        {
            SwerveModule{1, {-17.75, 25}},
            SwerveModule{2, {-17.75, -25}},
            SwerveModule{3, {17.75, 25}},
            SwerveModule{4, {17.75, -25}}};

    AHRS navx{frc::SPI::Port::kMXP};
    float currentAngle;

public:
    void initialize()
    {
        for (int i = 0; i < 4; i++)
        {
            modules[i].initialize();
        }
        navx.ZeroYaw();
    }

    void Set(Vector driveRate, float turnRate)
    {
        for (int i = 0; i < 4; i++)
        {
            modules[i].Set(driveRate.getRotatedCCW(navx.GetYaw()*M_PI/180), turnRate);
        }
    }
};