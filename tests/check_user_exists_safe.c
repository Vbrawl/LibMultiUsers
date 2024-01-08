#include <multiusers.h>

// TEST_FOR_USER is defined
#include <string.h>

int main() {
	int rc = user_exists_safe(TEST_FOR_USER, strlen(TEST_FOR_USER));
	return rc;
}
