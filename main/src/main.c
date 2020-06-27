#include "main/tests.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int N_OF_TESTS = 5;

int main(int argc, char** argv){
    int opt;
    char* tmp;
    int t = -1; //test number
    int p = 0; //print to file
    char filename[65];
    memset(filename, 0, sizeof(filename));
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
                    fprintf (stderr, "Unknown argument\n", optopt);
                exit(EXIT_FAILURE);
                break;
            default:
                exit(EXIT_FAILURE);

        }
    }
    if(t < 0 || t > N_OF_TESTS){
        fprintf (stderr, "Test number must be in range 0 - %d\n", N_OF_TESTS);
        exit(EXIT_FAILURE);
    }
    printf("Starting tests:\n");
    switch (t) {
        case 0:
            printf("Test avl random: %d\n", test_avl_random(filename));
            printf("Test avl strings: %d\n",test_avl_babel(filename));
            printf("Test avl remove: %d\n",test_avl_strings_removeall(filename));
            printf("Test segment basic: %d\n",test_segment_basic(filename));
            printf("Test segment pote: %d\n",test_segment_potentiometer(filename));
            break;
        case 1:
            printf("Test avl random: %d\n", test_avl_random(filename));
            break;
        case 2:
            printf("Test avl strings: %d\n",test_avl_babel(filename));
            break;
        case 3:
            printf("Test avl remove: %d\n",test_avl_strings_removeall(filename));
            break;
        case 4:
            printf("Test segment basic: %d\n",test_segment_basic(filename));
            break;
        case 5:
            printf("Test segment pote: %d\n",test_segment_potentiometer(filename));
            break;
        default:
            exit(EXIT_FAILURE);
    }






}
