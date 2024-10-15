#include "mem.h"
#include <stdint.h>

void memset(void *dest, char data, uint32_t count) {
	char* tmp = (char *)dest;
	while (count != 0) {
		count--;
		*tmp++ = data;
	}
}
