#include "Comm.h"
#include "cobs.h"
#include "Pinout.h"

void Communication::sendPacket (uint8_t* pack, size_t len)
    {
    assert (len <= PACK_SIZE_MAX);

    uint8_t cobsEncodedPack [PACK_SIZE_MAX + 1] = { };
    size_t cobsEncodedPackLen =
        COBS::encode (pack, len, cobsEncodedPack);

    // Actual packet
    Serial.write (cobsEncodedPack, cobsEncodedPackLen);
    // EOP byte
    Serial.write (EOP);
    }

size_t Communication::receivePacket (uint8_t * pack)
    {
    // Reads the serial
    while (Serial.available ())
        {
        inputBuf.push_back (Serial.read ());
        
        }

    // Searches for the EOP symb.
    int eop = -1;
    for (int i = 0; i < inputBuf.size (); i++)
        if (inputBuf [i] == EOP)
            {
            eop = i;
            break;
            }

    // Decodes the message if it is avail.
    size_t cobsDecodedPackLen = 0;
    if (eop != -1)
        {
        cobsDecodedPackLen =
            COBS::decode (inputBuf.data (), eop, pack);
        }
    
    // Removes the message from the buffer
    if (eop != -1)
        {

        size_t initial_size = inputBuf.size ();

        uint8_t* data = inputBuf.data ();

        for (int i = 0; i < initial_size - eop - 1; i++)
            { 
            data [i] = data [i + eop + 1];    
            
            }

        for (int i = 0; i < eop + 1; i++)
            inputBuf.pop_back ();

        }

    return cobsDecodedPackLen;
    }

Communication::Communication ()
    {
    }
