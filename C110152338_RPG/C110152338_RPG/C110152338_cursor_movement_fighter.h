#ifndef CURSOR_H
#define CURSOR_H
#include <Windows.h>

//==================<¥ú¼Ð²¾°Ê>=========================
void cursor_movement_fighter(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a, coord);
}
#endif