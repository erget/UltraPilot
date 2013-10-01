/*
 * vibration_scalers.hpp
 *
 *  Created on: Sep 26, 2013
 *      Author: lee
 */

#ifndef RANGEFINDER_H_
#define RANGEFINDER_H_

/* An abstract class for vibration scaling.
 *
 * VibrationScalers expect a percentage input that they scale to a percentage
 * output. The higher the input, the lower the output and vice versa.
 */
class VibrationScaler {
public:
	virtual double scale(double &input);
	virtual void ~destructor();
};

/* Scale input linearly.
 *
 * Because both input and output are a percent value, the given value is simply
 * returned inversely.
 */
class LinearScaler: public VibrationScaler {
public:
	double scale(double &input);
};

/* Scale input bilinearly.
 *
 * 75% of the output range is covered in the first 50% of the input range. The
 * remaining 25% output range are used to cover the remaining 50% input range.
 */
class BilinearScaler: public VibrationScaler {
	double scale(double &input);
};

/* Distribute the input logarithmically onto the output.
 *
 * The parameters affecting the range and slope of the curve were determined
 * empirically.
 */
class LogarithmicScaler: public VibrationScaler {
	double scale(double &input);
};

#endif /* RANGEFINDER_H_ */
