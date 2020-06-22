#include <stdio.h>

int cmp_int(const void* a, const void* b);
int cmp_string(const void* a, const void* b);

void free_val(void* s);
void dont_free(void* s);

char* get_string(FILE* file);
