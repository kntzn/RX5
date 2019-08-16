/*
 Name:		RX.ino
 Created:	8/6/2019 12:13:15 AM
 Author:	kntzn
*/

#include "Comm.h"
#include "Pinout.h"


#include <TM1637Display.h>
#include "Battery.h"
#include <Servo.h>

void initialize ()
    { 
    // inits the uC
    init ();

    pinMode (HC12_SET,      OUTPUT);
    digitalWrite (HC12_SET, HIGH);

    pinMode (HALL,          INPUT);
    pinMode (PPM,           OUTPUT);
    
    // Lights
    pinMode (LIGHTS_FRONT,  OUTPUT);
    analogWrite (LIGHTS_FRONT,   0);
    pinMode (LIGHTS_BACK,   OUTPUT);
    analogWrite (LIGHTS_BACK,    0);
    
    pinMode (BUZZER,        OUTPUT);
    
    // Unused pins
    pinMode (GROUNDED_0,    INPUT);
    pinMode (GROUNDED_1,    INPUT);

    pinMode (SD_CS,         OUTPUT);

    // XTL Wattmeter
    pinMode (SHUNT_POS,     INPUT);
    pinMode (SHUNT_NEG,     INPUT);
    pinMode (V_BAT,         INPUT);

    pinMode (THERM,         INPUT);

    // Display 
    pinMode (DISPLAY_SDA,  OUTPUT);
    pinMode (DISPLAY_SCL,  OUTPUT);
    }

int main ()
    { 
    initialize ();

    TM1637Display disp (DISPLAY_SCL, DISPLAY_SDA);
    disp.setBrightness (7);
    
    Battery battety;
    battety.batMeasure (V_BAT);
    unsigned long last_bat_upd = millis ();
    

    Servo VESC;
    VESC.attach (PPM);
    VESC.writeMicroseconds (1500);
    unsigned long last_avail = millis ();
    byte last_reading = 127;
    const int FAILSAFE_RAMP_UP = 2000;
    const int FAILSAFE_MS      = 500;

    Serial.begin (9600);
    
    // Beeps 6 times at startup
    for (int i = 0; i < 6; i++)
        { 
        digitalWrite (BUZZER, HIGH);
        delay (100);
        digitalWrite (BUZZER, LOW);
        delay (200);
        }

    Communication HC12;
    uint8_t test_buf [PACK_SIZE_MAX + 1] = { };

    

    // Main cycle
    while (true)
        {

        if (HC12.receivePacket (test_buf))
            { 
            if (test_buf [0] == 0x02 &&
                test_buf [1] == 0x04 &&
                test_buf [2] == 0x08 &&
                test_buf [3] == 0x16)
                digitalWrite (BUZZER, HIGH);
            }


        if (millis () - last_bat_upd > 500)
            { 
            battety.batMeasure (V_BAT);
            disp.showNumberDec (int (battety.getBatVoltage () * 10.0) * 10);
            last_bat_upd += 500;
            }

        // Comm v.1
        /*

        // Waits for packets from TX
        while (Serial.available ())
            {
            byte reading = Serial.read ();

            VESC.writeMicroseconds (map (255 - reading, 0, 255, 1000, 2000));
            last_reading = reading;
            
            last_avail = millis ();
            }
        
        // Failsafe handler 
        // Also beeps for FAILSAFE_RAMP_UP ms when diconnects
        // TODO: move to a func.
        if (millis () - last_avail > FAILSAFE_MS)
            {
            unsigned long delta = (millis () - last_avail) - FAILSAFE_MS;

            if (delta < FAILSAFE_RAMP_UP)
                {
                float k = float (delta) / float (FAILSAFE_RAMP_UP);

                int toVESC = k * 1000 +
                    (1.f - k) * (map (last_reading, 0, 255, 1000, 2000));

                VESC.writeMicroseconds (toVESC);

                digitalWrite (BUZZER, HIGH);
                }
            else
                {
                VESC.writeMicroseconds (1000);

                digitalWrite (BUZZER, LOW);
                }
            
            }
        else
            digitalWrite (BUZZER, LOW);
*/

        // Currently unused
        /*
        if (millis () - last_send > 50)
            { 
            Serial.print (char ((testCommByte++) % 256));
            last_send = millis ();
            }*/
        }
    }