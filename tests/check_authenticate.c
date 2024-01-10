#include <multiusers.h>
#include <stdio.h>
#include <string.h>
#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#endif
// NEEDS: TEST_FOR_USER


int main() {
	static const char passwd[] = "FakePasswordThatWillFail";
	user_data_t *ud;
	if(get_user_data(TEST_FOR_USER, &ud) != 0) { return -1; }
	authenticate_user(ud, passwd);
	clear_user_data(ud);
	return 0;
}
