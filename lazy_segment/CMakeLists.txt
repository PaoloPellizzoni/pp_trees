#Library name
project(lazy_segment)

#Create a shared library
add_library(lazy_segment SHARED
    src/pp_segment_node.c
    )

target_include_directories( lazy_segment
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
