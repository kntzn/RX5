#include "Comm.h"

void Communication::sendPacket (uint8_t* pack, size_t len)
    {
    assert (len <= PACK_SIZE_MAX);

    uint8_t cobsEncodedPack [PACK_SIZE_MAX + 1] = { };
    size_t cobsEncodedPackLen =
        COBS::encode (pack, len, cobsEncodedPack);

    // Actual packet
    Serial.write (cobsEncodedPack, cobsEncodedPackLen);
    // EOP byte
    Serial.write (0x00);
    }

size_t Communication::receivePacket (uint8_t * pack)
    {
    
    return size_t ();
    }

Communication::Communication ()
    {
    }
