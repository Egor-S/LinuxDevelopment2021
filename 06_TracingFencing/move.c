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


int main(int argc, char *argv[]) {
	if (argc != 3)
		FAIL(ARGS_ERROR, "Missing arguments\nUsage: %s infile outfile\n", argv[0]);
	
	FILE *infile;
	FILE *outfile;
	char buffer[BUFFER_SIZE];
	size_t n_read, n_write;
	
	if ((infile = fopen(argv[1], "r")) == NULL)
		FAIL(errno, "Can't open '%s' to read: %s\n", argv[1], strerror(errno));
	if ((outfile = fopen(argv[2], "w")) == NULL)
		FAIL(errno, "Can't open '%s' to write: %s\n", argv[2], strerror(errno));  // todo close infile

	while ((n_read = fread(buffer, 1, BUFFER_SIZE, infile)) > 0)
		if ((n_write = fwrite(buffer, 1, n_read, outfile)) != n_read)
			FAIL(errno, "Write error: %s\n", strerror(errno));

	if (ferror(infile))
		FAIL(errno, "Read error: %s\n", strerror(errno));

	fclose(infile);
	fclose(outfile);
	unlink(argv[1]);

	return OK;
}
