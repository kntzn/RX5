// Comm.h


#ifndef _COMM_h
#define _COMM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <stdint.h>
#include <stddef.h>

#define StartBlock()	(code_ptr = dst++, code = 1)
#define FinishBlock()	(*code_ptr = code)

#include "sarray.h"
#include <assert.h>

#define PACK_SIZE_MAX 64
#define PACK_SIZE_DEFAULT 3
#define EOP 0x00

#define REQUEST_PERIOD 1000
#define RESPONSE_TIMEOUT 50
#define REQUEST_TIMEOUT 500
#define RESPONSE_PACKETS 5


class Communication
    {
    private:
        sarray <uint8_t, PACK_SIZE_MAX + 1> inputBuf;
        uint8_t buffer [PACK_SIZE_DEFAULT];
        
    public:
        enum command
            {
            throttle     = 'T',
            voltage      = 'V',
            voltage_resp = 'v',
            raw          = 'R'
            };

        Communication ();        

        void sendPacket (uint8_t* pack, size_t len);
        size_t receivePacket (uint8_t* pack);

        // Returns ptr to the args. array
        uint8_t *argbuf ();

    };


#endif

