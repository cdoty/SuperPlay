#pragma once

#include <TinySTL\stdint.h>

#include "GameDefines.h"

struct SRAMStruct
{
	// Init count
	uint32_t	uInitCount;

	// Padding
	uint8_t		uPadding[gsc_iSRAMSize - sizeof(uint32_t)];
};
