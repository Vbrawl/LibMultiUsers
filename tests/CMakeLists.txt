macro(make_test test_name) # Add extra arguments to specify the source files
	add_executable(${test_name} ${ARGN})
	target_link_libraries(${test_name} ${PROJECT_NAME})
	target_include_directories(${test_name} PRIVATE ../include)

	if(MSVC)
	else()
		target_compile_options(${test_name} PRIVATE -DTEST_FOR_USER="$ENV{USER}")
	endif()

	add_test(NAME ${test_name} COMMAND ${test_name})
endmacro()

make_test(testUser user.c)
make_test(testUserSafe user_safe.c)
make_test(testUserExists check_user_exists.c)
make_test(testUserExistsSafe check_user_exists_safe.c)
make_test(testAuthenticate check_authenticate.c)
make_test(testCurrentUser check_current_user.c)
make_test(testBecomeUser check_become_user.c)