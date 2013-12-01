/*

 * vibration_scalers.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: lee
 */

#include <cmath>

#include "vibration_scalers.hpp"

double LinearScaler::scale(const double & input) {
    return 100 - input;
}

BilinearScaler::BilinearScaler(): max_input(100), mid_input(50), min_input(0),
max_output(100), mid_output(25), min_output(0) {}

double BilinearScaler::scale(const double & input) {
    int output;
    double slope, intercept;
    if (input < mid_input) {
        slope = (max_output - mid_output) / (min_input - mid_input);
        intercept = max_output - (slope * min_input);
    } else {
        slope = (mid_output - min_output) / (mid_input - max_input);
        intercept = min_output - (slope * max_input);
    }
    output = slope * input + intercept;
    if (output < min_output)
        output = 0;
    else if (output > max_output)
        output = max_output;
    return output;
}

double LogarithmicScaler::scale(const double & input) {
    int vibration = -log(input) * 21.5 + 100;
    if (vibration < 0)
        vibration = 0;
    return vibration;
}
