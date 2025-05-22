#include "config.h"

HANDLE Out()
{
	return (GetStdHandle(STD_OUTPUT_HANDLE));
}

void gotoxy(int x, int y) 
{
  COORD Point;
  Point.X = x;
  Point.Y = y;
  SetConsoleCursorPosition(Out(), Point);
}


