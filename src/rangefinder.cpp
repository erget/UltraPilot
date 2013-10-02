/*
 * rangefinder.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: lee
 */

#include <vector>

#include "rangefinder.hpp"

#include "vibration_scalers.hpp"
#include "ultrasonic_sensor.hpp"
#include "vibration_motor.hpp"

Rangefinder::Rangefinder(VibrationScaler *vib,
        const UltrasonicSensor &sensor,
		const std::vector<VibrationMotor> &vibrators):
		scaler(vib), sensor(sensor), vibrators(vibrators) {}

void Rangefinder::update_vibrators() {
	double range = sensor.detect();
	double vibration = scaler->scale(range);
	double full_vibration = 100 / vibrators.size();
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
