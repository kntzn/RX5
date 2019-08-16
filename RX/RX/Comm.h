// Comm.h

#ifndef _COMM_h
#define _COMM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "cobs.h"
#include <assert.h>

#define PACK_SIZE_MAX 16

class Communication
    {
    private:
        void sendPacket (uint8_t* pack, size_t len);
        size_t receivePacket (uint8_t* pack);
    public:
        Communication ();        
    };


#endif

