/*

 * vibration_motor.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: lee
 */

#include "wiringPi.h"

VibrationMotor::VibrationMotor(int &min, int &max, int &pin):
	min_vibration(min), max_vibration(max), pin(pin) {
	pinMode(pin, PWM_OUTPUT);
}

void VibrationMotor::vibrate(double &percent) {
	int range = max_vibration - min_vibration;
	int vibration = (percent * range) + min_vibration;
	pwmWrite(pin, vibration);
}
