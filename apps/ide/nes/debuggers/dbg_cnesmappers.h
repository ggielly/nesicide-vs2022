#if !defined ( MAPPERS_H )
#define MAPPERS_H

#include "nes_emulator_core.h"

using MapperInfo = struct _MapperInfo
{
	const char* name;
	int32_t id;
};

extern MapperInfo mapper[];
const char* mapperNameFromID(int32_t id);
int mapperIndexFromID(int32_t id);
int mapperIDFromIndex(int32_t index);

#endif
