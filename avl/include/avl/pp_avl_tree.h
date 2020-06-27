#ifndef PP_AVL_TREE_H_
#define PP_AVL_TREE_H_

#include "avl/pp_avl_node.h"

struct avl_tree
{
    struct avl_node* root;
    comparator_func cmpf;
    deleter_func del_key, del_val;
} typedef avl_tree_t;

avl_tree_t* avl_tree_init(comparator_func cmpf, deleter_func del_key, deleter_func del_val);
void avl_tree_free(avl_tree_t* self);
void* avl_tree_get(avl_tree_t* self, void* key);
int avl_tree_contains(avl_tree_t* self, void* key);
int avl_tree_put(avl_tree_t* self, void* key, void* val);
int avl_tree_remove(avl_tree_t* self, void* key);
void avl_preorder(avl_tree_t* self);
int avl_size(avl_tree_t* self);
int avl_isEmpty(avl_tree_t* self);
int avl_tree_order_of_key(avl_tree_t* self, void* key);
void* avl_tree_find_by_order(avl_tree_t* self, int order);

#endif
