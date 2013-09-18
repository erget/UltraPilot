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
 */

int logarithmicVibration(const int &distance) {
    int vibration = -300 * log(distance) + 2046;
    if (vibration < 0) vibration = 0;
    return vibration;
}

/*
 * bilinearVibration
 *   Scale vibration using two linear scales: One above and one below the
 *   midrange.
 */

int bilinearVibration(const int &distance, const int &min_distance,
        const int &max_distance, const int &min_vibration,
        const int &max_vibration) {
    int vibration;
    double slope, intercept;
    int mid_distance = (min_distance + max_distance) / 2;
    int mid_vibration = (min_vibration + max_vibration) / 2;

    if (distance < mid_distance) {
        slope = (max_vibration - mid_vibration) /
                (min_distance - mid_distance);
        intercept = max_vibration - (slope * min_distance);
    } else {
        slope = (mid_vibration - min_vibration) /
                (mid_distance - max_distance);
        intercept = max_vibration - (slope * max_distance);
    }
    vibration = slope * distance + intercept;
    if (vibration < min_vibration) vibration = 0;
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
    else percent = (value - min) / (max - min);
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
