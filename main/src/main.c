#include "main/utils.h"
#include "pp_avl/pp_avl_tree.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define DATA_DIR "../data/"

int test_avl_strings(){
    FILE* in = fopen(DATA_DIR"in3.txt", "r");
    FILE* out = fopen(DATA_DIR"out3.txt", "r");
    avl_tree_t* map = avl_tree_init(cmp_string, free_val, free_val);
    int n;
    int flag = 1;
    fscanf(in, "%d", &n);
    for(int i=0; i<n; i++){
        char* val = get_string(in);
        char* key = get_string(in);
        avl_tree_put(map, key, val);
    }
    fscanf(in, "%d", &n);
    for(int i=0; i<n; i++){
        char* key = get_string(in);
        char* sol = get_string(out);
        char* val = avl_tree_get(map, key);
        if((!val && strcmp(sol, "eh")!=0) || (val && strcmp(sol, val)!= 0)){
            printf("Error : %s %s \n", val, sol);
            flag = 0;
        }
        else{
            //printf("%s\n", val);
        }
        free(key);
        free(sol);
    }

    avl_tree_free(map);
    fclose(in);
    fclose(out);
    return flag;
}

int test_avl_strings_removeall(){
    FILE* in = fopen(DATA_DIR"in3.txt", "r");
    FILE* out = fopen(DATA_DIR"out3.txt", "r");
    avl_tree_t* map = avl_tree_init(cmp_string, free_val, free_val);
    int n;
    int flag = 1;
    fscanf(in, "%d", &n);
    for(int i=0; i<n; i++){
        char* val = get_string(in);
        char* key = get_string(in);
        avl_tree_put(map, key, val);
    }
    fscanf(in, "%d", &n);
    for(int i=0; i<n; i++){
        char* key = get_string(in);
        char* sol = get_string(out);
        char* val = avl_tree_get(map, key);
        if((!val && strcmp(sol, "eh")!=0) || (val && strcmp(sol, val)!= 0)){
            printf("Error : %s %s \n", val, sol);
            flag = 0;
        }
        else{
            //printf("%s\n", val);
        }
        free(key);
        free(sol);
    }
    void* to_remove = NULL;
    while( to_remove = avl_tree_find_by_order(map, 0) ){
        avl_tree_remove(map, to_remove);
    }
    free(map);

    fclose(in);
    fclose(out);
    return flag;
}


int test_avl_random(){
    FILE* in = fopen(DATA_DIR"in1.txt", "r");
    FILE* out = fopen(DATA_DIR"out1.txt", "r");
    avl_tree_t* map = avl_tree_init(cmp_int, free_val, dont_free);
    int flag = 1;
    for(int i=0; i<100000; i++){
        int q, k;
        fscanf(in, "%d %d", &q, &k);
        int* key = malloc(sizeof(int));

        memcpy(key, &k, sizeof(int));
        if(q == 0){
            if(avl_tree_contains(map, key) == 0){
                //we need only a set, so don't store any value
                avl_tree_put(map, key, NULL);
            }
            else{
                avl_tree_remove(map, key);
                free(key);
            }
        }
        else{
            int sol = avl_tree_contains(map, key);
            int tmp;
            fscanf(out, "%d", &tmp);
            if(tmp!=sol){
                printf("%d: %d %d ERROR!\n",k, sol, tmp);
                flag = 0;
            }
            free(key);
        }
    }
    fclose(in);
    fclose(out);
    avl_tree_free(map);
    return flag;
}

int main(){
    printf("Starting tests:\n");
    printf("Test random: %d\n", test_avl_random());
    printf("Test strings: %d\n",test_avl_strings());
    printf("Test remove: %d\n",test_avl_strings());
}
