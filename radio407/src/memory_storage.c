#include "global.h"
#include "memory_storage.h"
#include <stdbool.h>


float testFloat = 5.55f;

enum varPtrNames{
	STORAGE_TEST_VAR,
	STORAGE_VAR_NR
};

void *varPrtList[STORAGE_VAR_NR] = {
	&testFloat,
};

void memorySaveVar(int varID){
	// read block
	uint8_t thisBlock[256] = {0};

}
