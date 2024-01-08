#include "multiusers.h"

#include <string.h>
#include <stdlib.h>

#ifdef __linux__
#include <pwd.h>
#include <unistd.h>
#endif


int get_user_data(const char* username, user_data_t **ud) {
	int rc = 0;
	*ud = malloc(sizeof(user_data_t));

#if defined(__linux__)
	struct passwd udetails, *udetails_ptr;
	int buflen = sysconf(_SC_GETPW_R_SIZE_MAX);
	char* buffer = malloc(buflen);
	if(buffer == NULL) { rc = -1; }
	else {
		getpwnam_r(username, &udetails, buffer, buflen, &udetails_ptr);
		if(udetails_ptr == NULL) { rc = -1; }
		else {
			(*ud)->user_id = udetails.pw_uid;
			(*ud)->group_id = udetails.pw_gid;

			size_t namelen = strlen(udetails.pw_name)+1;
			size_t homelen = strlen(udetails.pw_dir)+1;

			(*ud)->username = malloc(namelen);
			if((*ud)->username == NULL) { rc = -1; }
			else { strncpy((char*)(*ud)->username, udetails.pw_name, namelen-1); }

			(*ud)->home_path = malloc(homelen);
			if((*ud)->home_path == NULL) { rc = -1; }
			else { strncpy((char*)(*ud)->home_path, udetails.pw_dir, homelen-1); }
		}
		free(buffer);
	}
#else
#error "OS not supported"
#endif
	if(rc != 0) { clear_user_data(*ud); }
	return rc;
}

void clear_user_data(user_data_t *ud) {
	if(ud->username != NULL) { free((char*)ud->username); }
	if(ud->home_path != NULL) { free((char*)ud->home_path); }
	free(ud);
}


int user_exists(const char* username) {
	user_data_t *ud;
	int rc = get_user_data(username, &ud);
	if(rc == 0) { clear_user_data(ud); }
	return rc;
}
