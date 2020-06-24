#Library name
project(main)

#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#Create an executable
add_executable(main
    src/main.c
    src/utils.c
)

target_include_directories( main
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(main LINK_PUBLIC
    avl
)
