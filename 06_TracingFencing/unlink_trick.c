#define _GNU_SOURCE
#include <libgen.h>
#include <string.h>
#include <errno.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef int (*orig_unlink_f_type)(const char *pathname);

int unlink(const char *pathname) {
	char *copy_pathname = strdup(pathname);
	char *filename = basename(copy_pathname);
	if (strstr(filename, "PROTECT") != NULL) {
		free(copy_pathname);
		errno = 13;
		return -1;
	}

    free(copy_pathname);
	orig_unlink_f_type orig_unlink;
    orig_unlink = (orig_unlink_f_type)dlsym(RTLD_NEXT, "unlink");
    return orig_unlink(pathname);
}
