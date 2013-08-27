#include <iostream>

#include "wiringSerial.h"
#include "io.h"

int main() {
	std::cout << "Printing distance in cm." << std::endl;
	int serial = serialOpen("/dev/ttyUSB0", 9600);
	int output;
	while (1) {
        output = getDistance(serial);
		std::cout << output << std::endl;
    }
	return 0;
}
