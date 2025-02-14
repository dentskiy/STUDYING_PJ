#include "wfunction.h"

int main() {
  Window_t current = wMenu;
  initscr();
  cbreak();
  noecho();
  curs_set(0);

  while (current != wQuit) {
    clear();
    switch (current) {
      case wMenu:
        current = WinMenu();
        break;
      default:
        current = WinDisplay(current);
        break;
    }
  }
  endwin();
  return 0;
}
