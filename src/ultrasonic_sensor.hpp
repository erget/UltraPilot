/*
 * ultrasonic_sensor.hpp
 *
 *  Created on: Sep 30, 2013
 *      Author: lee
 */

#ifndef ULTRASONIC_SENSOR_HPP_
#define ULTRASONIC_SENSOR_HPP_

#include <deque>

#include "wiringSerial.h"

#include "sensors.hpp"

/* A virtual ultrasonic rangefinder.
 *
 * The serial connection argument is used to connect the object to a serial
 * input device.
 *
 * Methods:
 *  get_range() - Detect nearest ranged object. Returns a number between 0 and
 *                100, 0 meaning 0% of the detectable range and 100 being the
 *                opposite.
 */
class UltrasonicSensor: public Sensor {
    double min_range;
    double max_range;
    int serial_connection;
protected:
    double get_range();
public:
    UltrasonicSensor(const double &min, const double &max, const int &serial);
    ~UltrasonicSensor();
};

/* An ultrasonic rangefinder for detecting the distance to arbitrary objects.
 *
 * The alert level is set inversely to the detected distance.
 */
class UltrasonicGeneralRanger: public UltrasonicSensor {
public:
    UltrasonicGeneralRanger(const double &min,
            const double &max,
            const int &serial);
    void set_alert_level();
};

#endif /* ULTRASONIC_SENSOR_HPP_ */
