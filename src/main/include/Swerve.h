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

    // NavX V2 gyro object
    AHRS navx{frc::SPI::Port::kMXP};
    Vector robotDriveRate;
    float currentAngle;

public:
    // initialize the swerve modules and zero the NavX yaw
    void initialize()
    {
        for (int i = 0; i < 4; i++)
        {
            modules[i].initialize();
        }
        navx.ZeroYaw();
    }

    // set field centric drive rate
    void Set(Vector driveRate, float turnRate, bool useAcceleration = true)
    {
        // set the current angle to the gyro angle + the starting angle
        currentAngle = -navx.GetYaw();
        // store the robot oriented drive rate
        driveRate.rotateCCW(-currentAngle*M_PI/180);
        for (int i = 0; i < 4; i++)
        {
            modules[i].Set(robotDriveRate, turnRate);
        }
    }
};