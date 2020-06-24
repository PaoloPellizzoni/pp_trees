#include "main/utils.h"
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 64

int cmp_int(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

int cmp_string(const void* _a, const void* _b){
    char* a = (char*)_a;
    char* b = (char*)_b;
    int i = 0;
    while(a[i] && b[i]){
        if(a[i] < b[i]) return 1;
        if(a[i] > b[i]) return -1;
        i++;
    }
    if(a[i] == b[i]) return 0;
    return b[i] ? 1 : -1;
}

void free_val(void* s){
    //printf("Freeing %p\n", s);
    free(s);
}

void dont_free(void* s){
    //printf("Freeing %p\n", s);
}

char* get_string(FILE* file){
    char buf[65];
    memset(buf, 0, sizeof(buf));
    fscanf(file, "%64s", buf);
    //while(getchar()!='\n');
    char* s = calloc(1, strlen(buf)+1);
    if(!s) return NULL;
    memcpy(s, buf, strlen(buf)+1);
    return s;
}
