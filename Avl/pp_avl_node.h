#ifndef PP_AVL_NODE_H_
#define PP_AVL_NODE_H_

typedef int (*comparator_func) (const void*, const void*);
typedef void (*deleter_func) (void*);


struct avl_node
{
    int balance_factor;
    int height;
    int subtree_size;
    
    void* val;
    void* key;
    
    struct avl_node* left;
    struct avl_node* right;
} typedef avl_node_t;

avl_node_t* avl_node_init(void* key, void* val);
void avl_node_free(avl_node_t* node, deleter_func delete_key, deleter_func delete_val);
avl_node_t* avl_node_get(avl_node_t* node, void* key, comparator_func cmpf);
avl_node_t* avl_node_insert(avl_node_t* node, void* key, void* val, comparator_func cmpf);
avl_node_t* avl_node_get_first(avl_node_t* node);
avl_node_t* avl_node_get_last(avl_node_t* node);
avl_node_t* avl_node_remove(avl_node_t* node, void* key, comparator_func cmpf);
int avl_node_order_of_key(avl_node_t* node, void* key, comparator_func cmpf);
avl_node_t* avl_node_find_by_order(avl_node_t* node, int order, comparator_func cmpf);

void avl_node_update(avl_node_t* node);
avl_node_t* avl_node_balance(avl_node_t* node);
avl_node_t* avl_node_left_left_balance(avl_node_t* node);
avl_node_t* avl_node_left_right_balance(avl_node_t* node);
avl_node_t* avl_node_right_left_balance(avl_node_t* node);
avl_node_t* avl_node_right_right_balance(avl_node_t* node);
avl_node_t* avl_node_left_rotation(avl_node_t* node);
avl_node_t* avl_node_right_rotation(avl_node_t* node);

#endif
