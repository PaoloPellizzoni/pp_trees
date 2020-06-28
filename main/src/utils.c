#include "main/utils.h"
#include <stdlib.h>
#include <string.h>

/**
 * @param a: A pointer to an integer
 * @param b: A pointer to an integer
 * @brief A natural order comparator function for integers
 */
int cmp_int(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

/**
 * @param a: A pointer to the first char of the string
 * @param b: A pointer to the first char of the string
 * @brief A lexicogrphic order comparator function for strings
 */
int cmp_string(const void* a, const void* b){
    char* _a = (char*)a;
    char* _b = (char*)b;
    int i = 0;
    while(_a[i] && _b[i]){
        if(_a[i] < _b[i]) return 1;
        if(_a[i] > _b[i]) return -1;
        i++;
    }
    if(_a[i] == _b[i]) return 0;
    return _b[i] ? 1 : -1;
}

/**
 * @param s: A pointer
 * @brief A wrapper function for free(), useful for debug purposes
 */
void free_val(void* s){
    //printf("Freeing %p\n", s); //Debug purposes only
    free(s);
}

/**
 * @param s: A pointer
 * @brief An empty function, useful for debug purposes
 */
void dont_free(void* s){
    //printf("Freeing %p\n", s);  //Debug purposes only
}

/**
 * @param file: A FILE pointer
 * @returns a heap-allocated char array.
 * @brief This function reads a string of up to 64 chars and allocates it on the heap.
        It is used to allocate keys as stack-allocated strings could be deleted after being inserted in the map.
 */
char* get_string(FILE* file){
    char buf[65];
    memset(buf, 0, sizeof(buf));
    fscanf(file, "%64s", buf);
    //while(getchar()!='\n'); // not working when reading from file
    char* s = calloc(1, strlen(buf)+1);
    if(!s){
        fprintf(stderr, "Failed allocation\n");
        return NULL;
    }
    memcpy(s, buf, strlen(buf)+1);
    return s;
}
