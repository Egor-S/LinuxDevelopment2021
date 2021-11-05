#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <config.h>
#include <rhash.h>

#ifdef HAVE_LIBREADLINE
#include <readline/readline.h>
#include <readline/history.h>

char *free_readline(char *line) {
	if (line)
		free(line);
	return readline(NULL);
}
#endif 


int strcmpi(char const *a, char const *b) {
	/* source: https://stackoverflow.com/questions/5820810 */
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}


enum rhash_ids get_hash_id(char const *hash_name) {
	if (strcmpi(hash_name, "TTH") == 0)  return RHASH_TTH;
	if (strcmpi(hash_name, "SHA1") == 0) return RHASH_SHA1;
	if (strcmpi(hash_name, "MD5") == 0)  return RHASH_MD5;
	return 0;
}


int main(int argc, char *argv[]) {
	char *line = NULL;
	
	char digest[64];
    char output[130];
    rhash_library_init();

    #ifndef HAVE_LIBREADLINE
	size_t len = 0;
	ssize_t n_read;
	while ((n_read = getline(&line, &len, stdin)) != -1) {
		line[n_read - 1] = '\0';  // trim \n
	#else
	while ((line = free_readline(line))) {
		if (*line)
			add_history(line);
	#endif
		char *hash_name;
		char *payload;
		if ((hash_name = strtok(line, " ")) == NULL || (payload = strtok(NULL, " ")) == NULL) {
			fprintf(stderr, "Not enough arguments. Usage: <hash> <\"string|file>\n");
			continue;
		}
		if (strtok(NULL, " ") != NULL) {
			fprintf(stderr, "Too many arguments. Usage: <hash> <\"string|file>\n");
			continue;
		}
		int hash_id = get_hash_id(hash_name);
		if (!hash_id) {
			fprintf(stderr, "Unknown hash name: %s\n", hash_name);
			continue;
		}
		unsigned char c = hash_name[0];
		int format = (c == tolower(c)) ? RHPR_BASE64 : RHPR_HEX;

		if (payload[0] == '"') {
			payload++;  // trim quote
			int res = rhash_msg(hash_id, payload, strlen(payload), digest);
			if (res < 0) {
				fprintf(stderr, "message digest calculation error\n");
				continue;
			}
		} else {
			int res = rhash_file(hash_id, payload, digest);
			if(res < 0) {
				fprintf(stderr, "LibRHash error: %s: %s\n", payload, strerror(errno));
				continue;
			}
		}
		rhash_print_bytes(output, digest, rhash_get_digest_size(hash_id), (format | RHPR_UPPERCASE));
		printf("%s\n", output);
	}
	
	if (line)
		free(line);
	return 0;
}
