/*
 * UltraPilot Mark 1 - a program to retrieve ranges to objects using a single
 * ultrasonic sensor and report it back to the user using haptic feedback that
 * is inversely scaled to the distance to the detected object.
 * Author: Daniel Lee, 2013
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "wiringPi.h"
#include "wiringSerial.h"

#include "rangefinder.hpp"
#include "ultrasonic_sensor.hpp"
#include "vibration_motor.hpp"

// Sensor parameters
const int MIN_RANGE = 20;
const int MAX_RANGE = 400;
const char *DEVICE = "/dev/ttyUSB0";
const int BAUD_RATE = 9600;
const double GROUND_OBSTACLE_SIZE = 0.01315;
const int WARNING_TIME = 6;

// Vibrator parameters
const int MIN_VIBRATION = 1;
const int MAX_VIBRATION = 1023;
const int PIN = 1;

const std::string USAGE =
"Usage: UltraPilot [options]"
"\n"
"Sense the distance to the nearest object using an ultrasonic ranger and \n"
"report it to the user in the form of vibration. \n"
"\n"
"  -h, --help     display this help and exit \n"
"\n"
"Options:\n"
"  general: Report range to objects using ultrasonic\n"
"  ground:  Report whether ground obstacle is detected or not"
"\n"
"Report date bugs to lee@isi-solutions.org \n";

int main(int argc, char *argv[]) {
    if (argc != 2 || argv[1] == "-h" || argv[1] == "--help") {
        std::cout << USAGE;
        return 0;
    }
    std::string sensor_type = argv[1];

    wiringPiSetup();

    std::shared_ptr<UltrasonicSensor> sensor;
    if (sensor_type == "general")
        sensor = std::make_shared<UltrasonicGeneralRanger>(MIN_RANGE,
                MAX_RANGE,
                serialOpen(DEVICE, BAUD_RATE));
    else if (sensor_type == "ground")
        sensor = std::make_shared<UltrasonicGroundSensor>(MIN_RANGE,
                MAX_RANGE,
                serialOpen(DEVICE, BAUD_RATE),
                GROUND_OBSTACLE_SIZE,
                WARNING_TIME);
    else {
        std::cerr << "Invalid sensor type!" << std::endl;
        std::cout << USAGE;
        return 1;
    }

    VibrationMotor vibrator(MIN_VIBRATION, MAX_VIBRATION, PIN);
    std::vector<VibrationMotor> vibrators {vibrator};

    Rangefinder wand(sensor, vibrators);
    while (true)
        wand.update_vibrators();

    return 0;
}
