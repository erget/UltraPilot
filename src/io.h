/*
 * io.h
 *
 *  Created on: Aug 26, 2013
 *      Author: lee
 */

#ifndef IO_H_
#define IO_H_

int getDistance(const int serial_connection);
double valueToPercent(double value, double min, double max);
double percentToValue(double percent, double min, double max);

#endif
