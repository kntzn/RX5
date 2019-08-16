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

#define PACK_SIZE_MAX 16
#define EOP 0x00

class Communication
    {
    private:
        sarray <uint8_t, PACK_SIZE_MAX + 1> inputBuf;

        
    public:
        Communication ();        

        void sendPacket (uint8_t* pack, size_t len);
        size_t receivePacket (uint8_t* pack);
    };


#endif

