/*

 * vibration_motor.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: lee
 */

#include "wiringPi.h"

#include "vibration_motor.hpp"

VibrationMotor::VibrationMotor(const int &min, const int &max, const int &pin):
	min_vibration(min), max_vibration(max), pin(pin) {
	pinMode(pin, PWM_OUTPUT);
}

void VibrationMotor::vibrate(const double &percent) {
	int range = max_vibration - min_vibration;
	int vibration = (percent * range) + min_vibration;
	pwmWrite(pin, vibration);
}
