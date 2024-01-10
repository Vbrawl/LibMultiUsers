#ifndef MULTIUSERS_H
#define MULTIUSERS_H

#ifdef __linux__
#include <sys/types.h>
#endif

struct group_data {
	gid_t *groups;
	int size;
};

typedef struct user_data {
	const char* username;
	const char* home_path;
	uid_t user_id;
	gid_t group_id;
	struct group_data supplementary_groups;
} user_data_t;




/* Get user_data */
int get_current_user_data(user_data_t **ud);
int get_user_data(const char* username, user_data_t **ud);
int get_user_data_safe(const char* username, size_t len, user_data_t **ud);
void clear_user_data(user_data_t *ud);

/* Check if user exists without getting it's data */
int user_exists(const char* username); // Success = 0, Failure = Anything else (commonly -1)
int user_exists_safe(const char* username, size_t len); // Same as non-safe version

/* Advanced actions */
int authenticate_user(user_data_t *user, const char* passwd);
int become_user(user_data_t *user);

#endif
