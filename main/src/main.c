#include "main/tests.h"
#include "main/utils.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

const int N_OF_TESTS = 6;

int main(int argc, char** argv){
    int opt;
    char* tmp;
    int t = -1; //test number
    int p = 0; //print to file
    char filename[65];
    memset(filename, 0, sizeof(filename));
    // standard getopt routine
    while((opt = getopt(argc, argv, "t:p:")) != -1){
        switch (opt) {
            case 't':
                tmp = optarg;
                char* check = NULL;
                t = strtol(tmp, &check, 10);
                if(tmp == check){
                    fprintf (stderr, "Option -t requires an integer argument\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'p':
                p = 1;
                tmp = optarg;
                strncpy(filename, tmp, 64);

                break;
            case '?':
                if (optopt == 't')
                    fprintf (stderr, "Option -t requires an integer argument\n");
                else if (optopt == 'p')
                    fprintf (stderr, "Option -p requires a string argument\n");
                else
                    fprintf (stderr, "Unknown argument\n");
                exit(EXIT_FAILURE);
                break;
            default:
                exit(EXIT_FAILURE);

        }
    }
    if(t < 0 || t > N_OF_TESTS){
        fprintf (stderr, "Test number must be in range 0 - %d. Set it with -t\n", N_OF_TESTS);
        exit(EXIT_FAILURE);
    }
    char pre[70];
    printf("Starting tests:\n");
    clock_t start_time = clock();
    switch (t) {
        case 0:
            strcpy(pre, "1_");
            printf("Test avl random: %s\n", test_avl_random( filename[0] ? strcat(pre, filename) : filename) ? "SUCCESS" : "FAIL");
            strcpy(pre, "2_");
            printf("Test avl strings: %s\n",test_avl_babel(filename[0] ? strcat(pre, filename) : filename)? "SUCCESS" : "FAIL");
            strcpy(pre, "3_");
            printf("Test avl remove: %s\n",test_avl_strings_removeall(filename[0] ? strcat(pre, filename) : filename)? "SUCCESS" : "FAIL");
            strcpy(pre, "4_");
            printf("Test avl order statistics: %s\n", test_avl_order_statistics( filename[0] ? strcat(pre, filename) : filename) ? "SUCCESS" : "FAIL");
            strcpy(pre, "5_");
            printf("Test segment basic: %s\n",test_segment_basic(filename[0] ? strcat(pre, filename) : filename)? "SUCCESS" : "FAIL");
            strcpy(pre, "6_");
            printf("Test segment pote: %s\n",test_segment_potentiometer(filename[0] ? strcat(pre, filename) : filename)? "SUCCESS" : "FAIL");
            printf("Tests took %2.6f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
            break;
        case 1:
            printf("Test avl random: %s\n", test_avl_random(filename)? "SUCCESS" : "FAIL");
            printf("Test took %2.6f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
            break;
        case 2:
            printf("Test avl strings: %s\n",test_avl_babel(filename)? "SUCCESS" : "FAIL");
            printf("Test took %2.6f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
            break;
        case 3:
            printf("Test avl remove: %s\n",test_avl_strings_removeall(filename)? "SUCCESS" : "FAIL");
            printf("Test took %2.6f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
            break;
        case 4:
            printf("Test avl order statistics: %s\n",test_avl_order_statistics(filename)? "SUCCESS" : "FAIL");
            printf("Test took %2.6f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
        case 5:
            printf("Test segment tree basic: %s\n",test_segment_basic(filename)? "SUCCESS" : "FAIL");
            printf("Test took %2.6f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
            break;
        case 6:
            printf("Test segment tree potentiometer: %s\n",test_segment_potentiometer(filename)? "SUCCESS" : "FAIL");
            printf("Test took %2.6f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
            break;
        default:
            exit(EXIT_FAILURE);
    }

    return 0;
}
