
// Battery.h

#pragma once
#include "Config.h"



#ifndef _BATTERY_h
#define _BATTERY_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Battery
    {
    private:
        double bat_voltage;

        long aver_analog (uint8_t pin, byte times = 50);

        long readVcc ();
            

    public:
        Battery ();

        void batMeasure (byte pin)
            {
            int avr_inp = aver_analog (pin, 10U);
            
            bat_voltage = (readVcc ()*avr_inp / 1023 / 1000.0 + 0.5) * 0.06 +
                          bat_voltage * (1.0 - 0.06);

            

            


            }
        double getBatVoltage ()
            { 
            // According to the volatge divider:
            return bat_voltage / (4300.0 / 24300.0)*DIVIDER_K;
            }

    };


#endif







