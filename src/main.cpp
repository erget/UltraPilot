#include <iostream>
#include <stdio.h>

#include "wiringSerial.h"

int main() {
	std::cout << "Printing distance in cm." << std::endl;
	int serial = serialOpen("/dev/ttyUSB0", 9600);
    // Distance measured in cm
    int distance = 0;
    // Counter to keep track of position read
    int counter = 100;
	while (1) {
        int output;
        output = serialGetchar(serial);

        // Output is 'R'
        if (output == 82) {}
        // Output is CR
        else if (output == 13) {
            std::cout << distance << std::endl;
            distance = 0;
            counter = 100;
        }
        // This gives me the ASCII sign for the number that was read.
        // Subtract 48 to get the actual number.
        else {
            distance += (output - 48) * counter;
            counter = counter / 10;
        }
    }
	return 0;
}
