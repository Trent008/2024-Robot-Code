#pragma once
#include "complex"

using namespace std;

// parameters for robot movement and autonomous
struct Parameters
{  
    // max amperage for the drive motor PID controllers
    float const driveMotorMaxAmperage = 45;

    // diameter of the drive wheels
    float const wheelDiameter = 3.9;

    // inches per rotation of the swerve wheel drive motors
    float const driveMotorInPerRot = (M_PI * wheelDiameter / 6.75);

    // degrees per rotation of the note handler angle motor
    float const noteHandlerDegPerRot = (360/27);

    // inches per rotation of the note handler elevator motor
    float const noteHandlerElevInPerRot = (9/2.54);

    // percent to change the robot velocity per teleop cycle
    float const slewRate = 0.04;

    // max drive rate for autonomous
    float const autoMaxDriveRate = 0.2;

    // max rotation rate for autonomous
    float const autoMaxTurnRate = 0.2;

    // proportional constant for autonomous position error
    float const autoPositionP = 0.01;

    // proportional constant for autonomous angle error
    float const autoAngleP = 0.005;
} parameters;