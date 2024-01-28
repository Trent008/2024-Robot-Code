// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "subsystems/M.h"
#include "AHRS.h"
class S
{
public:
	void set(complex<float> dV, float tV) {
		a = -g.GetYaw()*M_PI/180;
		dV *= polar<float>(1, -a);
		// normalize module speeds
		float f = 1;
		for (auto m:ms) {
			float mS = abs(m.getV(dV, tV));
			if (mS > f) {
				f = mS;
			}
		}
		// drive the modules
		for (auto m : ms) {
			m.set(dV/f, tV/f);
		}
	}
private:
	M ms[4] = {
		M(1, complex<float>(-17.75, 25)),
		M(2, complex<float>(-17.75, -25)),
		M(3, complex<float>(17.75, 25)),
		M(4, complex<float>(17.75, -25))};
	AHRS g{frc::SPI::Port::kMXP};
	float a;
};
