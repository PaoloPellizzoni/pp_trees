#ifndef PP_SEGMENT_NODE_H_
#define PP_SEGMENT_NODE_H_

struct segment_node{
    struct segment_node* left;
    struct segment_node* right;
    int low, high;
    int val, lazy;
} typedef segment_node_t;

segment_node_t* segment_node_init(int* array, int l, int r);
void segment_node_free(segment_node_t* node);
void segment_node_update(segment_node_t* node, int l, int r, int upd);
void segment_node_propagate(segment_node_t* node);
int segment_node_sum(segment_node_t* node, int l, int r);

#endif
