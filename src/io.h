/*
 * io.h
 *
 *  Created on: Aug 26, 2013
 *      Author: lee
 */

#ifndef IO_H_
#define IO_H_

int getDistance(const int &serial_connection);
// Rename to logVibration
int getVibration(const int &distance);
int bilinearVibration(const int &distance);
double valueToPercent(const double &value, const double &min, const double &max);
double percentToValue(const double &percent, const double &min, const double &max);

#endif
