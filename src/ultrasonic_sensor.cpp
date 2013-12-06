/*

 * ultrasonic_sensor.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: lee
 */

#ifndef NDEBUG
#include <iostream>
#endif /* NDEBUG */

#include <algorithm>

#include "wiringSerial.h"

#include "ultrasonic_sensor.hpp"

UltrasonicSensor::UltrasonicSensor(const double & min,
        const double & max,
        const int & serial) :
        min_range(min), max_range(max), serial_connection(serial) {}

/* Read range from sensor.
 *
 * This is accomplished by reading the sensor's serial output. The function
 * converts the observation to a normalized reading between 0 and 100% of the
 * sensor's range, multiplies that by 100, and returns it. Thus, if an object
 * is detected at 5% of the sensor's range, the return is 5.0.
 */
double UltrasonicSensor::get_range() {
    int distance = 0;
    int counter = 100;
    int output;
    while (true) {
        output = serialGetchar(serial_connection);
        // Output is 'R'
        if (output == 82) {
        }
        // Output is CR
        else if (output == 13)
            break;
        else {
            // Subtract 48 to get int from ASCII number
            distance += (output - 48) * counter;
            counter /= 10;
        }
    }
    if (distance > max_range)
        distance = max_range;

#ifndef NDEBUG
    std::cout << "Distance measured: " << distance << std::endl;
#endif /* NDEBUG */

    // Returned range is normalized to percent of sensor's range
    return (distance - min_range) / (max_range - min_range) * 100;
}

UltrasonicSensor::~UltrasonicSensor() {}

UltrasonicGeneralRanger::UltrasonicGeneralRanger(const double & min,
        const double & max,
        const int & serial): UltrasonicSensor(min, max, serial) {}

/* Set alert_level inversely to detected range.
 *
 * If no object is detected, the alert_level is set to 0. If an object is
 * detected at 25% of the sensor's range, the alert_level is set to 75%.
 */
void UltrasonicGeneralRanger::set_alert_level() {
    double range = get_range();
    alert_level = 100 - range;
}

UltrasonicGroundSensor::UltrasonicGroundSensor(const double & min,
        const double & max,
        const int & serial,
        const double & max_deviance,
        const int & warn_time): UltrasonicSensor(min, max, serial),
                max_deviance(max_deviance), warn_time(warn_time) {};

/* Set alert_level according to variability in the last several measurements.
 *
 * Each measurement is added to the back of the observations deque. If the
 * observations contains more than warn_time observations, the oldest
 * observation is removed from the front of the deque. Then the maximum
 * deviance between all remaining observations is computed. If this exceeds
 * the UltrasonicGroundSensor's max_deviance, the alert_level is set to 100.
 * Otherwise, it is set to 0.
 */
void UltrasonicGroundSensor::set_alert_level() {
    double range = get_range();
    observations.push_back(range);
    if (observations.size() > warn_time) observations.pop_front();
    double max_value = *std::max(observations.cbegin(), observations.cend());
    double min_value = *std::min(observations.cbegin(), observations.cend());
    double deviance = max_value - min_value;
    alert_level = (deviance > max_deviance ? 100 : 0);
}
