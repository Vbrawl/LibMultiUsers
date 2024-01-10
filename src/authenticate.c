#include "multiusers.h"
#include <security/pam_appl.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <grp.h>
#include <unistd.h>
#endif

#ifndef PAM_SERVICE_STRING
#define PAM_SERVICE_STRING "system-remote-login"
#endif


#ifdef __linux__
// PRIVATE FUNCTION (appdata_ptr => password [DO NOT OVERWRITE])
int authenticate_user_conv(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata_ptr) {
	struct pam_response *pamr;
	size_t passlen = strlen((char*)appdata_ptr);

	// Allocate storage
	pamr = malloc(sizeof(struct pam_response));
	if(pamr == NULL) { return -1; }
	pamr->resp = malloc(passlen+1);
	if(pamr->resp == NULL) {
		free(pamr);
		return 0;
	}

	// Copy values to struct
	strncpy(pamr->resp, appdata_ptr, passlen);
	pamr->resp[passlen] = '\0';
	pamr->resp_retcode = 0;

	// Send message and return
	*resp = pamr;
	return 0;
}
#endif


int authenticate_user(user_data_t *user, const char* password) {
	int rc = 0;
#ifdef __linux__
	pam_handle_t *pamh;
	struct pam_conv pamc;

	// Setup PAM conversation
	pamc.conv = authenticate_user_conv;
	pamc.appdata_ptr = (char*)password;

	// Perform the authentication
	rc = pam_start(PAM_SERVICE_STRING, user->username, &pamc, &pamh);
	if(rc == PAM_SUCCESS) {
		rc = pam_authenticate(pamh, 0);
		pam_end(pamh, rc);
	}

	// Make sense of return code
	if(rc == PAM_SUCCESS) { rc = 0; }
	else { rc = -1; }
#endif
	return rc;
}


int become_user(user_data_t *user) {
	int rc = 0;
#ifdef __linux__
	user_data_t *current;
	if(get_current_user_data(&current) != 0) { return -1; }

	if(setgroups(user->supplementary_groups.size, user->supplementary_groups.groups) == -1) { rc = -2; }
	else {
		if(setgid(user->group_id) == -1) { rc = -3; }
		else if(setuid(user->user_id) == -1) { rc = -4; }

		if(rc != 0) {
			setgroups(current->supplementary_groups.size, current->supplementary_groups.groups);
			setgid(current->group_id);
		}
	}

	clear_user_data(current);
#endif
	return rc;
}
