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
    UltrasonicGeneralRanger(const double & min,
            const double & max,
            const int & serial);
    void set_alert_level();
};

/* An ultrasonic rangefinder for detecting ground obstacles.
 *
 * The alert level is set according to the variability between distances
 * measured within the given warn_time. If the deviance between distances
 * measured exceeds the max_deviance, the alert_level is set to 100. Otherwise
 * it stays at 0.
 *
 * Fields:
 *  max_deviance: The maximum deviance in measurements allowed within the
 *                warn_time. As long as the deviance between measurements does
 *                not exceed this value, the sensor's alert_level is set to 0.
 *                If the deviance exceeds this level, the alert_level is set to
 *                100.
 *  warn_time: The amount of measurements that the sensor continues to warn for
 *             when its max_deviance is exceeded. For the MaxBotix sensors that
 *             these classes are written for, this corresponds to tenths of a
 *             second when the sensors measure continuously.
 *  observations: The observations from the previous warn_time amount of time.
 */
class UltrasonicGroundSensor: public UltrasonicSensor {
    double max_deviance;
    int warn_time;
    std::deque<double> observations;
public:
    UltrasonicGroundSensor(const double & min,
            const double & max,
            const int & serial,
            const double & max_deviance,
            const int & warn_time);
    void set_alert_level();
};

#endif /* ULTRASONIC_SENSOR_HPP_ */
