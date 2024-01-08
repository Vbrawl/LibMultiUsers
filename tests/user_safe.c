#include <multiusers.h>

// for this test to work you need to provide a username at the compilation time.
// use -DTEST_FOR_USER=$(whoami)
#ifndef TEST_FOR_USER
#error "Provide a user using the option -DTEST_FOR_USER. eg.[bash] -DTEST_FOR_USER=$(whoami)"
#endif

#include <string.h>

int main() {
	int rc = 0;
	user_data_t *ud;

	rc |= get_user_data_safe(TEST_FOR_USER, strlen(TEST_FOR_USER), &ud);

	if(rc == 0) {
		if(strncmp(TEST_FOR_USER, ud->username, strlen(TEST_FOR_USER)) != 0) {
			rc |= -1;
		}

		clear_user_data(ud);
	}
	return rc;
}
