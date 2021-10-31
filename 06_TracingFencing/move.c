#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define FAIL(code, ...) {fprintf(stderr, ##__VA_ARGS__); return code;}
#define BUFFER_SIZE 1024

enum {
	OK = 0,
	ARGS_ERROR = 255
} ExitCode;


int cleanup(FILE *infile, FILE *outfile, const char *to_delete) {
	if (infile != NULL) {
		fclose(infile);
		if (outfile != NULL) {
			fclose(outfile);
			if (unlink(to_delete) != 0)
				return errno;
		}
	}
	return 0;
}


int main(int argc, char *argv[]) {
	if (argc != 3)
		FAIL(ARGS_ERROR, "Missing arguments\nUsage: %s infile outfile\n", argv[0]);
	
	FILE *infile;
	FILE *outfile;
	char buffer[BUFFER_SIZE];
	size_t n_read, n_write;
	int err;
	
	if ((infile = fopen(argv[1], "r")) == NULL)
		FAIL(errno, "Can't open '%s' to read: %s\n", argv[1], strerror(errno));
	if ((outfile = fopen(argv[2], "w")) == NULL) {
		err = errno;
		cleanup(infile, outfile, argv[2]);
		FAIL(err, "Can't open '%s' to write: %s\n", argv[2], strerror(err));
	}
	int out_fd = fileno(outfile);  // fwrite don't raise any errors :(

	while ((n_read = fread(buffer, 1, BUFFER_SIZE, infile)) > 0)
		if ((n_write = write(out_fd, buffer, n_read)) != n_read) {
			err = errno;
			cleanup(infile, outfile, argv[2]);
			FAIL(err, "Write error: %s\n", strerror(err));
		}

	if (ferror(infile)) {
		err = errno;
		cleanup(infile, outfile, argv[2]);
		FAIL(err, "Read error: %s\n", strerror(err));
	}

	if ((err = cleanup(infile, outfile, argv[1])) != 0)
		FAIL(err, "Can't delete file:\n", strerror(err));

	return OK;
}
