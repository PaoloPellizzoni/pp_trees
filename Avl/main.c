#include "utils.h"
#include "pp_avl_tree.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*
void test_avl_random(){
    FILE* in = fopen("in1.txt", "r");
    FILE* out = fopen("out1.txt", "r");
    avl_tree_t* map = avl_tree_init(cmp_int);
    for(int i=0; i<100000; i++){
        int q, k;
        fscanf(in, "%d %d", &q, &k);
        if(q == 0){
            if(avl_tree_contains(map, k) == 0)
                avl_tree_put(map, k, 0);
            else
                avl_tree_remove(map, k);
        }
        else{
            int sol = avl_tree_contains(map, k);
            int tmp ;
            fscanf(out, "%d", &tmp);
            //printf("%d : %d %d\n", k, sol, tmp);
            if(tmp!=sol)
                printf("%d: %d %d ERRORE!\n",k, sol, tmp);
        }
    }    
    printf("Finished");
    fclose(in);
    fclose(out);
    avl_tree_free(map, NULL, NULL);

}
*/
/*
int cmp_int(int a, int b){
    return a - b;
}

int cmp_string(char* a, char* b){
    int i = 0;
    while(a[i] && b[i]){
        if(a[i] < b[i]) return 1;
        if(a[i] > b[i]) return -1;
        i++;
    }
    if(a[i] == b[i]) return 0;
    return b[i] ? 1 : -1;
}

void free_string(char* s){
    free(s);
}

char* get_string(FILE* file){
    char buf[65];
    memset(buf, 0, sizeof(buf));
    fscanf(file, "%64s", buf);
    while(getchar()!='\n');
    char* s = calloc(1, strlen(buf)+1);
    if(!s) return NULL;
    memcpy(s, buf, strlen(buf)+1);
    return s;
}
*/
int main(){
    FILE* in = fopen("in4.txt", "r");
    FILE* out = fopen("out4.txt", "r");
    avl_tree_t* map = avl_tree_init(cmp_string, free_val, free_val);
    int n;
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
        }
        else{
            //printf("%s\n", val);
        }
        free(key);
        free(sol);
    }
    
    avl_tree_free(map);
    
    
}
