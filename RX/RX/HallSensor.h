// HallSensor.h

#ifndef _HALLSENSOR_h
#define _HALLSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class HallSensor
    {
    private:
        uint8_t int_id;
        double dia;

        double speed;
        unsigned long int last_hs_sesnsed;


    public:
        HallSensor (double wheelDia);

        void interruptHandler ();

        double getSpeed ();
    };

#endif

