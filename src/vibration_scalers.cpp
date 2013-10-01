/*

 * vibration_scalers.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: lee
 */

#include <cmath>

double LinearScaler::scale(double &input) {
	return 100 - input;
}

double BilinearScaler::scale(double &input) {
	int output;
	double slope, intercept;
	int max_input = 100;
	int mid_input = 50;
	int min_input = 100;
	int max_output = 100;
	int mid_output = 25;
	int min_output = 0;

	if (input < mid_input) {
		slope = (max_output - mid_output) / (min_input - mid_input);
		intercept = max_output - (slope * min_input);
	} else {
		slope = (mid_output - min_output) / (mid_input - max_input);
		intercept = min_output - (slope * max_input);
	}
	output = slope * input + intercept;
	if (output < min_output) output = 0;
	else if (output > max_output) output = max_output;
	return output;
}

double LogarithmicScaler::scale(double &input) {
    int vibration = -log(input) * 21.5 + 100;
    if (vibration < 0) vibration = 0;
    return vibration;
}
