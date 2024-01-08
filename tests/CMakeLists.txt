
add_executable(testUser user.c)
if(MSVC)
else()
	target_compile_options(testUser PRIVATE -DTEST_FOR_USER="$ENV{USER}")
endif()
target_link_libraries(testUser ${PROJECT_NAME})
target_include_directories(testUser PRIVATE ../include)
add_test(NAME testUser COMMAND testUser)



add_executable(testUserSafe user_safe.c)
if(MSVC)
else()
	target_compile_options(testUserSafe PRIVATE -DTEST_FOR_USER="$ENV{USER}")
endif()
target_link_libraries(testUserSafe ${PROJECT_NAME})
target_include_directories(testUserSafe PRIVATE ../include)
add_test(NAME testUserSafe COMMAND testUserSafe)



add_executable(testCheckUserExists check_user_exists.c)
if(MSVC)
else()
	target_compile_options(testCheckUserExists PRIVATE -DTEST_FOR_USER="$ENV{USER}")
endif()
target_link_libraries(testCheckUserExists ${PROJECT_NAME})
target_include_directories(testCheckUserExists PRIVATE ../include)
add_test(NAME testCheckUserExists COMMAND testCheckUserExists)


add_executable(testCheckUserExistsSafe check_user_exists_safe.c)
if(MSVC)
else()
	target_compile_options(testCheckUserExistsSafe PRIVATE -DTEST_FOR_USER="$ENV{USER}")
endif()
target_link_libraries(testCheckUserExistsSafe ${PROJECT_NAME})
target_include_directories(testCheckUserExistsSafe PRIVATE ../include)
add_test(NAME testCheckUserExistsSafe COMMAND testCheckUserExistsSafe)
