#ifndef ROVER_SENSOR_H
#define ROVER_SENSOR_H

#include "Position.h"

class Sensor {
public:
    [[nodiscard]] virtual bool
    is_safe(coordinate_t x, coordinate_t y) const = 0;
};

#endif //ROVER_SENSOR_H
