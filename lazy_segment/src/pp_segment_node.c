#include "lazy_segment/pp_segment_node.h"
#include <stdlib.h>

segment_node_t* segment_node_init(int* array, int l, int r){
    segment_node_t* node = calloc(1, sizeof(segment_node_t));
    if(!node) return NULL;
    node->val = 0;
    node->lazy = 0;
    node->low = l;
    node->high = r;
    if(l == r-1){
        node->left = NULL;
        node->right = NULL;
        node->val = array[l];
    }
    else{
        int mid = l + (r - l)/2;
        node->left = segment_node_init(array, l, mid);
        node->right = segment_node_init(array, mid, r);
        if(node->left == NULL || node->right == NULL)
            return NULL;

        node->val = node->left->val + node->right->val;
    }
    return node;
}

void segment_node_free(segment_node_t* node){
    if(node->left)
        segment_node_free(node->left);
    if(node->right)
        segment_node_free(node->right);
    free(node);
}

void segment_node_update(segment_node_t* node, int l, int r, int upd){
    segment_node_propagate(node);

    if(l <= node->low && r >= node->high){
        node->val = upd*(node->high - node->low); //change to += to add to range 
        if(node->left) node->left->lazy += upd;
        if(node->right) node->right->lazy += upd;
    }
    else if(l >= node->high || r <= node->low){
        //do nothing
    }
    else{
        if(node->left) segment_node_update(node->left, l, r, upd);
        if(node->right) segment_node_update(node->right, l, r, upd);
        node->val = (node->left ? node->left->val : 0) + (node->right ? node->right->val : 0);
    }
}

void segment_node_propagate(segment_node_t* node){
    if(node->lazy){
        node->val += node->lazy * (node->high - node->low);
        if(node->left) node->left->lazy += node->lazy;
        if(node->right) node->right->lazy += node->lazy;
        node->lazy = 0;
    }
}

int segment_node_sum(segment_node_t* node, int l, int r){
    segment_node_propagate(node);
    if(l <= node->low && r >= node->high){
        return node->val;
    }
    else if(l >= node->high || r <= node->low){
        return 0;
    }
    else{
        return (node->left ? segment_node_sum(node->left, l, r) : 0) + (node->right ? segment_node_sum(node->right, l, r) : 0);
    }
}
