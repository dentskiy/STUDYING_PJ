#ifndef CPP3_BRICKGAME_SRC_GUI_TERMINAL_WFUNCTOIN_H
#define CPP3_BRICKGAME_SRC_GUI_TERMINAL_WFUNCTOIN_H

#include <ncurses.h>

#include "../../brick_game/brickgame.h"

enum Window_t { wMenu, wTetris, wSnake, wQuit = -1 };

Window_t WinMenu();
Window_t WinDisplay(const Window_t& game);

int ActionsCase(int buton);
void MapPrint(WINDOW* win, s21::GameInfo_t& data);
void DataPrint(WINDOW* win, s21::GameInfo_t& data);

#endif  // CPP3_BRICKGAME_SRC_GUI_TERMINAL_WFUNCTOIN_H