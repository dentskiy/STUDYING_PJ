#include "wfunction.h"

Window_t WinMenu() {
  Window_t res[] = {wTetris, wSnake, wQuit};
  int pos{};
  int iKey{};
  WINDOW* menu = newwin(5, 22, 0, 0);
  keypad(menu, true);
  refresh();
  box(menu, 0, 0);
  while (res[pos] != wQuit && iKey != ' ' && iKey != '\n') {
    wattron(menu, WA_REVERSE);
    if (pos == 0)
      mvwprintw(menu, 1, 1, "Tetris");
    else if (pos == 1)
      mvwprintw(menu, 2, 1, "Snake");
    wattroff(menu, WA_REVERSE);
    if (pos == 1)
      mvwprintw(menu, 1, 1, "Tetris");
    else if (pos == 0)
      mvwprintw(menu, 2, 1, "Snake");
    wrefresh(menu);
    iKey = wgetch(menu);
    if (iKey == KEY_DOWN && pos != 1)
      pos++;
    else if (iKey == KEY_UP && pos != 0)
      pos--;
    else if (iKey == 'q')
      pos = 2;
  }
  delwin(menu);
  return res[pos];
}

Window_t WinDisplay(const Window_t& game) {
  s21::Controller* cntrl = nullptr;
  s21::GameInfo_t data{};
  int iCode{};

  WINDOW* display = newwin(22, 22, 0, 0);
  WINDOW* panel = newwin(22, 15, 0, 23);
  keypad(display, true);
  refresh();
  box(display, 0, 0);
  box(panel, 0, 0);

  if (game == wTetris)
    cntrl = new s21::Controller(new s21::TetrisModel());
  else
    cntrl = new s21::Controller(new s21::SnakeModel());

  while (data.pause != s21::GameOver || iCode != s21::Terminate) {
    data = cntrl->updateCurrentState();
    MapPrint(display, data);
    DataPrint(panel, data);
    wtimeout(display, 1000 / 50);
    iCode = ActionsCase(wgetch(display));
    if (iCode < 0)
      cntrl->userInput({}, false);
    else
      cntrl->userInput((s21::UserAction_t)iCode, true);
  }
  delwin(display);
  delwin(panel);
  delete cntrl;
  return wMenu;
}

int ActionsCase(int buton) {
  int res{};
  switch (buton) {
    case KEY_UP:
      res = s21::Up;
      break;
    case KEY_DOWN:
      res = s21::Down;
      break;
    case KEY_LEFT:
      res = s21::Left;
      break;
    case KEY_RIGHT:
      res = s21::Right;
      break;
    case ' ':
      res = s21::Action;
      break;
    case 27:
      res = s21::Pause;
      break;
    case 'q':
      res = s21::Terminate;
      break;
    case '\n':
      res = s21::Start;
      break;
    default:
      res = -1;
  }
  return res;
}

void MapPrint(WINDOW* win, s21::GameInfo_t& data) {
  for (int i{}; i < s21::kHeight; i++) {
    for (int j{}; j < s21::kWidth; j++) {
      if (data.field[i][j] == s21::kMoveCell)
        mvwprintw(win, i + 1, j * 2 + 1, "[]");
      else if (data.field[i][j] == s21::kStaticCell)
        mvwprintw(win, i + 1, j * 2 + 1, "()");
      else
        mvwprintw(win, i + 1, j * 2 + 1, "  ");
    }
  }
  wrefresh(win);
}

void DataPrint(WINDOW* win, s21::GameInfo_t& data) {
  int n_str{1};
  if (data.high_score >= 0) {
    mvwprintw(win, n_str++, 1, "High score:");
    mvwprintw(win, n_str++, 1, "%06d", data.high_score);
    n_str++;
  }
  if (data.score >= 0) {
    mvwprintw(win, n_str++, 1, "Score:");
    mvwprintw(win, n_str++, 1, "%06d", data.score);
    n_str++;
  }
  mvwprintw(win, n_str++, 1, "Level:");
  mvwprintw(win, n_str++, 1, "%d", data.level);
  n_str++;
  if (data.next) {
    mvwprintw(win, n_str++, 1, "Next:");
    for (int i{}; i < 4; i++) {
      for (int j{}; j < 4; j++) {
        if (data.next[i][j])
          mvwprintw(win, i + n_str, j * 2 + 1, "[]");
        else
          mvwprintw(win, i + n_str, j * 2 + 1, "  ");
      }
    }
  }
  wrefresh(win);
}