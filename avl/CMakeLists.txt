#Library name
project(avl)

#Create a shared library
add_library(avl SHARED
    src/pp_avl_node.c
    src/pp_avl_tree.c
    )

target_include_directories( avl
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
