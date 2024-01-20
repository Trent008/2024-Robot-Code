#pragma once
#include "rev/CANSparkMax.h"
#include "Parameters.h"

class NoteHandler
{
  public:

    // set the note handler angle (range: 0 to 330 degrees)
    bool SetAngle(float angle)
    {
        // limit the angle setpoint
        if (angle > 330)
        {
            angle = 330;
        }
        if (angle < 0)
        {
            angle = 0;
        }
        
        // calculate the reference
        float reference = angle / parameters.noteHandlerDegPerRot;
        // set the reference
        pivotPID.SetReference(reference, rev::CANSparkMax::ControlType::kPosition);
        // return true if setpoint reached
        if (abs(reference - pivotEncoder.GetPosition()))
        {
            return true;
        }
        return false;
    }

    // set the elevator height (range: 0 to 20 inches)
    bool SetHeight(float height)
    {
        // limit the height setpoint
        if (height > 20)
        {
            height = 20;
        }
        if (height < 0)
        {
            height = 0;
        }
        // calculate the reference
        float reference = height / parameters.noteHandlerElevInPerRot;
        // set the reference
        elevatorPID.SetReference(reference, rev::CANSparkMax::ControlType::kPosition);
        // return true if setpoint reached
        if (abs(reference - elevatorEncoder.GetPosition()))
        {
            return true;
        }
        return false;
    }

    void initialize()
    {
        // pivot motor setup
        m_pivot.RestoreFactoryDefaults();
        m_pivot.SetInverted(false);
        pivotPID.SetP(0.2);
        pivotPID.SetI(0);
        pivotPID.SetD(1);
        pivotPID.SetIZone(0);
        pivotPID.SetFF(0);
        pivotPID.SetOutputRange(-0.3, 0.3);
        m_pivot.BurnFlash();
        // elevator motor setup
        m_elevator.RestoreFactoryDefaults();
        m_elevator.SetInverted(false);
        elevatorPID.SetP(0.2);
        elevatorPID.SetI(0);
        elevatorPID.SetD(1);
        elevatorPID.SetIZone(0);
        elevatorPID.SetFF(0);
        elevatorPID.SetOutputRange(-0.3, 0.3);
        m_elevator.BurnFlash();
        // roller motor setup
        m_elevator.RestoreFactoryDefaults();
        m_roller.SetInverted(false);
        m_roller.BurnFlash();
    }


  private:
    // pivot motor
    rev::CANSparkMax m_pivot{11, rev::CANSparkMax::MotorType::kBrushless};
    // pivot PID
    rev::SparkPIDController pivotPID = m_pivot.GetPIDController();
    // pivot encoder
    rev::SparkRelativeEncoder pivotEncoder = m_pivot.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor);
    // elevator motor
    rev::CANSparkMax m_elevator{12, rev::CANSparkMax::MotorType::kBrushless};
    // elevator PID
    rev::SparkPIDController elevatorPID = m_elevator.GetPIDController();
    // elevator encoder
    rev::SparkRelativeEncoder elevatorEncoder = m_elevator.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor);
    // roller motor
    rev::CANSparkMax m_roller{13, rev::CANSparkMax::MotorType::kBrushless};
} noteHandler;