/*
 * BatPi - a program that uses Raspberry Pi to read distance measurements from
 * an ultrasonic sensor and report it to the user in the form of PWM vibration.
 * The stronger the vibration, the closer the detected range.
 * Author: Daniel Lee, 2013
 */

#include <iostream>
#include <string>

#include "wiringPi.h"
#include "wiringSerial.h"

#include "io.h"

int MIN_RANGE = 20;
int MAX_RANGE = 400;
int MIN_VIBRATION = 1;
int MAX_VIBRATION = 1023;
std::string USAGE =
"Usage: BatPi [SCALING PARAMETER] \n"
"\n"
"Sense the distance to the nearest object using an ultrasonic ranger and \n"
"report it to the user in the form of vibration. \n"
"\n"
"  -h, --help     display this help and exit \n"
"\n"
"SCALING PARAMETER controls the output. Possible parameters are: \n"
"  linear        Vibration is scaled linearly to distance \n"
"  logarithmic   Vibration is scared logarithmically to distance \n"
"  bilinear      Vibration is scaled more strongly for objects detected at \n"
"                less than 150cm \n"
"\n"
"Report date bugs to lee@isi-solutions.org \n";

int main(int argc, char *argv[]) {
	if (argc != 2 || argv[1] == "-h" || argv[1] == "--help") {
		std::cout << USAGE;
		return 0;
	}

    wiringPiSetup();
    pinMode(1, PWM_OUTPUT);
	int serial = serialOpen("/dev/ttyUSB0", 9600);
	int output;
	int pwm_value;

    #ifndef NDEBUG
    std::cout << "Option chosen: " << argv[1] << std::endl;
    #endif
    
	while (1) {
        output = getDistance(serial);
        if (std::string(argv[1]) == "linear") {
        	double distance_percent = valueToPercent(output,
        			MIN_RANGE, MAX_RANGE);
        	pwm_value = percentToValue(1 - distance_percent,
        			MIN_VIBRATION, MAX_VIBRATION);
        } else if (std::string(argv[1]) == "logarithmic")
        	pwm_value = logarithmicVibration(output);
        else if (std::string(argv[1]) == "bilinear")
        	pwm_value = bilinearVibration(output, MIN_RANGE, MAX_RANGE,
                    MIN_VIBRATION, MAX_VIBRATION);
		else {
			std::cout << "Invalid input!" << std::endl;
			std::cout << USAGE;
			return 1;
		}

        #ifndef NDEBUG
        std::cout << "Distance: " << output << "\t Vibration:" << pwm_value
            << std::endl;
        #endif

        pwmWrite(1, pwm_value);
    }
	return 0;
}
