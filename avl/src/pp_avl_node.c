#include "pp_avl/pp_avl_node.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @param key: the key of the new node
 * @param val: the value of the new node
 * @returns a pointer to the newly created node, or NULL if the allocation failed.
 */
avl_node_t* avl_node_init(void* key, void* val){
    avl_node_t* node = calloc(1, sizeof(avl_node_t));
    if(!node) return NULL;

    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->val = val;
    node->balance_factor = 0;
    node->height = 0;
    node->subtree_size = 1;
    return node;
}

/**
 * @param node: the root of the subtree to be freed
 * @param delete_key: a pointer to the key delete function, or NULL if not necessary
 * @param delete_val: a pointer to the value delete function, or NULL if not necessary
 * @brief frees the entire subtree
 */
void avl_node_free(avl_node_t* node, deleter_func delete_key, deleter_func delete_val){
    if(!node) return;
    avl_node_free(node->left, delete_key, delete_val);
    avl_node_free(node->right, delete_key, delete_val);

    if(delete_key)
        delete_key(node->key);
    if(delete_val)
        delete_val(node->val);

    free(node);
}

/**
 * @param node: the root of the subtree to search in
 * @param key: the key to be searched
 * @param cmpf: a pointer to the key comparator function
 * @returns a pointer to the requested node if present, or NULL otherwise.
 */
avl_node_t* avl_node_get(avl_node_t* node, void* key, comparator_func cmpf){
    if(!node) return NULL;
    int cmp = cmpf(key, node->key);
    if(cmp < 0)
        return avl_node_get(node->left, key, cmpf);
    if(cmp > 0)
        return avl_node_get(node->right, key, cmpf);
    return node;
}

/**
 * @param node: the root of the subtree to search in
 * @param key: the key to be searched
 * @param cmpf: a pointer to the key comparator function
 * @returns the 0-indexed order of the key in the subtree
 */
int avl_node_order_of_key(avl_node_t* node, void* key, comparator_func cmpf){
    if(!node) return -1;
    int order = 0;
    while(1){
        int cmp = cmpf(key, node->key);
        if(cmp == 0){
            return order + (node->left ? node->left->subtree_size : 0);
        }
        else if(cmp < 0){
            node = node->left;
            if(!node) return -1;
        }
        else{
            node = node->right;
            if(!node) return -1;
            order += 1+(node->left ? node->left->subtree_size : 0);
        }
    }
}

/**
 * @param node: the root of the subtree to search in
 * @param order: the 0-indexed order of the queried node
 * @param cmpf: a pointer to the key comparator function
 * @returns a pointer to the node the requested position in the subtree
 */
avl_node_t* avl_node_find_by_order(avl_node_t* node, int order, comparator_func cmpf){
    if(!node) return NULL;
    while(1){
        int pos = (node->left ? node->left->subtree_size : 0);
        //printf("%d %d\n", node->key, pos);
        if(pos == order)
            break;
        else if(pos < order){
            if(node->right == NULL) return NULL;
            node = node->right;
            order -= pos+1;
        }
        else{
            if(node->left == NULL) return NULL;
            node = node->left;
        }
    }
    return node;
}

/**
 * @param node: the node to be updated
 * @brief Update the values of the node
 */
void avl_node_update(avl_node_t* node){
    int leftHeight = (!node->left) ? -1 : node->left->height;
    int rightHeight = (!node->right) ? -1 : node->right->height;
    node->height = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
    node->balance_factor = rightHeight - leftHeight;
    int leftSize = (!node->left) ? 0 : node->left->subtree_size;
    int rightSize = (!node->right) ? 0 : node->right->subtree_size;
    node->subtree_size = 1 + leftSize + rightSize;
}


/*          === ROTATIONS ===

     y                                 x
    / \      Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3
*/

/**
 * @param node: the node that pivots the rotation
 * @brief Rotates the tree clockwise
 */
avl_node_t* avl_node_right_rotation(avl_node_t* node){
    avl_node_t* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    avl_node_update(node);
    avl_node_update(tmp);
    return tmp;
}

/**
 * @param node: the node that pivots the rotation
 * @brief Rotates the tree clockwise
 */
avl_node_t* avl_node_left_rotation(avl_node_t* node){
    avl_node_t* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    avl_node_update(node);
    avl_node_update(tmp);
    return tmp;
}
/*
                == LEFT-LEFT BALANCE ==
         z                                      y
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2

*/
avl_node_t* avl_node_left_left_balance(avl_node_t* node){
    return avl_node_right_rotation(node);
}

/*
                          == LEFT-RIGHT BALANCE ==
     z                               z                           x
    / \                            /   \                        /  \
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2

*/
avl_node_t* avl_node_left_right_balance(avl_node_t* node){
    node->left = avl_node_left_rotation(node->left);
    return avl_node_left_left_balance(node);
}

/*
  z                                y
 /  \                            /   \
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4

*/
avl_node_t* avl_node_right_right_balance(avl_node_t* node){
    return avl_node_left_rotation(node);
}

/*
   z                            z                            x
  / \                          / \                          /  \
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4

*/
avl_node_t* avl_node_right_left_balance(avl_node_t* node){
    node->right = avl_node_right_rotation(node->right);
    return avl_node_right_right_balance(node);
}


/**
 * @param node: the root of the subtree to be balanced
 * @returns the new root of the balanced subtree
 * @brief Balances a subtree to make sure that for each node its left and right subtrees heights differ by at most 1.
 */
avl_node_t* avl_node_balance(avl_node_t* node){
    if(node->balance_factor == -2){
        if(node->left->balance_factor <= 0)
            return avl_node_left_left_balance(node);
        else
            return avl_node_left_right_balance(node);
    }
    else if(node->balance_factor == +2){
        if(node->right->balance_factor >= 0)
            return avl_node_right_right_balance(node);
        else
            return avl_node_right_left_balance(node);
    }
    return node;
}


/**
 * @param node: the root of the subtree to be balanced
 * @param key: the key for the node to be inserted
 * @param val: the value for the node to be inserted
 * @param cmpf: a pointer to the key comparator function
 * @returns the new root of the balanced subtree
 * @brief Balances a subtree to make sure that for each node its left and right subtrees heights differ by at most 1.
 */
avl_node_t* avl_node_insert(avl_node_t* node, void* key, void* val, comparator_func cmpf){
    if(!node) return avl_node_init(key, val);

    int cmp = cmpf(key, node->key);
    if(cmp < 0)
        node->left = avl_node_insert(node->left, key, val, cmpf);
    else
        node->right = avl_node_insert(node->right, key, val, cmpf);

    avl_node_update(node);

    return avl_node_balance(node);
}

/**
 * @param node: the root of the subtree to be searched
 * @returns the node with the smallest key in the subtree
 */
avl_node_t* avl_node_get_first(avl_node_t* node){
    while(node->left) node = node->left;
    return node;
}

/**
 * @param node: the root of the subtree to be searched
 * @returns the node with the smallest key in the subtree
 */
avl_node_t* avl_node_get_last(avl_node_t* node){
    while(node->right) node = node->right;
    return node;
}



/**
 * @param node: the root of the subtree to be searched
 * @param key: the key to be searched for removal
 * @param cmpf: a pointer to the key comparator function
 * @return the root of the updated subtree
*/
avl_node_t* avl_node_remove(avl_node_t* node, void* key, comparator_func cmpf, deleter_func del_key, deleter_func del_val){
    if(!node) return NULL;
    int cmp = cmpf(key, node->key);
    if(cmp < 0){ //recur left
        node->left = avl_node_remove(node->left, key, cmpf, del_key, del_val);
    }
    else if(cmp > 0){ //recur right
        node->right= avl_node_remove(node->right, key, cmpf, del_key, del_val);
    }
    else{ // found
        if(del_key)
            del_key(node->key);
        if(del_val)
            del_val(node->val);


        if((node->left == NULL) || (node->right == NULL)){
            avl_node_t* tmp = node->left ? node->left : node->right;
            if(!tmp){ //leaf
                tmp = node;
                node = NULL;
            }
            else{
                *node = *tmp; //swap nodes
            }
            free(tmp); // remove the node
        }
        else{
            if(node->left->height > node->right->height){
                avl_node_t* tmp = avl_node_get_last(node->left);
                node->key = tmp->key;
                node->val = tmp->val;
                node->left = avl_node_remove(node->left, tmp->key, cmpf, NULL, NULL); //already freed key and val
            }
            else{
                avl_node_t* tmp = avl_node_get_first(node->right);
                node->key = tmp->key;
                node->val = tmp->val;
                node->right = avl_node_remove(node->right, tmp->key, cmpf, NULL, NULL); //already freed key and val
            }
        }
    }

    if(!node) return NULL;

    avl_node_update(node);
    return avl_node_balance(node);
}


/**
 * @param node: the root of the subtree to be traversed
 * @brief Prints the preorder traversal of the subtree
void avl_node_preorder(avl_node_t* node){
    if(node){
        printf("%d ", (node->key) );
        avl_node_preorder(node->left);
        avl_node_preorder(node->right);
    }
}
*/
