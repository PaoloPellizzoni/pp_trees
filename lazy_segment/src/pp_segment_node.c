#include "lazy_segment/pp_segment_node.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @param array: A pointer to an integer array
 * @param l: The left bound for the range updates and queries
 * @param r: The right bound (excluded) for the range updates and queries
 * @brief Creates in O(n) a segment tree based on the given array.
 * @returns a pointer to the newly allocated root of the tree.
 */
segment_node_t* segment_node_init(int* array, int l, int r){
    segment_node_t* node = calloc(1, sizeof(segment_node_t));
    if(!node){
        fprintf(stderr, "Failed allocation\n");
        return NULL;
    }
    node->val = 0;      // this stores the range sum
    node->lazy = 0;     // this stores the lazy updates
    node->low = l;      // this saves the left bound
    node->high = r;     // this saves the right bound
    if(l == r-1){       // is a leaf node
        node->left = NULL;
        node->right = NULL;
        node->val = array[l];
    }
    else{
        int mid = l + (r - l)/2;    //bisect the range and recur
        node->left = segment_node_init(array, l, mid);
        node->right = segment_node_init(array, mid, r);
        if(node->left == NULL || node->right == NULL)   // failed allocation
        {
            segment_node_free(node);                    // free this subtree and tell parent
            return NULL;
        }

        node->val = node->left->val + node->right->val;
    }
    return node;
}

/**
 * @param node: A pointer to the root of the tree to be freed
 * @brief Frees in O(n) the segment tree.
 */
void segment_node_free(segment_node_t* node){
    if(node->left)
        segment_node_free(node->left);
    if(node->right)
        segment_node_free(node->right);
    free(node);
}

/**
 * @param node: A pointer to the root of the subtree to be updated
 * @param l: The left bound for the range update
 * @param r: The right bound (excluded) for the range update
 * @param upd: The quantity to add to the whole range
 * @brief Updates in log(n) a range making use of lazy updates.
 */
void segment_node_update(segment_node_t* node, int l, int r, int upd){
    segment_node_propagate(node);                   // before updating this node propagate down its stored updates

    if(l <= node->low && r >= node->high){          // update range partially overlaps with node range
        node->val += upd*(node->high - node->low);  // add upd to all the nodes of the range
        if(node->left) node->left->lazy += upd;     // propagate the update lazily to its children
        if(node->right) node->right->lazy += upd;
    }
    else if(l >= node->high || r <= node->low){     // update range does not overlap with node range
        //do nothing
    }
    else{                                            // update range is included in node range
        if(node->left) segment_node_update(node->left, l, r, upd);                              // recur down...
        if(node->right) segment_node_update(node->right, l, r, upd);
        node->val = (node->left ? node->left->val : 0) + (node->right ? node->right->val : 0);  // ...and merge results
    }
}

/**
 * @param node: A pointer to the node to propagate
 * @brief Propagates down the tree the lazy updates.
 */
void segment_node_propagate(segment_node_t* node){
    if(node->lazy){
        node->val += node->lazy * (node->high - node->low); // do the posponed update to the node
        if(node->left) node->left->lazy += node->lazy;      // and propagate down the tree the value of the update...
        if(node->right) node->right->lazy += node->lazy;    // ...so the children qill be updated next time (thus lazily)
        node->lazy = 0;                                     // and reset this node's lazy update value
    }
}

/**
 * @param node: A pointer to the root of the subtree to be queried
 * @param l: The left bound for the range query
 * @param r: The right bound (excluded) for the range query
 * @brief Returns in log(n) the sum in the given range.
 * @returns an integer, the sum in the given range.
 */
int segment_node_sum(segment_node_t* node, int l, int r){
    segment_node_propagate(node);                    // before quering this node propagate down its stored updates
    if(l <= node->low && r >= node->high){      // update range partially overlaps with node range
        return node->val;   // just return the sum of this node's range
    }
    else if(l >= node->high || r <= node->low){ // update range does not overlap with node range
        return 0;           // outside of range so the sum is 0
    }
    else{                                       // update range is included in node range
        return (node->left ? segment_node_sum(node->left, l, r) : 0) + (node->right ? segment_node_sum(node->right, l, r) : 0); //recur
    }
}
