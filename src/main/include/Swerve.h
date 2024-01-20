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
            SwerveModule{11, 31, 21, {-17.75, 25}},
            SwerveModule{12, 32, 22, {-17.75, -25}},
            SwerveModule{13, 33, 23, {17.75, 25}},
            SwerveModule{14, 34, 24, {17.75, -25}}};

    // NavX V2 gyro object
    AHRS navx{frc::SPI::Port::kMXP};
    
    // drive and turn rates with drive rates stored as complex number
    complex<float> targetDriveRate;
    // robot oriented drive rate
    complex<float> robotDriveRate;
    float targetTurnRate;

    // current position on the field relative to the starting position
    complex<float> currentPosition{0, 0};
    // current angle
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
    void Set(complex<float> driveRate, float turnRate, bool useAcceleration = true)
    {
        // set the current angle to the gyro angle + the starting angle
        currentAngle = -navx.GetYaw();

        // set the target rates to the input
        targetDriveRate = driveRate;
        targetTurnRate = turnRate;

        // store the robot oriented drive rate
        robotDriveRate = targetDriveRate * polar<float>(1, -currentAngle*M_PI/180);
        // stores the robot's change in position since last Set()
        complex<float> positionChange;
        // drive the modules and average the module position changes
        for (int i = 0; i < 4; i++)
        {

            modules[i].Set(robotDriveRate, targetTurnRate);
            // find the position change of each module since the last function call
            positionChange += modules[i].getPositionChangeVector();
        }
        // average the position change of all four swerve modules
        positionChange /= 4;
        // field-orient the position change vector
        positionChange *= polar<float>(1, currentAngle*M_PI/180);
        // add the change in position over this cycle to the running total
        currentPosition += positionChange;
    }

    // drive toward a point and angle (degrees) and return true when the point is reached
    bool driveToward(complex<float> targetPostition, float targetAngle, float positionTolerance = 2, float angleTolerance = 5)
    {
        complex<float> positionError = targetPostition - currentPosition;
        float angleError = angleDifference(currentAngle, targetAngle);
        complex<float> positionPIDOutput = positionError * parameters.autoPositionP;
        float anglePIDOutput = angleError * parameters.autoAngleP;
        if (abs(positionPIDOutput) > parameters.autoMaxDriveRate)
        {
            positionPIDOutput *= parameters.autoMaxDriveRate / abs(positionPIDOutput);
        }
        if (abs(anglePIDOutput) > parameters.autoMaxTurnRate)
        {
            anglePIDOutput *= parameters.autoMaxTurnRate / abs(anglePIDOutput);
        }
        Set(positionPIDOutput, anglePIDOutput, false);
        return (abs(positionError) < positionTolerance) && (abs(angleError) < angleTolerance);
    }

};