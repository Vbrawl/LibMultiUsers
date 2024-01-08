cmake_minimum_required(VERSION 3.20)

set(CMAKE_BUILD_TYPE Debug)

project(multiusers VERSION 1.0.0 DESCRIPTION "lubmultiusers provides a common interface for managing OS-level users under different operating systems")


add_library(${PROJECT_NAME} SHARED src/multiusers.c)
target_include_directories(${PROJECT_NAME} PRIVATE include)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/multiusers.h)


include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
