#include "main/utils.h"
#include "main/tests.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/**
 * @param filename: the name of the output file, if any
 * @returns 1 if the test is successful or 0 otherwise
 * @brief This function tests the avl tree against a randomly generated problemset whose solution is computed with a c++ std:map.
        The main aim of this function is to test the map functions put(), get() and remove() with simple keys and values.
 */
int test_avl_random(char* filename){
    FILE* input = fopen(DATA_DIR"in1.txt", "r");    //this is the input file
    if(!input){
        fprintf(stderr, "Missing file\n");
        exit(EXIT_FAILURE);
    }
    FILE* solution = fopen(DATA_DIR"out1.txt", "r"); //this is the solution file
    if(!solution){
        fprintf(stderr, "Missing file\n");
        exit(EXIT_FAILURE);
    }
    FILE* output;
    if(filename[0]){
        output = fopen(filename, "w");              //this is the output file, is filename exists
        if(!output){
            fprintf(stderr, "Can't create file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
    avl_tree_t* map = avl_tree_init(cmp_int, free_val, dont_free); //set appropriate deleter functions
    int flag = 1;
    for(int i=0; i<100000; i++){
        int q, k;                       // q is the type of query, k is the integer key
        fscanf(input, "%d %d", &q, &k);
        int* key = malloc(sizeof(int)); // we malloc an int to use it as a key
        if(!key){
            fprintf(stderr, "Failed allocation\n");
            avl_tree_free(map);         // free memory before exiting
            exit(EXIT_FAILURE);
        }
        memcpy(key, &k, sizeof(int));
        if(q == 0){ // update the map
            if(avl_tree_contains(map, key) == 0){   // if the key does not exist, put it in the set
                //we need only a set, so don't store any value
                int chk = avl_tree_put(map, key, NULL);
                if(chk == AVL_BAD_ALLOC){       // insertion failed
                    free(key);
                    avl_tree_free(map);         // free memory before exiting
                    exit(EXIT_FAILURE);
                }
            }
            else{                                   // if the key exists, remove it from the set
                avl_tree_remove(map, key);
                free(key);
            }
        }
        else{       //query
            int val = avl_tree_contains(map, key);
            if(filename[0])
                fprintf(output, "%d\n", val);

            int sol;
            fscanf(solution, "%d", &sol);   //read what the solution should be
            if(val!=sol){                   // and perform a check
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

/**
 * @param filename: the name of the output file, if any
 * @returns 1 if the test is successful or 0 otherwise
 * @brief This function tests the avl tree against the problem Babelfish (https://open.kattis.com/problems/babelfish).
        The main aim of this function is to test the map functions put() and get() with complex keys and values.
 */
int test_avl_babel(char* filename){
    FILE* input = fopen(DATA_DIR"in2.txt", "r");    //this is the input file
    if(!input){
        fprintf(stderr, "Missing file\n");
        exit(EXIT_FAILURE);
    }
    FILE* solution = fopen(DATA_DIR"out2.txt", "r"); //this is the solution file
    if(!solution){
        fprintf(stderr, "Missing file\n");
        exit(EXIT_FAILURE);
    }
    FILE* output;
    if(filename[0]){
        output = fopen(filename, "w");              //this is the output file
        if(!output){
            fprintf(stderr, "Can't create file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
    avl_tree_t* map = avl_tree_init(cmp_string, free_val, free_val); // set appropriate deleter functions
    int n;
    int flag = 1;
    fscanf(input, "%d", &n);    // read number of insertions
    for(int i=0; i<n; i++){
        char* val = get_string(input);
        if(!val){
            avl_tree_free(map);
            exit(EXIT_FAILURE);
        }
        char* key = get_string(input);
        if(!key){
            free(val);
            avl_tree_free(map);
            exit(EXIT_FAILURE);
        }
        int chk = avl_tree_put(map, key, val);
        if(chk == AVL_BAD_ALLOC){
            free(val);
            free(key);
            avl_tree_free(map);
            exit(EXIT_FAILURE);
        }
    }
    fscanf(input, "%d", &n);    // read number of queries
    for(int i=0; i<n; i++){
        char* key = get_string(input);
        if(!key){
            avl_tree_free(map);
            exit(EXIT_FAILURE);
        }
        char* sol = get_string(solution); // read what the solution should be
        if(!sol){
            free(key);
            avl_tree_free(map);
            exit(EXIT_FAILURE);
        }
        char* val = avl_tree_get(map, key);
        if(filename[0]){
            fprintf(output, "%s\n", val);
        }
        // check if the solution is correct, official solution is "eh" if the key is not present
        if((!val && strcmp(sol, "eh")!=0) || (val && strcmp(sol, val)!= 0)){ // check if the solution is correct
            fprintf(stderr, "Error : %s %s \n", val, sol);
            flag = 0;
        }
        // free key and sol, but not val as the map returns the pointer to the actual value stored,
        // and not a pointer to a copy of it. This performance-aiding design choice requires the user to be careful.
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


/**
 * @param filename: the name of the output file, if any
 * @returns 1 if the test is successful or 0 otherwise
 * @brief This function tests the avl tree against the problem Babelfish (https://open.kattis.com/problems/babelfish).
        The main aim of this function is to test the remove() and find_by_order() functions. Indeed the tree structure is
        freed by removing all of its nodes and not through the tree_free() function.
 */
 // this function is almost the same as the one above, for comments on the code please consult the aforementioned one.
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
        if(!val){
            avl_tree_free(map);
            exit(EXIT_FAILURE);
        }
        char* key = get_string(input);
        if(!key){
            free(val);
            avl_tree_free(map);
            exit(EXIT_FAILURE);
        }
        int chk = avl_tree_put(map, key, val);
        if(chk == AVL_BAD_ALLOC){
            free(val);
            free(key);
            avl_tree_free(map);
            exit(EXIT_FAILURE);
        }
    }
    fscanf(input, "%d", &n);
    for(int i=0; i<n; i++){
        char* key = get_string(input);
        if(!key){
            avl_tree_free(map);
            exit(EXIT_FAILURE);
        }
        char* sol = get_string(solution); // read what the solution should be
        if(!sol){
            free(key);
            avl_tree_free(map);
            exit(EXIT_FAILURE);
        }
        char* val = avl_tree_get(map, key);
        if(filename[0]){
            fprintf(output, "%s\n", val);
        }

        if((!val && strcmp(sol, "eh")!=0) || (val && strcmp(sol, val)!= 0)){
            fprintf(stderr, "Error : %s %s \n", val, sol);
            flag = 0;
        }
        free(key);
        free(sol);
    }
    void* to_remove = NULL;
    while( to_remove = avl_tree_find_by_order(map, 0) ){ //removes the first element
        if(filename[0])
            fprintf(output, "Removing key %s\n", (char*)to_remove);
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

/*
 * @param filename: the name of the output file (not used)
 * @returns 1 if the test is succesful or 0 otherwise
 * @brief This function tests the avl tree against a simple handmade problemset.
        The main aim of this function is to test the order statistics functions.
        This function does not take any input nor creates an output.
 *  This function is for debug purposes only, it is not memory-safe
void test_avl_order_statistics(char* filename){
    int flag = 1;
    avl_tree_t* tree = avl_tree_init(cmp_int, NULL, NULL);
    int** p = malloc(9*sizeof(int*));
    p[0] = malloc(sizeof(int)); *p[0] = 9;
    avl_tree_put(tree, p[0], 0);
    p[1] = malloc(sizeof(int)); *p[1] = 5;
    avl_tree_put(tree, p[1], 0);
    p[2] = malloc(sizeof(int)); *p[2] = 10;
    avl_tree_put(tree, p[2], 0);
    p[3] = malloc(sizeof(int)); *p[3] = 0;
    avl_tree_put(tree, p[3], 0);
    p[4] = malloc(sizeof(int)); *p[4] = 6;
    avl_tree_put(tree, p[4], 0);
    p[5] = malloc(sizeof(int)); *p[5] = 11;
    avl_tree_put(tree, p[5], 0);
    p[6] = malloc(sizeof(int)); *p[6] = -1;
    avl_tree_put(tree, p[6], 0);
    p[7] = malloc(sizeof(int)); *p[7] = 1;
    avl_tree_put(tree, p[7], 0);
    p[8] = malloc(sizeof(int)); *p[8] = 2;
    avl_tree_put(tree, p[8], 0);
    int val;
    if((val = avl_tree_order_of_key(tree, p[2]))!= 7){
        fprintf(stderr, "Error : %d %d \n", val, 7);
        flag = 0;
    }
    if((val = avl_tree_order_of_key(tree, p[5]))!= 8){
        fprintf(stderr, "Error : %d %d \n", val, 8);
        flag = 0;
    }
    if((val = avl_tree_order_of_key(tree, p[1]))!= 4){
        fprintf(stderr, "Error : %d %d \n", val, 4);
        flag = 0;
    }
    if((val = *((int*)avl_tree_find_by_order(tree, 5)))!= 6){
        fprintf(stderr, "Error : %d %d \n", val, 6);
        flag = 0;
    }

    avl_tree_free(tree);
    for(int i = 0; i < 8; i++)
        free(p[i]);
    free(p);

    return flag;
}
*/

/**
 * @param filename: the name of the output file (not used)
 * @returns 1 if the test is succesful or 0 otherwise
 * @brief This function tests the segment tree against a simple handmade problemset.
        The main aim of this function is to test the range updates.
        This function does not take any input nor creates an output.
 */
int test_segment_basic(char* filename){
    int flag = 1;
    int* a = calloc(10, sizeof(int));
    if(!a){
        fprintf(stderr, "Failed allocation\n");
        exit(EXIT_FAILURE);
    }
    a[2] = 1;
    a[9] = 3;
    // Now the vector is 0 0 1 0 0 0 0 0 0 3
    segment_node_t* root = segment_node_init(a, 0, 10);
    if(!root){
        free(a);
        exit(EXIT_FAILURE);
    }
    int val;
    val = segment_node_sum(root, 0, 10); //range sum query
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
    // Now the vector is 4 0 1 0 0 0 0 0 0 3
    val = segment_node_sum(root, 0, 3);
    if(val != 5){
        fprintf(stderr, "Error : %d %d \n", val, 5);
        flag = 0;
    }
    segment_node_update(root, 1, 6, +1); //range update
    // Now the vector is 4 1 2 1 1 1 0 0 0 3
    val = segment_node_sum(root, 0, 3);
    if(val != 7){
        fprintf(stderr, "Error : %d %d \n", val, 7);
        flag = 0;
    }

    segment_node_update(root, 4, 8, -1); //range update
    // Now the vector is 4 1 2 1 0 0 -1 -1 0 3
    val = segment_node_sum(root, 2, 7);
    if(val != 2){
        fprintf(stderr, "Error : %d %d \n", val, 2);
        flag = 0;
    }

    free(a);
    segment_node_free(root);
    return flag;
}

/**
 * @param filename: the name of the output file, if any
 * @returns 1 if the test is succesful or 0 otherwise
 * @brief This function tests the segment tree against the problem Potentiometers (https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3238).
        The main aim of this function is to test the performance of point updates and range queries.
        Note that this problem could be solved with the simpler non-lazy version of the segment tree.
 */
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
    while(1){           // loop until the flag value n = 0 is encountered
        int n;
        fscanf(input, "%d", &n);
        if(!n) break;

        int* a = calloc(n, sizeof(int));
        if(!a){
            fprintf(stderr, "Failed allocation\n");
            exit(EXIT_FAILURE);
        }

        for(int i=0; i<n; i++) // read the array form input
            fscanf(input, "%d", &a[i]);

        segment_node_t* root = segment_node_init(a, 0, n);
        if(!root){
            free(a);
            exit(EXIT_FAILURE);
        }

        char buf[65];
        int l, r, sol;
        int cases = 0;
        fscanf(solution, "%64s", buf);  // read twice...
        fscanf(solution, "%64s", buf);  // ...to get rid of "Case: k"
        if(filename[0]){
            fprintf(output, "Case: %d\n", ++cases);
        }
        while(1){                       // loop until "END" is encountered
            fscanf(input, "%64s", buf);
            if(buf[0] == 'E') break;    // it must be "END"
            fscanf(input, "%d %d",&l, &r);
            if(buf[0] == 'M'){          // range query
                l--; r--;               // was 1-based, make it 0-based
                int val = segment_node_sum(root, l, r+1);
                if(filename[0]){
                    fprintf(output, "%d\n", val);
                }
                fscanf(solution, "%d", &sol);   // read the official solution
                if(val!=sol){                   // and check it
                    fprintf(stderr, "Error : %d %d \n", val, sol);
                    flag = 0;
                }

            }
            else{                       // point update
                l--;                    // was 1-based
                int prev = segment_node_sum(root, l, l+1);
                r -= prev;              // now if I add r to prev I get the desired value
                segment_node_update(root, l, l+1, r);   //set position l to value r
            }
        }
        segment_node_free(root);
        free(a);
    }

    fclose(input);
    fclose(solution);
    if(filename[0])
        fclose(output);

    return flag;
}
