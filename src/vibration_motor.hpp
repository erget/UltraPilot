/*
 * vibration_motor.hpp
 *
 *  Created on: Sep 30, 2013
 *      Author: lee
 */

#ifndef VIBRATION_MOTOR_HPP_
#define VIBRATION_MOTOR_HPP_

/* A vibration motor controlled by PWM.
 *
 * The connected pin is set up to use PWM on object initialization.
 */
class VibrationMotor {
	int min_vibration;
	int max_vibration;
	int pin;
public:
	VibrationMotor(int &min, int &max, int &pin);
	void vibrate(double &percent);
};

#endif /* VIBRATION_MOTOR_HPP_ */
