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

/* An ultrasonic sensor connected to one or more vibrators.
 *
 * The class uses the state pattern to scale the distance detected with the
 * ultrasonic ranger differently to the vibration motors.
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
