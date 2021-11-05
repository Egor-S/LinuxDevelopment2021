#include <stdio.h>
// #include <rhash.h>


#define MAX_LINE_SIZE 1024


int main(int argc, char *argv[]) {
	char line[MAX_LINE_SIZE];
	while (fgets(line, MAX_LINE_SIZE, stdin)) {
		printf("hi\n");
	}
	return 0;
}
