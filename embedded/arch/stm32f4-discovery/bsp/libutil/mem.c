#include <stddef.h>
void *memcpy(void *dest, const void *src, size_t n) {
unsigned i;
for (i=0; i<n; i++) {
((char *) dest)[i] = ((char *) src)[i];
}
return dest;
}
