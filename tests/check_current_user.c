#include <multiusers.h>
#include <string.h>
// NEEDS: TEST_FOR_USER


int main() {
    int rc;
    user_data_t *ud;

    get_current_user_data(&ud);
    rc = !(strcmp(ud->username, TEST_FOR_USER) == 0);
    clear_user_data(ud);

    return rc;
}