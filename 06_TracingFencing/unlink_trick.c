#define _GNU_SOURCE
#include <libgen.h>
#include <string.h>
#include <errno.h>
#include <dlfcn.h>
#include <stdio.h>

typedef int (*orig_unlink_f_type)(const char *pathname);

int unlink(const char *pathname) {
	char *filename = basename(pathname);
	printf("%s\n", filename);
	if (strstr(filename, "PROTECT") != NULL) {
		errno = 13;
		return -1;
	}

	orig_unlink_f_type orig_unlink;
    orig_unlink = (orig_unlink_f_type)dlsym(RTLD_NEXT, "unlink");
    return orig_unlink(pathname);
}
