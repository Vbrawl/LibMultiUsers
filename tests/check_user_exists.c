#include <multiusers.h>

// TEST_FOR_USER is defined

int main() {
	int rc = user_exists(TEST_FOR_USER);
	return rc;
}
