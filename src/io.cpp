/*
 * io.cpp
 * Functions for working with inputs and outputs from sensors to hardware pins
 * on the Raspberry Pi
 * Author: Daniel Lee, 2013
 */

#include <cmath>
#include "wiringSerial.h"

/*
 * getDistance:
 *   Get the distance read from a MaxBotix sensor using the given
 *   serial_connection
 */

int getDistance(const int &serial_connection) {
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

/*
 * getVibration:
 *   Return a logarithmic vibration value based on the distance measured. The
 *   function is designed to work with values between 0 and 400, returning a
 *   value inclusively between 1023 and 0.
 * Author: Daniel Lee, 2013
 */

int getVibration(const int &distance) {
    int vibration = -236.7 * log2(distance) + 2046;
    if (vibration < 0) vibration = 0;
    return vibration;
}

/*
 * bilinearVibration
 *   Scale vibration using two linear scales: One above and one below 1.5m
 */
// TODO: This has 1023 vibration at 0, not at 20. 0 is never reached.
int bilinearVibration(const int &distance) {
    int vibration;
    if (distance > 400) vibration = 0;
    else if (distance < 150) vibration = -3.41 * distance + 1024;
    else vibration = -2.048 * distance + 819.2;
    return vibration;
}

/*
 * valueToPercent:
 *   Find the percent of a value's distance between given upper and lower
 *   ranges
 */

double valueToPercent(const double &value, const double &min, const double &max)
{
    double percent;
    if (value < min) percent = 0;
    else if (value > max) percent = 1;
    else percent = (value - min) / max;
    return percent;
}

/*
 * percentToValue:
 *   Find the value at the given percent's distance between given upper and
 *   lower ranges
 */

double percentToValue(const double &percent, const double &min,
        const double &max) {
    double range = max - min;
    return (percent * range) + min;
}
