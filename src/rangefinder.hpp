/*
 * rangefinder.hpp
 *
 *  Created on: Sep 30, 2013
 *      Author: lee
 */

#ifndef RANGEFINDER_H_
#define RANGEFINDER_H_

#include <memory>
#include <vector>

#include "ultrasonic_sensor.hpp"
#include "vibration_motor.hpp"

/* A ``Sensor`` connected to one or more vibrators.
 *
 * The ``Sensor`` detects the range to objects continuously. The ``Rangefinder``
 * polls it continuously and uses the alert level it reports to distribute the
 * alert to its vibrators.
 */
class Rangefinder {
    std::shared_ptr<UltrasonicSensor> sensor;
    std::vector<VibrationMotor> vibrators;
public:
    Rangefinder(std::shared_ptr<UltrasonicSensor> sensor,
            const std::vector<VibrationMotor> &vibrators);
    void update_vibrators();
};

#endif /* RANGEFINDER_H_ */
