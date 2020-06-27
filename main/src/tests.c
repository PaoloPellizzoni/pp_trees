#include "main/utils.h"
#include "main/tests.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int test_avl_babel(char* filename){
    FILE* input = fopen(DATA_DIR"in2.txt", "r");
    if(!input){
        fprintf(stderr, "Missing file\n");
        exit(EXIT_FAILURE);
    }
    FILE* solution = fopen(DATA_DIR"out2.txt", "r");
    if(!solution){
        fprintf(stderr, "Missing file\n");
        exit(EXIT_FAILURE);
    }
    FILE* output;
    if(filename[0]){
        output = fopen(filename, "w");
        if(!output){
            fprintf(stderr, "Can't create file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
    avl_tree_t* map = avl_tree_init(cmp_string, free_val, free_val);
    int n;
    int flag = 1;
    fscanf(input, "%d", &n);
    for(int i=0; i<n; i++){
        char* val = get_string(input);
        char* key = get_string(input);
        avl_tree_put(map, key, val);
    }
    fscanf(input, "%d", &n);
    for(int i=0; i<n; i++){
        char* key = get_string(input);
        char* sol = get_string(solution);
        char* val = avl_tree_get(map, key);
        if(filename[0]){
            fprintf(output, "%s\n", val);
        }

        if((!val && strcmp(sol, "eh")!=0) || (val && strcmp(sol, val)!= 0)){
            fprintf(stderr, "Error : %s %s \n", val, sol);
            flag = 0;
        }
        else{
            // DO NOTHING
        }
        free(key);
        free(sol);
    }

    avl_tree_free(map);
    fclose(input);
    fclose(solution);
    if(filename[0])
        fclose(output);
    return flag;
}

int test_avl_strings_removeall(char* filename){
    FILE* input = fopen(DATA_DIR"in2.txt", "r");
    if(!input){
        fprintf(stderr, "Missing file\n");
        exit(EXIT_FAILURE);
    }
    FILE* solution = fopen(DATA_DIR"out2.txt", "r");
    if(!solution){
        fprintf(stderr, "Missing file\n");
        exit(EXIT_FAILURE);
    }
    FILE* output;
    if(filename[0]){
        output = fopen(filename, "w");
        if(!output){
            fprintf(stderr, "Can't create file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
    avl_tree_t* map = avl_tree_init(cmp_string, free_val, free_val);
    int n;
    int flag = 1;
    fscanf(input, "%d", &n);
    for(int i=0; i<n; i++){
        char* val = get_string(input);
        char* key = get_string(input);
        avl_tree_put(map, key, val);
    }
    fscanf(input, "%d", &n);
    for(int i=0; i<n; i++){
        char* key = get_string(input);
        char* sol = get_string(solution);
        char* val = avl_tree_get(map, key);
        if(filename[0]){
            fprintf(output, "%s\n", val);
        }

        if((!val && strcmp(sol, "eh")!=0) || (val && strcmp(sol, val)!= 0)){
            fprintf(stderr, "Error : %s %s \n", val, sol);
            flag = 0;
        }
        else{
            // DO NOTHING
        }
        free(key);
        free(sol);
    }
    void* to_remove = NULL;
    while( to_remove = avl_tree_find_by_order(map, 0) ){
        avl_tree_remove(map, to_remove);
    }
    free(map);

    fclose(input);
    fclose(solution);
    if(filename[0]){
        fclose(output);
    }
    return flag;
}


int test_avl_random(char* filename){
    FILE* input = fopen(DATA_DIR"in1.txt", "r");
    if(!input){
        fprintf(stderr, "Missing file\n");
        exit(EXIT_FAILURE);
    }
    FILE* solution = fopen(DATA_DIR"out1.txt", "r");
    if(!solution){
        fprintf(stderr, "Missing file\n");
        exit(EXIT_FAILURE);
    }
    FILE* output;
    if(filename[0]){
        output = fopen(filename, "w");
        if(!output){
            fprintf(stderr, "Can't create file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
    avl_tree_t* map = avl_tree_init(cmp_int, free_val, dont_free);
    int flag = 1;
    for(int i=0; i<100000; i++){
        int q, k;
        fscanf(input, "%d %d", &q, &k);
        int* key = malloc(sizeof(int));
        if(!key){
            fprintf(stderr, "Failed allocation\n");
            exit(EXIT_FAILURE);
        }
        memcpy(key, &k, sizeof(int));
        if(q == 0){ // update
            if(avl_tree_contains(map, key) == 0){
                //we need only a set, so don't store any value
                avl_tree_put(map, key, NULL);
            }
            else{
                avl_tree_remove(map, key);
                free(key);
            }
        }
        else{ //query
            int val = avl_tree_contains(map, key);
            if(filename[0])
                fprintf(output, "%d\n", val);

            int sol;
            fscanf(solution, "%d", &sol);
            if(val!=sol){
                fprintf(stderr, "Error : %d %d \n", val, sol);
                flag = 0;
            }
            free(key);
        }
    }
    fclose(input);
    fclose(solution);
    if(filename[0])
        fclose(output);
    avl_tree_free(map);
    return flag;
}

int test_segment_basic(char* filename){
    int flag = 1;
    int* a = calloc(10, sizeof(int));
    a[2] = 1;
    a[9] = 3;
    segment_node_t* root = segment_node_init(a, 0, 10);
    int val;
    val = segment_node_sum(root, 0, 10);
    if(val != 4){
        fprintf(stderr, "Error : %d %d \n", val, 4);
        flag = 0;
    }
    val = segment_node_sum(root, 0, 3);
    if(val != 1){
        fprintf(stderr, "Error : %d %d \n", val, 1);
        flag = 0;
    }
    segment_node_update(root, 0, 1, +4); //point update
    val = segment_node_sum(root, 0, 3);
    if(val != 5){
        fprintf(stderr, "Error : %d %d \n", val, 5);
        flag = 0;
    }
    segment_node_update(root, 1, 6, +1); //range update
    val = segment_node_sum(root, 0, 3);
    if(val != 7){
        fprintf(stderr, "Error : %d %d \n", val, 7);
        flag = 0;
    }

    return flag;
}


int test_segment_potentiometer(char* filename){
    FILE* input = fopen(DATA_DIR"in3.txt", "r");
    if(!input){
        fprintf(stderr, "Missing file\n");
        exit(EXIT_FAILURE);
    }
    FILE* solution = fopen(DATA_DIR"out3.txt", "r");
    if(!solution){
        fprintf(stderr, "Missing file\n");
        exit(EXIT_FAILURE);
    }
    FILE* output;
    if(filename[0]){
        output = fopen(filename, "w");
        if(!output){
            fprintf(stderr, "Can't create file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
    int flag = 1;
    while(1){
        int n;
        fscanf(input, "%d", &n);
        if(!n) break;

        int* a = calloc(n, sizeof(int));
        if(!a){
            fprintf(stderr, "Failed allocation\n");
            exit(EXIT_FAILURE);
        }

        for(int i=0; i<n; i++)
            fscanf(input, "%d", &a[i]);

        segment_node_t* root = segment_node_init(a, 0, n);

        char buf[65];
        int l, r, sol;
        int cases = 0;
        fscanf(solution, "%64s", buf);
        fscanf(solution, "%64s", buf); //get rid of "Case: ..."
        if(filename[0]){
            fprintf(output, "Case: %d\n", ++cases);
        }
        while(1){
            fscanf(input, "%64s", buf);
            if(buf[0] == 'E') break;
            fscanf(input, "%d %d",&l, &r);
            if(buf[0] == 'M'){ //query
                l--; r--; //was 1-based
                int val = segment_node_sum(root, l, r+1);
                if(filename[0]){
                    fprintf(output, "%d\n", val);
                }
                fscanf(solution, "%d", &sol);
                if(val!=sol){
                    fprintf(stderr, "Error : %d %d \n", val, sol);
                    flag = 0;
                }

            }
            else{ //update
                l--; // was 1-based
                segment_node_update(root, l, l+1, r); //set position l to value r
            }
        }
        segment_node_free(root);
    }

    fclose(input);
    fclose(solution);
    if(filename[0])
        fclose(output);

    return flag;
}
