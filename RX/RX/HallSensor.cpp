// 
// 
// 

#include "HallSensor.h"


void HallSensor::interruptHandler ()
    {
    speed = (dia * M_PI) /
            ((millis () - last_hs_sesnsed) / 1000.0) *
            3.6;

    last_hs_sesnsed = millis ();
    }

double HallSensor::getSpeed ()
    {
    if (millis () - last_hs_sesnsed > 500)
        return 0.0;

    return speed;
    }

HallSensor::HallSensor (double wheelDia):
    last_hs_sesnsed (millis ()),
    dia (wheelDia),
    speed (0.0)
    {
    
    }
