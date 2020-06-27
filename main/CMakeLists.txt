#Library name
project(main)


#Create an executable
add_executable(main
    src/main.c
    src/utils.c
    src/tests.c
)

target_include_directories( main
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(main LINK_PUBLIC
    avl
    lazy_segment
)
