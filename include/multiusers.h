#ifndef MULTIUSERS_H
#define MULTIUSERS_H

#ifdef __linux__
#include <sys/types.h>
#endif

struct user_password {
	const char* password;
	const char* salt;
	const char* algorithm;
};

typedef struct user_data {
	const char* username;
	const struct user_password password;
	const char* home_path;
	const uid_t user_id;
	const gid_t group_id;
} user_data_t;





int get_user_data(const char* username, user_data_t **ud);
int getn_user_data(const char* username, size_t len, user_data_t **ud);
void clear_user_data(user_data_t *ud);


#endif
