#include "multiusers.h"

#include <string.h>
#include <stdlib.h>

#ifdef __linux__
#include <pwd.h>
#include <unistd.h>
#include <grp.h>
#endif

#ifdef __linux__
int structpasswd_to_userdatat(struct passwd *udetails, user_data_t *udata) {
	int rc = 0;

	size_t namelen = strlen(udetails->pw_name) + 1;
	size_t homelen = strlen(udetails->pw_dir) + 1;

	udata->user_id = udetails->pw_uid;
	udata->group_id = udetails->pw_gid;

	udata->username = malloc(namelen);
	if(udata->username == NULL) { rc = -1; }
	else { strncpy((char*)udata->username, udetails->pw_name, namelen-1); }

	udata->home_path = malloc(homelen);
	if(udata->home_path == NULL) { rc = -1; }
	else { strncpy((char*)udata->home_path, udetails->pw_dir, homelen-1); }

	return rc;
}

int fill_userdatat_supplementary_groups(user_data_t *udata) {
	int rc = 0;

	udata->supplementary_groups.size = 1;
	udata->supplementary_groups.groups = malloc(sizeof(gid_t)); // Formula: sizeof(gid_t) * udata->supplementary_groups.size
	if(udata->supplementary_groups.groups == NULL) { rc = -1; }
	else if(getgrouplist(udata->username, udata->group_id, udata->supplementary_groups.groups, &udata->supplementary_groups.size) == -1) {
		void *tmp = realloc(udata->supplementary_groups.groups, sizeof(gid_t) * udata->supplementary_groups.size);
		if(tmp == NULL) {
			free(udata->supplementary_groups.groups);
			return -1;
		}
		udata->supplementary_groups.groups = tmp;
		getgrouplist(udata->username, udata->group_id, udata->supplementary_groups.groups, &udata->supplementary_groups.size);
	}

	return rc;
}
#endif

int get_current_user_data(user_data_t **ud) {
	int rc = 0;
	*ud = malloc(sizeof(user_data_t));
#if defined(__linux__)
	int uid = getuid();
	struct passwd udetails, *udetails_ptr;
	int buflen = sysconf(_SC_GETPW_R_SIZE_MAX);
	char* buffer = malloc(buflen);
	if(buffer == NULL) { rc = -1; }
	else {
		getpwuid_r(uid, &udetails, buffer, buflen, &udetails_ptr);
		if(udetails_ptr == NULL) { rc = -1; }
		else { rc = structpasswd_to_userdatat(udetails_ptr, *ud); }
		free(buffer);

		if(rc == 0) { rc = fill_userdatat_supplementary_groups(*ud); }
	}
#endif

	if(rc != 0) { clear_user_data(*ud); }
	return rc;
}

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
		else { structpasswd_to_userdatat(udetails_ptr, *ud); }
		free(buffer);

		if(rc == 0) { rc = fill_userdatat_supplementary_groups(*ud); }
	}
#endif
	if(rc != 0) { clear_user_data(*ud); }
	return rc;
}

void clear_user_data(user_data_t *ud) {
	if(ud->username != NULL) { free((char*)ud->username); }
	if(ud->home_path != NULL) { free((char*)ud->home_path); }
	if(ud->supplementary_groups.groups != NULL) { free(ud->supplementary_groups.groups); }
	free(ud);
}


int user_exists(const char* username) {
	user_data_t *ud;
	int rc = get_user_data(username, &ud);
	if(rc == 0) { clear_user_data(ud); }
	return rc;
}
