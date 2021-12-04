#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	bindtextdomain("guess", ".");
	textdomain("guess");

	int low = 1;
	int high = 100;
	char answer[256];

	printf(_("Think of a number from 1 to 100. Press <enter> when ready.\n"));
	fgetc(stdin);
	printf(_("Allowed answers: lower, right, greater\n"));
	while (1) {
		int guess = (high + low) / 2;
		if (guess > high || guess < low) {
			printf(_("Conflicting answers, abort\n"));
			return 1;
		}
		printf(_("My guess is %d. Is it right? "), guess);
		scanf("%s", answer);  // todo bufsize
		if (strcmp(answer, _("right")) == 0 || strcmp(answer, _("yes")) == 0) {
			printf("Yay!\n");
			break;
		} else if (strcmp(answer, _("lower")) == 0) {
			high = guess - 1;
		} else if (strcmp(answer, _("greater")) == 0) {
			low = guess + 1;
		} else {
			printf(_("Can't understand you, please repeat\n"));
		}
	}
	return 0;
}
