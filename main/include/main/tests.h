#ifndef PP_TESTS_H_
#define PP_TESTS_H_

#include "avl/pp_avl_tree.h"
#include "lazy_segment/pp_segment_node.h"

#define DATA_DIR "../data/"

int test_avl_babel();
int test_avl_strings_removeall();
int test_avl_random();
int test_avl_order_statistics();

int test_segment_basic();
int test_segment_potentiometer();

#endif
