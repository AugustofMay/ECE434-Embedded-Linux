#include <ncurses.h>

typedef struct _WIN_BORDER_struct {
	char ls, rs, ts, bs, tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {
	int startX, startY;
	int height, width;
	WIN_BORDER border;
}WIN;

void init_win_params(WIN *p_win);
void print_win_params(WIN *p_win);
void create_box(WIN *win, bool flag);

int main(int argc, char *argv[]) {
	WIN win;
	int ch;

	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_MAGENTA, COLOR_WHITE);

	init_win_params(&win);
	print_win_params(&win);

	attron(COLOR_PAIR(1));
	printw("Press e to exit");
	refresh();
	attroff(COLOR_PAIR(1));

	create_box(&win, TRUE);

	while((ch = getch()) != 'e') {
		switch(ch) {
			case KEY_LEFT:
				create_box(&win, FALSE);
				if(win.startX > 1) {
					win.startX--;
				}
				create_box(&win, TRUE);
				break;
			case KEY_RIGHT:
				break;
			case KEY_UP:
				break;
			case KEY_DOWN:
				break;
		}
	}
	endwin();
	return 0;
}

void init_win_params(WIN *p_win) {
	p_win->height = 10;
	p_win->width = 10;
	p_win->startY = 1;
	p_win->startX = 1;

	p_win->border.ls = '|';
	p_win->border.rs = '|';
	p_win->border.ts = '-';
	p_win->border.bs = '-';
	p_win->border.tl = '+';
	p_win->border.tr = '+';
	p_win->border.bl = '+';
	p_win->border.br = '+';
}

void print_win_params(WIN *p_win) {
	#ifdef _DEBUG
		mvprintw(25, 0, "%d %d %d %d", p_win->startX, p_win->startY, p_win->width, p_win->height);
		refresh();
	#endif
}

void create_box(WIN *p_win, bool flag) {
	int i, j;
	int x, y, w, h;

	x = p_win->startX;
	y = p_win->startY;
	w = p_win->width;
	h = p_win->height;

	if(flag == TRUE) {
		mvaddch(y, x, p_win->border.tl);
		mvaddch(y, x + w, p_win->border.tr);
		mvaddch(y + h, x, p_win->border.bl);
		mvaddch(y + h, x + w, p_win->border.br);
		mvhline(y, x + 1, p_win->border.ts, w - 1);
		mvhline(y + h, x + 1, p_win->border.bs, w - 1);
		mvvline(y + 1, x, p_win->border.ls, h - 1);
		mvvline(y + 1, x + w, p_win->border.rs, h - 1);
	} else {
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
	}

	refresh();

}
