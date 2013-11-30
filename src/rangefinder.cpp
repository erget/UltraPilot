/*
 * rangefinder.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: lee
 */

#ifndef NDEBUG
#include <iostream>
#endif /* NDEBUG */

#include <vector>

#include "rangefinder.hpp"

#include "ultrasonic_sensor.hpp"
#include "vibration_motor.hpp"

Rangefinder::Rangefinder(std::shared_ptr<UltrasonicSensor> sensor,
        const std::vector<VibrationMotor> &vibrators) :
        sensor(sensor), vibrators(vibrators) {
}

void Rangefinder::update_vibrators() {
    sensor->set_alert_level();
    double vibration = sensor->get_alert_level();
    double full_vibration = 100 / vibrators.size();

#ifndef NDEBUG
    std::cout << " Vibration: " << vibration;
    std::cout << std::endl;
#endif /* NDEBUG */

    for (auto &vibrator : vibrators) {
        if (vibration > full_vibration) {
            vibrator.vibrate(100);
            vibration -= full_vibration;
        } else {
            vibrator.vibrate(vibration / full_vibration);
            vibration = 0;
        }
    }
}
