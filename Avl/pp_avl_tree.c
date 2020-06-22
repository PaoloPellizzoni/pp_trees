#include "pp_avl_tree.h"
#include "pp_avl_node.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @param cmpf: a pointer to the key comparator function
 * @returns a pointer to the newly created tree, or NULL if the allocation failed.
 */
avl_tree_t* avl_tree_init(comparator_func cmpf, deleter_func del_key, deleter_func del_val){
    avl_tree_t* tree = calloc(1, sizeof(avl_tree_t));
    if(!tree) return NULL;
    
    tree->root = NULL;
    tree->cmpf = cmpf;
    tree->del_key = del_key;
    tree->del_val = del_val;
    return tree;
}

/**
 * @param self: a pointer to the map
 * @param delete_key: a pointer to the key delete function, or NULL if not necessary
 * @param delete_val: a pointer to the value delete function, or NULL if not necessary
 * @brief frees the entire map
 */
void avl_tree_free(avl_tree_t* self){
    avl_node_free(self->root, self->del_key, self->del_val);
    free(self);
}

/**
 * @param self: a pointer to the map
 * @param key: the key to be searched
 * @returns the value associated to the key, or null if not present
 */
void* avl_tree_get(avl_tree_t* self, void* key){
    avl_node_t* node = avl_node_get(self->root, key, self->cmpf);
    if(!node) return NULL;
    return node->val;
}

/**
 * @param self: a pointer to the map
 * @param key: the key to be searched
 * @returns true if the key is present, or false otherwise
 */
int avl_tree_contains(avl_tree_t* self, void* key){
    avl_node_t* node = avl_node_get(self->root, key, self->cmpf);
    if(!node) return 0;
    return 1;
}

/**
 * @param self: a pointer to the map
 * @param key: the key to be inserted
 * @param key: the value associated to the key
 * @returns true if the insertion created a new node, or false if the insertion updated an already existing one.
 */
int avl_tree_put(avl_tree_t* self, void* key, void* val){
    avl_node_t* node = avl_node_get(self->root, key, self->cmpf);
    if(!node){
        self->root = avl_node_insert(self->root, key, val, self->cmpf);
        return 1;
    }
    else{
        self->del_val(node->val);
        node->val = val;
        return 0;
    }
}

/**
 * @param self: a pointer to the map
 * @param key: the key to be removed
 * @returns false if the map did not contain the key, or true if it did it was then removed.
 */
int avl_tree_remove(avl_tree_t* self, void* key){
    avl_node_t* node = avl_node_get(self->root, key, self->cmpf);
    if(!node) return 0;
    self->root = avl_node_remove(self->root, key, self->cmpf);
    return 1;
}

/**
 * @param self: a pointer to the map
 * @returns the number of nodes in the map
 */
int avl_tree_size(avl_tree_t* self){
    return self->root->subtree_size;
}

/**
 * @param self: a pointer to the map
 * @returns true if the map is empty, or false otherwise
 */
int avl_tree_isEmpty(avl_tree_t* self){
    return (self->root->subtree_size) == 0;
}

/**
 * @param self: a pointer to the map
 * @param key: a key
 * @returns the position of the key in the ordered key set
 */
int avl_tree_order_of_key(avl_tree_t* self, void* key){
    return avl_node_order_of_key(self->root, key, self->cmpf);
}

/**
 * @param self: a pointer to the map
 * @param order: an integer 
 * @returns the key in the queried position in the ordered key set
 */
void* avl_tree_find_by_order(avl_tree_t* self, int order){
    avl_node_t* node = avl_node_find_by_order(self->root, order, self->cmpf);
    return (node ? node->key : NULL);
}
