// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "rev/CANSparkMax.h"
#include "ctre/phoenix6/CANcoder.hpp"
#include "ctre/phoenix6/TalonFX.hpp"
#include "complex"
#include "aMath.h"
using namespace std;

class M
{
public:
	M(int ID, complex<float> p) {
        m_d = new ctre::phoenix6::hardware::TalonFX(10+ID, "rio");
        e_s = new ctre::phoenix6::hardware::CANcoder{20+ID, "rio"};
        m_s = new rev::CANSparkMax(30+ID, rev::CANSparkMax::MotorType::kBrushless);
        tVector = p*complex<float>(0, 1)/abs(p);
    }
	void set(complex<float> dV, float tV) {
        complex<float> V = getV(dV, tV);
        float m_dV = abs(V);
        if (m_dV > 0.001) {
            float e = arg(V) - e_s->GetAbsolutePosition().GetValue().value()*2*M_PI;
            wrap(e);
            if (abs(e) > M_PI_2) {
                e += M_PI;
                wrap(e);
                m_dV = -m_dV;
            }
            m_d->Set(m_dV);
            m_s->Set(e/M_PI);
        } else {
            m_d->Set(0);
            m_s->Set(0);
        }
    }
    complex<float> getV(complex<float> dV, float tV) {
        return dV + tVector * tV;
    }


private:
	ctre::phoenix6::hardware::TalonFX *m_d;
    ctre::phoenix6::hardware::CANcoder *e_s;
    rev::CANSparkMax *m_s;
    complex<float> tVector;
};
