#ifndef MULTIUSERS_H
#define MULTIUSERS_H

#ifdef __linux__
#include <sys/types.h>
#endif

typedef struct user_data {
	const char* username;
	const char* home_path;
	uid_t user_id;
	gid_t group_id;
} user_data_t;





int get_user_data(const char* username, user_data_t **ud);
int get_user_data_safe(const char* username, size_t len, user_data_t **ud);
void clear_user_data(user_data_t *ud);
int user_exists(const char* username); // Success = 0, Failure = Anything else (commonly -1)
int user_exists_safe(const char* username, size_t len); // Same as non-safe version

#endif
