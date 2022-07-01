#include "qol.h"
#include "Help.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	CON_Frame(0, 0, 3);
	CON_PlayerField(2, 1);
	CON_Frame(96, 0, 3);
	CON_EPlayerField();
	CON_CreateShips(ship);
	GM_Choose();
	CON_EPlayerField();
	CON_Frame(0, 0, 3);
	CON_PlayerField(2, 1);
	CON_Frame(96, 0, 3);
	GM_AutoEPlacement();
	CON_EPlayerField();
	CON_Frame(0, 0, 3);
	CON_PlayerField(2, 1);
	CON_Frame(96, 0, 3);
	CON_ZPlayerField();
	CON_EPlayerField();
	GM_Game();
	SYS_Cursor(0, 14);
}