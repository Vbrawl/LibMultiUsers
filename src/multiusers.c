#include "multiusers.h"

#include <string.h>
#include <stdlib.h>

#ifdef __linux__
#include <pwd.h>
#include <unistd.h>
#endif

int getn_user_data(const char* username, size_t len, user_data_t **ud) {
	int rc;
	char* safe_username = malloc(len+1);
	if(safe_username == NULL) {
		return -1;
	}
	else {
		strncpy(safe_username, username, len);
		safe_username[len] = '\0';
	}
	rc = get_user_data(safe_username, ud);
	free(safe_username);
	return rc;
}


int get_user_data(const char* username, user_data_t **ud) {
	int rc = 0;
	char *rusername = NULL, *home_path = NULL;
	char *pw_password = NULL, *pw_salt = NULL, *pw_algorithm = NULL;
	uid_t user_id = 0;
	gid_t group_id = 0;
#if defined(__linux__)
	struct passwd udetails, *udetails_ptr;
	int buflen = sysconf(_SC_GETPW_R_SIZE_MAX);
	char* buffer = malloc(buflen);
	if(buffer == NULL) { rc = -1; }
	else {
		getpwnam_r(username, &udetails, buffer, buflen, &udetails_ptr);
		if(udetails_ptr == NULL) { rc = -1; }
		else {
			user_id = udetails.pw_uid;
			group_id = udetails.pw_gid;

			size_t namelen = strlen(udetails.pw_name)+1;
			size_t passwdlen = strlen(udetails.pw_passwd)+1;
			#pragma message ( "TODO: Better password parsing!" )
			size_t homelen = strlen(udetails.pw_dir)+1;

			rusername = malloc(namelen);
			if(rusername == NULL) { rc = -1; }
			else { strncpy(rusername, udetails.pw_name, namelen); }

			pw_password = malloc(passwdlen+1);
			if(pw_password == NULL) { rc = -1; }
			else { strncpy(pw_password, udetails.pw_passwd, passwdlen); }

			home_path = malloc(homelen+1);
			if(home_path == NULL) { rc = -1; }
			else { strncpy(home_path, udetails.pw_dir, homelen); }
		}
		free(buffer);
	}
#else
#error "OS not supported"
#endif
	if(rc == 0) {
		user_data_t nud = {
			.username = rusername,
			.password = {
				.password = pw_password,
				.salt = pw_salt,
				.algorithm = pw_algorithm
			},
			.home_path = home_path,
			.user_id = user_id,
			.group_id = group_id
		};
		*ud = malloc(sizeof(user_data_t));
		memcpy(*ud, &nud, sizeof(user_data_t));
	}
	else {
		if(rusername != NULL) { free(rusername); }
		if(pw_password != NULL) { free(pw_password); }
		if(pw_salt != NULL) { free(pw_salt); }
		if(pw_algorithm != NULL) { free(pw_algorithm); }
		if(home_path != NULL) { free(home_path); }
	}
	return rc;
}



void clear_user_data(user_data_t *ud) {
	if(ud->username != NULL) { free((char*)ud->username); }
	if(ud->password.password != NULL) { free((char*)ud->password.password); }
	if(ud->password.salt != NULL) { free((char*)ud->password.salt); }
	if(ud->password.algorithm != NULL) { free((char*)ud->password.algorithm); }
	if(ud->home_path != NULL) { free((char*)ud->home_path); }
	free(ud);
}
