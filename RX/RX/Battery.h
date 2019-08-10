#pragma once
#include "Config.h"

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
            bat_voltage = readVcc ()*aver_analog (pin, 25U) / 1023 / 1000.0 + 0.5;

            // According to the volatge divider:
            bat_voltage /= (4300.0 / 24300.0)*DIVIDER_K;


            }
        double getBatVoltage ()
            { 
            return bat_voltage;
            }

    };








