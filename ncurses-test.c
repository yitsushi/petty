#include <ncurses.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int max_x = 0,
      max_y = 0;

  initscr();
  noecho();
  cbreak();
  keypad(stdscr, 1);
  curs_set(0);

  getmaxyx(stdscr, max_y, max_x);

  int x = 0, y = 0;

  WINDOW *info = newwin(20, 0, 0, 0);
  wborder(info, '|', '|', '-', '-', '+', '+', '+', '+');
  box(info, 0, 0);
  wrefresh(info);

  WINDOW *command = newwin(20, 0, 20, 0);
  //box(command, 0, 0);
  wrefresh(command);

  while (1)
  {
    //clear();
    wclear(info);
    wclear(command);

    timeout(10);
    char ch = getch();
    if ( ch == 0x1b && (ch = getch() == 0x78) ) break;

    // do stuff
    if (ch != -1)
    {
      wprintw(command, "%c (%03x - %03x)", ch, ch, KEY_F(1));
    }

    wprintw(info, "Press ESC+x to quit.");
    mvwprintw(info, 1, 1, "o");

    wrefresh(info);
    wrefresh(command);
    //refresh();
  }

  endwin();
}
