#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DX 3

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("No input file specified\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input== NULL) {
        printf("Can't open file: %s\n", argv[1]);
        return 2;
    }
    int n_lines = 0;
    int cur_line = 0;
    int cur_col = 0;
    int n_lines_cap = 10;
    char **lines = malloc(sizeof(char*) * n_lines_cap);
    while (1) {
        char *line = NULL;
        size_t len = 0;
        ssize_t nread = getline(&line, &len, input);
        if (nread <= 0) {
            if (nread == 0)
                free(line);
            break;
        }
        if (n_lines == n_lines_cap) {
            n_lines_cap *= 2;
            lines = realloc(lines, sizeof(char*) * n_lines_cap);
        }
        lines[n_lines++] = line;
    }


    WINDOW *win;
    int c = 0;
    initscr();
    noecho();
    cbreak();
    printw("File: %s", argv[1]);
    refresh();

    win = newwin(LINES - 2 * DX, COLS - 2 * DX, DX, DX);
    keypad(win, TRUE);
    scrollok(win, FALSE);

    do {
        switch (c) {
            case ' ':
            case KEY_DOWN:
                if (cur_line + 1 < n_lines)
                    cur_line++;
                break;
            case KEY_UP:
                if (cur_line > 0)
                    cur_line--;
                break;
            case KEY_LEFT:
                if (cur_col > 0)
                    cur_col--;
                break;
            case KEY_RIGHT:
                cur_col++;
                break;
        }
        werase(win);

        for (int i = 0; i < LINES - 2 * (DX + 1); i++) {
            wmove(win, i + 1, 0);
            int line_idx = cur_line + i;
            if (line_idx >= n_lines)
                break;
            if (strlen(lines[line_idx]) > cur_col)
                wprintw(win, "  %3d: %s", cur_line + i + 1, lines[line_idx] + cur_col);
            else
                wprintw(win, "  %3d:", cur_line + i + 1);
        }
        
        wmove(win, 0, 0);
        box(win, 0, 0);
        wrefresh(win);
    } while ((c = wgetch(win)) != 27);

    endwin();
    for (int i = 0; i < n_lines; i++)
        free(lines[i]);
    free(lines);

    return 0;
}

