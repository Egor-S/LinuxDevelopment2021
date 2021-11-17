#include <stdlib.h>
#include <ctype.h>

typedef struct {
	int group;
	int offset;
	int length;
} sub_token;

typedef struct {
	sub_token *tokens;
	int length;
	int capacity;
} sub_array;

void sa_init(sub_array *a) {
	a->length = 0;
	a->capacity = 2;
	a->tokens = malloc(a->capacity * sizeof(sub_token));
}

void sa_extend(sub_array *a) {
	a->capacity *= 2;
	a->tokens = realloc(a->tokens, a->capacity * sizeof(sub_token));
}

void sa_append(sub_array *a, sub_token token) {
	if (a->length >= a->capacity)
		sa_extend(a);
	a->tokens[a->length] = token;
	a->length++;
}

void sa_free(sub_array *a) {
	free(a->tokens);
	a->tokens = NULL;
	a->capacity = -1;
}

void sub_parse(sub_array *a, char const *sub) {
	int escaped = 0;
	sub_token token = {0};

	for (int pos = 0; ; pos++) {
		char c = sub[pos];
		if (c == '\0') {
			if (token.offset != pos) {
				token.group = -1;
				token.length = pos - token.offset;
				sa_append(a, token);
			}
			break;
		} else if (c == '\\') {
			if (escaped) {  // just backslash
				token.group = -1;
				token.length = pos - token.offset;
				sa_append(a, token);
				token.offset = pos + 1;
				escaped = 0;
			} else {  // start escaped sequence
				escaped = 1;
			}
		} else if (escaped && isdigit(c)) {  // group number
			if (token.offset != pos - 1) {
				token.group = -1;
				token.length = (pos - 1) - token.offset;
				sa_append(a, token);
			}
			token.group = c - '0';
			token.offset = -1;
			token.length = 0;
			sa_append(a, token);
			token.offset = pos + 1;
			escaped = 0;
		}
	}
}
