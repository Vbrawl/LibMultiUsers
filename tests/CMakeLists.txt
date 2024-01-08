
add_executable(testUser user.c)
if(MSVC)
else()
	target_compile_options(testUser PRIVATE -DTEST_FOR_USER="$ENV{USER}")
endif()
target_link_libraries(testUser ${PROJECT_NAME})
add_test(NAME testUser COMMAND testUser)
