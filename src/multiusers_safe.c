#include "multiusers.h"
#include <stdlib.h>
#include <string.h>


#define _SAFE_BUFFER(buf, len, customCode) char* safe_buffer = malloc(len+1); \
				if(safe_buffer == NULL) { return -1; } \
				else { strncpy(safe_buffer, buf, len); }; \
				customCode \
				free(safe_buffer)




int get_user_data_safe(const char* username, size_t len, user_data_t **ud) {
	int rc = 0;
	_SAFE_BUFFER( username, len, rc = get_user_data(safe_buffer, ud); );
	return rc;
}




int user_exists_safe(const char* username, size_t len) {
	int rc = 0;
	_SAFE_BUFFER( username, len, rc = user_exists(safe_buffer); );
	return rc;
}
