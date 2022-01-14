#ifndef ROVER_SENSOR_H
#define ROVER_SENSOR_H

#include "position.h"

class Sensor {
public:
    [[nodiscard]] virtual bool
    is_safe(coordinate_t x, coordinate_t y) = 0;
};

#endif //ROVER_SENSOR_H
