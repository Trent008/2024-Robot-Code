#pragma once
#include "rev/CANSparkMax.h"
#include "Parameters.h"

class NoteHandler
{
  public:

    bool SetAngle(float angle)
    {
        // limit the angle
        if (angle > 330)
        {
            angle = 330;
        }
        if (angle < 0)
        {
            angle = 0;
        }
        
        float reference = angle / parameters.noteHandlerDegPerRot;
        pivotPID.SetReference(reference, rev::CANSparkMax::ControlType::kPosition);
        if (abs(reference - pivotEncoder.GetPosition()))
        {
            return true;
        }
        return false;
    }

    bool SetHeight(float height)
    {
        if (height > 20)
        {
            height = 20;
        }
        if (height < 0)
        {
            height = 0;
        }
        float reference = height / parameters.noteHandlerElevInPerRot;
        elevatorPID.SetReference(reference, rev::CANSparkMax::ControlType::kPosition);
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