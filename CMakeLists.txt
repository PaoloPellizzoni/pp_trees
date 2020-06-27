cmake_minimum_required(VERSION 3.0)

#set custom install path
message(STATUS "Setting default CMAKE_INSTALL_PREFIX path to ${CMAKE_BINARY_DIR}/install")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/../install" CACHE STRING "The path to use for make install" FORCE)

# Project name
project(pp_trees)

#add libavl directory
add_subdirectory(avl)

#add libsegment directory
add_subdirectory(lazy_segment)

#add main directory
add_subdirectory(main)


#install
install (TARGETS main
	DESTINATION bin
)

install (TARGETS avl
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

install (TARGETS lazy_segment
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

install (DIRECTORY data
	DESTINATION .)
