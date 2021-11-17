#include <stdio.h>
#include <regex.h>
#include "subparser.h"

#define ERRBUF_SIZE 1024
#define MAX_MATCHES 9

void print_regex_error(char const *prefix, int err, regex_t *regex_p) {
	char errbuf[ERRBUF_SIZE];
	regerror(err, regex_p, errbuf, ERRBUF_SIZE);
	fprintf(stderr, "%s error %d: %s\n", prefix, err, errbuf);
}

int main (int argc, char *argv[]) {
	regex_t regex;
	regmatch_t pmatches[1 + MAX_MATCHES];
	sub_array sa;

	if (argc != 4) {
		fprintf(stderr, "usage: %s <regexp> <substitution> <string>\n", argv[0]);
		return 1;
	}

	char const *re = argv[1];
	char const *sub = argv[2];
	char const *str = argv[3];
	
	int err;
	if ((err = regcomp(&regex, re, REG_NEWLINE | REG_EXTENDED))) {
		print_regex_error("regcomp", err, &regex);
		return err;
	}

	sa_init(&sa);
	sub_parse(&sa, sub);
	int maxgroup = -1;
	for (int i = 0; i < sa.length; i++)
		if (sa.tokens[i].group > maxgroup)
			maxgroup = sa.tokens[i].group;

	char const *s = str;
	for (int i = 0; ; i++) {
		if ((err = regexec(&regex, s, 1 + MAX_MATCHES, pmatches, 0))) {
			if (err == 1) {
				printf("%s\n", s);
				break;
			} else {
				print_regex_error("regexec", err, &regex);
				sa_free(&sa);
				return err;
			}
		}
		int n_matches = 0;
		while (n_matches < MAX_MATCHES && pmatches[1 + n_matches].rm_so != -1)
			n_matches++;

		if (maxgroup > n_matches) {
			fprintf(stderr, "sub error: \\%d requested, but there is only %d groups\n", maxgroup, n_matches);
			sa_free(&sa);
			return err;
		}

		printf("%.*s", (int)pmatches[0].rm_so, s);
		for (int j = 0; j < sa.length; j++) {
			if (sa.tokens[j].group > 0) {
				regmatch_t g = pmatches[sa.tokens[j].group];
				printf("%.*s", (int)(g.rm_eo - g.rm_so), s + g.rm_so);
			} else {
				printf("%.*s", sa.tokens[j].length, sub + sa.tokens[j].offset);
			}
		}
		s += pmatches[0].rm_eo;
		int remaining = 0;
		while (s[remaining] != '\0') {
			remaining++;
			if (s[remaining - 1] == '\n')
				break;
		}
		printf("%.*s", remaining, s);
		s += remaining;
	}

	sa_free(&sa);
	return 0;
}
