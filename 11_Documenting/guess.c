#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

/** \var char *roman_numbers
 *  \brief Predefined first 100 Roman numerical
*/
char *roman_numbers[] = {"N","I","II","III","IV","V","VI","VII","VIII","IX","X","XI","XII","XIII","XIV","XV","XVI","XVII","XVIII","XIX","XX","XXI","XXII","XXIII","XXIV","XXV","XXVI","XXVII","XXVIII","XXIX","XXX","XXXI","XXXII","XXXIII","XXXIV","XXXV","XXXVI","XXXVII","XXXVIII","XXXIX","XL","XLI","XLII","XLIII","XLIV","XLV","XLVI","XLVII","XLVIII","XLIX","L","LI","LII","LIII","LIV","LV","LVI","LVII","LVIII","LIX","LX","LXI","LXII","LXIII","LXIV","LXV","LXVI","LXVII","LXVIII","LXIX","LXX","LXXI","LXXII","LXXIII","LXXIV","LXXV","LXXVI","LXXVII","LXXVIII","LXXIX","LXXX","LXXXI","LXXXII","LXXXIII","LXXXIV","LXXXV","LXXXVI","LXXXVII","LXXXVIII","LXXXIX","XC","XCI","XCII","XCIII","XCIV","XCV","XCVI","XCVII","XCVIII","XCIX","C"};

char *itor(int i) {
    /** \brief Converts integer to Roman numerical
     * \param i - from 0 to 100
     * \returns string if in range, otherwise NULL
     */
    if (i < 0 || i > 100)
        return NULL;
    return roman_numbers[i];
}

int rtoi(char *r) {
    /** \brief Converts Roman numerical to integer
     * \param r - string (capital letters)
     * \returns integer value if in range, otherwise -1
     */
    for (int i = 0; i <= 100; i++) {
        if (strcmp(roman_numbers[i], r) == 0)
            return i;
    }
    return -1;
}

void print_help(char *exe) {
    printf("Usage: %s [OPTIONS]\n", exe);
    printf("-r          %s\n", _("use Roman numerals"));
    printf("    --help  %s\n", _("show this message"));
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	bindtextdomain("guess", ".");
	textdomain("guess");

    int use_roman = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-r") == 0) {
            use_roman = 1;
        } else {
            fprintf(stderr, _("Unknown option. See --help\n"));
            return 1;
        }
    }

	int low = 1;
	int high = 100;
	char answer[256];

    if (!use_roman)
	    printf(_("Think of a number from 1 to 100. Press <enter> when ready.\n"));
    else
        printf(_("Think of a number from I to L. Press <enter> when ready.\n"));
	fgetc(stdin);
	printf(_("Allowed answers: lower, right, greater\n"));
	while (1) {
		int guess = (high + low) / 2;
		if (guess > high || guess < low) {
			printf(_("Conflicting answers, abort\n"));
			return 1;
		}
        if (!use_roman)
		    printf(_("My guess is %d. Is it right? "), guess);
        else
            printf(_("My guess is %s. Is it right? "), itor(guess));
		scanf("%s", answer);
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
