#pragma once

#include <TinySTL/stdint.h>

// Update CRC32
uint32_t updateCRC32(uint8_t _uValue, uint32_t _uCRC);

// Calculate CRC32
uint32_t calculateCRC32(uint8_t* _pBuffer, int _iLength);
