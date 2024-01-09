#include <multiusers.h>
#include <stdio.h>
#include <string.h>
#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#endif
// NEEDS: TEST_FOR_USER


int main() {
	char passwd[] = "FakePasswordThatWillFail";
	authenticate_user(TEST_FOR_USER, passwd) == -1;
	return 0;
}
