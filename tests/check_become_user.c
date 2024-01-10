#include <multiusers.h>
// NEEDS: TEST_FOR_USER



int main() {
    user_data_t *ud;

    if(get_user_data(TEST_FOR_USER, &ud)) { return -1; }
    become_user(ud);
    clear_user_data(ud);
    return 0;
}