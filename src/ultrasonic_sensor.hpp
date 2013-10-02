/*
 * ultrasonic_sensor.hpp
 *
 *  Created on: Sep 30, 2013
 *      Author: lee
 */

#ifndef ULTRASONIC_SENSOR_HPP_
#define ULTRASONIC_SENSOR_HPP_

#include "wiringSerial.h"

/* An ultrasonic rangefinder.
 *
 * The serial connection argument is used to connect the object to a serial
 * input device.
 */
class UltrasonicSensor {
	double min_range;
	double max_range;
	int serial_connection;
public:
	UltrasonicSensor(const double &min, const double &max, const int &serial);
	double detect();
};

#endif /* ULTRASONIC_SENSOR_HPP_ */
