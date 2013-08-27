/*
 * io.cpp
 *
 *  Created on: Aug 26, 2013
 *      Author: lee
 */

#include "wiringSerial.h"

/*
 * getDistance:
 *   Get the distance read from a MaxBotix sensor using the given
 *   serial_connection
 */

int getDistance(const int serial_connection) {
  int distance = 0;
  int counter = 100;
  int output;
  while (1) {
      output = serialGetchar(serial_connection);
      // Output is 'R'
      if (output == 82) {}
      // Output is CR
      else if (output == 13) break;
      else {
          // Subtract 48 to get int from ASCII number
          distance += (output - 48) * counter;
          counter /= 10;
      }
  }
  return distance;
}
