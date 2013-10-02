/*

 * ultrasonic_sensor.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: lee
 */

#include "wiringSerial.h"

#include "ultrasonic_sensor.hpp"

UltrasonicSensor::UltrasonicSensor(const double &min, const double &max,
        const int &serial) :
        min_range(min), max_range(max), serial_connection(serial) {}

double UltrasonicSensor::detect() {
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
    // Returned range is normalized to percent of sensor's range
    return (distance - min_range) / (max_range - min_range) * 100;
}
