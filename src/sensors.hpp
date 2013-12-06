/*
 * sensors.hpp
 *
 *  Created on: Nov 23, 2013
 *      Author: lee
 */

#ifndef SENSORS_HPP_
#define SENSORS_HPP_

/*
 * An abstract class used for ranging sensors.
 *
 * alert_level: An integer with inclusive range 0-100. Reflects the level of
 *              proximity the sensor detects.
 */
class Sensor {
protected:
    double alert_level;
    virtual ~Sensor() = 0;
public:
    virtual void set_alert_level() = 0;
    int get_alert_level();
};

#endif /* SENSORS_HPP_ */
