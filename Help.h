#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

// что означают приписки к функциям
// CON - функции отрисовывающие или создающие что-то
// SYS - функции которые выставляют определенные настройки
// PRF - какая-либо проверка
// GM - функции относящиеся непосредственно к геймплею

int field [12] [24] = { {0}, {0} };
int efield[12] [24] = { {0}, {0} };
int lf[12][24] = { {0}, {0} };
bool pass;
class Ship { //класс содержащий структуру коробля
public:
	int lenth = { 0 };
	bool alive = 1;
	bool horizontal = 1;
	int xf;
	int yf;
	int xl;
	int yl;
};
Ship* ship = new Ship[20]; //создаем 20 кораблей без харакиеристик
enum keys { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Space = 32 }; //это хоткеи для движения по консоли
enum Color { Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White }; //база цветов
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //без понятия что это

//58 - центр поля

int SYS_GetXCoord() //определение координаты x курсора консоли в данный момент
{
	CONSOLE_SCREEN_BUFFER_INFO info_x;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_x);
	return info_x.dwCursorPosition.X;
}
void SYS_Color(Color text, Color background) //установка цвета
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
void SYS_Cursor(int x, int y) //установка курсора
{
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}
void SYS_Clear()
{
	for (int y = 0; y < 13; y++)
	{
		for (int x = 25; x < 95; x++)
		{
			SYS_Cursor(x, y);
			SYS_Color(Black, Black);
			cout << ' ';
		}
	}
}


void CON_Frame(int x, int y, int s) //установка рамки поля
{
	char mas[10] = { 'A','B','C','D','E','F','G','H','I','J'};
	int num[11] = { 0,1,2,3,4,5,6,7,8,9,10 };
	switch (x)
	{
	case 0:
		SYS_Color(Black, Blue);
		break;
	case 96:
		SYS_Color(Black, Red);
		break;
	}
	SYS_Cursor(x, y);
	cout << "  " << mas[0]<<" ";
	for (int j = 0; j < 12; j++)
	{
		if (j == 0)
		{
			for (int i = 1; i < 10; i++)
			{
				Sleep(s);
				cout << mas[i] << " ";
				if (i == 9) cout << "  ";
			}
			y++;
		}
		int A = SYS_GetXCoord() - 2;
		if (j > 0 && j < 10)
		{
			for (y; y <= 10; y++)
			{
				if (num[y] == 10)
				{
					Sleep(s);
					SYS_Cursor(x, y);
					cout << num[y];
					Sleep(s);
					SYS_Cursor(A, y);
					cout << "  ";
					exit;
				}
				if (num[y] < 10)
				{
					Sleep(s);
					SYS_Cursor(x, y);
					cout << num[y] << " ";
					Sleep(s);
					SYS_Cursor(A, y);
					cout << "  ";
				}
			}
		}
		if (j == 11)
		{
			
			Sleep(s);
			SYS_Cursor(x, y);
			for (int i = 0; i < 24; i++)
			{
				Sleep(s);
				cout << " ";
			}
		}
	}
}
void CON_PlayerField(int x, int y) //установка поля игрока и ИИ
{
	int buff = x;
	for (y; y < 11; y++)
	{
		x = buff;
		for (x; x < 22; x++)
		{
			Sleep(3);
			SYS_Cursor(x, y);
			SYS_Color(Color(LightCyan), Color(LightCyan));
			cout << field[y][x];
		}
	}
}
void CON_ZPlayerField() //установка поля игрока, но без задержки
{
	for (int y = 1; y < 11; y++)
	{
		for (int x = 2; x < 22; x++)
		{
			switch (field[y][x]) //этот свич отображает клутку поля с нужным для нее цветом
			{
			case 0:
				SYS_Cursor(x, y);
				SYS_Color(Color(LightCyan), Color(LightCyan));
				cout << field[y][x];
				break;
			case 1:
				SYS_Cursor(x, y);
				SYS_Color(Color(LightRed), Color(LightRed));
				cout << field[y][x];
				break;
			case 2:
				SYS_Cursor(x, y);
				SYS_Color(Color(LightCyan), Color(LightCyan));
				cout << field[y][x];
				break;
			case 4:
				SYS_Cursor(x, y);
				SYS_Color(Color(LightGray), Color(LightGray));
				cout << field[y][x];
				break;
			case 5:
				SYS_Cursor(x, y);
				SYS_Color(Color(Red), Color(Red));
				cout << field[y][x];
				break;
			}
		}
	}
}
void CON_LPlayerField() //установка поля игрока и ИИ, но буз задержки
{
	int x = 2;
	int y = 1;
	int buff = x;
	for (y; y < 11; y++)
	{
		x = buff;
		for (x; x < 22; x++)
		{
			switch (lf[y][x]) //этот свич отображает клутку поля с нужным для нее цветом
			{
			case 3:
				SYS_Cursor(x, y);
				SYS_Color(Color(Magenta), Color(Magenta));
				cout << lf[y][x];
				break;
			}
		}
	}
}
void CON_EPlayerField()
{
	int h = 96;
	for (int y = 1; y < 11; y++)
	{
		for (int x = 2; x < 22; x++)
		{
			switch (efield[y][x]) //этот свич отображает клетку поля с нужным для нее цветом
			{
			case 0:
				SYS_Cursor(x + h, y);
				SYS_Color(Color(LightCyan), Color(LightCyan));
				cout << efield[y][x];
				break;
			case 1:
				SYS_Cursor(x + h, y);
				SYS_Color(Color(LightCyan), Color(LightCyan));
				cout << efield[y][x];
				break;
			case 2:
				SYS_Cursor(x + h, y);
				SYS_Color(Color(LightCyan), Color(LightCyan));
				cout << efield[y][x];
				break;
			case 4:
				SYS_Cursor(x + h, y);
				SYS_Color(Color(LightGray), Color(LightGray));
				cout << efield[y][x];
				break;
			case 5:
				SYS_Cursor(x + h, y);
				SYS_Color(Color(Red), Color(Red));
				cout << efield[y][x];
				break;
			}
		}
	}
}
void CON_ZField()
{
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			if (lf[y][x] == 3) lf[y][x] = 0;
		}
	}
}
void CON_EnemyField() //установка поля противника
{
	int x = 95, y = 1;
	SYS_Color(Color(0), Color(15));
	for (y; y <= 10; y++)
	{
		for (int xh = 2; x < 24; x++)
		{
			SYS_Cursor(x + xh, y);
			Sleep(0);
			cout << efield[y][xh];
		}
	}
}
void CON_Barrier(bool e) //окружает готовый корабль барьером
{
	int x, y;
	switch (e)
	{
	case 0:
		for (y = 1; y < 11; y++)
		{
			for (x = 2; x < 22; x += 2)
			{
				if (field[y][x] == 1)
				{
					for (int j = -1; j <= 1; j++)
					{
						for (int i = -2; i <= 2; i += 2)
						{
							if (field[y + j][x + i] == 0)
							{
								field[y + j][x + i] = 2;
								field[y + j][x + i + 1] = 2;
							}
						}
					}
				}
			}
		}
		CON_ZPlayerField();
	case 1:
		for (y = 1; y < 11; y++)
		{
			for (x = 2; x < 22; x += 2)
			{
				if (efield[y][x] == 1)
				{
					for (int j = -1; j <= 1; j++)
					{
						for (int i = -2; i <= 2; i += 2)
						{
							if (efield[y + j][x + i] == 0)
							{
								efield[y + j][x + i] = 2;
								efield[y + j][x + i + 1] = 2;
							}
						}
					}
				}
			}
		}
		CON_EPlayerField();
	}
}
void CON_CreateShips(Ship* ship) //задаем кораблям количество палуб
{
	for (int i = 0; i < 20; i++)
	{
		if (i == 0 || i == 10)
		{
			ship[i].lenth = 4;
		}
		else if (i > 0 && i < 3 || i > 10 && i < 13)
		{
			ship[i].lenth = 3;
		}
		else if (i > 2 && i < 6 || i > 12 && i < 16)
		{
			ship[i].lenth = 2;
		}
		else if (i > 5 && i < 10 || i > 15 && i < 20)
		{
			ship[i].lenth = 1;
		}
	}
}
void CON_SetShip(int x, int y, int l, bool h, bool e)
{
	switch (h)
	{
	case 0:
		for (int i = 0; i < l; i++)
		{
			lf[y + i][x] = 3;
			lf[y + i][x + 1] = 3;
		}
		break;
	case 1:
		for (int i = 0; i < l; i++)
		{
			lf[y][x + i] = 3;
		}
		break;
	}
}


bool PRF_Proof(int x, int y, int l, bool h)
{
	switch (h)
	{
	case 1:
		if (22 - x >= l) return 1;
		else return 0;
		break;
	case 0:
		if (11 - y >= l) return 1;
		else return 0;
		break;
	}
}
bool PRF_Space(int x, int y, int l, bool h, bool e)
{
	int c = 0;
	switch (e)
	{
	case 0:
		switch (h)
		{
		case 1:
			for (int i = 0; i < l; i++)
			{
				if (field[y][x + i] == 0) c++;
			}
			if (c == l) return 1;
			else return 0;
		case 0:
			for (int i = 0; i < l; i++)
			{
				if (field[y + i][x] == 0) c++;
			}
			if (c == l) return 1;
			else return 0;
		}
	case 1:
		switch (h)
		{
		case 1:
			for (int i = 0; i < l; i++)
			{
				if (efield[y][x + i] == 0) c++;
			}
			if (c == l) return 1;
			else return 0;
		case 0:
			for (int i = 0; i < l; i++)
			{
				if (efield[y + i][x] == 0) c++;
			}
			if (c == l) return 1;
			else return 0;
		}
	}
}


void GM_ManualPlacement(int x, int y) //ручная расстановка кораблей
{
	int key;
	int xl, yl;
	SYS_Cursor(x, y);
	for (int i = 0; i < 10; i++)
	{
		int l = ship[i].lenth;
		int lv = l, lh = l * 2;
		do
		{
			key = _getch();
			switch (key)
			{
			case Enter:
				ship[i].xf = x, ship[i].yf = y;
				switch (ship[i].horizontal)
				{
				case 1:
					if (PRF_Space(x, y, lh, ship[i].horizontal, 0))
					{
						for (int i = 0; i < lh; i++)
						{
							field[y][x + i] = 1;
						}
						ship[i].xl = x + ship[i].lenth - 2, ship[i].yl = y + ship[i].lenth - 1;
					}
					else
					{
						i--;
						CON_LPlayerField();
					}
					break;
				case 0:
					if (PRF_Space(x, y, lv, ship[i].horizontal, 0))
					{
						for (int i = 0; i < lv; i++)
						{
							field[y + i][x] = 1;
							field[y + i][x + 1] = 1;
						}
						ship[i].xl = x + ship[i].lenth - 2, ship[i].yl = y + ship[i].lenth - 1;
					}
					else
					{
						i--;
						CON_LPlayerField();
					}
					break;
				}
				CON_ZPlayerField();				
				break;
			case Up:
				if (y > 1 && y < 12) y--;
				CON_ZField();
 				switch (ship[i].horizontal)
				{
				case 1:
					if (PRF_Proof(x, y, lh, ship[i].horizontal))
					{
						CON_SetShip(x, y, lh, ship[i].horizontal, 0);
					}
					else
					{
						y++;
						CON_SetShip(x, y, lh, ship[i].horizontal, 0);
					}
					break;
				case 0:
					if (PRF_Proof(x, y, lv, ship[i].horizontal))
					{
						CON_SetShip(x, y, lv, ship[i].horizontal, 0);
					}
					else
					{
						y++;
						CON_SetShip(x, y, lv, ship[i].horizontal, 0);
					}
					break;
				}
				CON_ZPlayerField();
				CON_LPlayerField();
				break;
			case Left:
				if (x <= 20 && x > 2) x -= 2;
				CON_ZField();
				switch (ship[i].horizontal)
				{
				case 1:
					if (PRF_Proof(x, y, lh, ship[i].horizontal))
					{
						CON_SetShip(x, y, lh, ship[i].horizontal, 0);
					}
					else
					{
						x += 2;
						CON_SetShip(x, y, lh, ship[i].horizontal, 0);
					}
					break;
				case 0:
					if (PRF_Proof(x, y, lv, ship[i].horizontal))
					{
						CON_SetShip(x, y, lv, ship[i].horizontal, 0);
					}
					else
					{
						x += 2;
						CON_SetShip(x, y, lv, ship[i].horizontal, 0);
					}
					break;
				}
				CON_ZPlayerField();
				CON_LPlayerField();
				break;
			case Right:
				if (x > 1 && x < 20) x += 2;
				CON_ZField();
				switch (ship[i].horizontal)
				{
				case 1:
					if (PRF_Proof(x, y, lh, ship[i].horizontal))
					{
						CON_SetShip(x, y, lh, ship[i].horizontal, 0);
					}
					else
					{
						x -= 2;
						CON_SetShip(x, y, lh, ship[i].horizontal, 0);
					}
					break;
				case 0:
					if (PRF_Proof(x, y, lv, ship[i].horizontal))
					{
						CON_SetShip(x, y, lv, ship[i].horizontal, 0);
					}
					else
					{
						x -= 2;
						CON_SetShip(x, y, lv, ship[i].horizontal, 0);
					}
					break;
				}
				CON_ZPlayerField();
				CON_LPlayerField();
				break;
			case Down:
				if (y > 0 && y < 10) y++;
				CON_ZField();
				switch (ship[i].horizontal)
				{
				case 1:
					if (PRF_Proof(x, y, lh, ship[i].horizontal))
					{
						CON_SetShip(x, y, lh, ship[i].horizontal, 0);
					}
					else
					{
						y--;
						CON_SetShip(x, y, lh, ship[i].horizontal, 0);
					}
					break;
				case 0:
					if (PRF_Proof(x, y, lv, ship[i].horizontal))
					{
						CON_SetShip(x, y, lv, ship[i].horizontal, 0);
					}
					else
					{
						y--;
						CON_SetShip(x, y, lv, ship[i].horizontal, 0);
					}
					break;
				}
				CON_ZPlayerField();
				CON_LPlayerField();
				break;
			case Space:
				ship[i].horizontal = !ship[i].horizontal;
				CON_ZField();
				switch (ship[i].horizontal)
				{
				case 1:
					if (PRF_Proof(x, y, lh, ship[i].horizontal) && (24 - x) >= (ship[i].lenth)*2)
					{
						CON_SetShip(x, y, lh, ship[i].horizontal, 0);
					}
					else
					{
						ship[i].horizontal = !ship[i].horizontal;
						if (PRF_Proof(x, y, lv, ship[i].horizontal) && (12 - y) >= ship[i].lenth)
						{
							CON_SetShip(x, y, lv, ship[i].horizontal, 0);
						}
					}
					break;
				case 0:
					if (PRF_Proof(x, y, lv, ship[i].horizontal) && (12 - y) >= ship[i].lenth)
					{
						CON_SetShip(x, y, lv, ship[i].horizontal, 0);
					}
					else
					{
						ship[i].horizontal = !ship[i].horizontal;
						if (PRF_Proof(x, y, lh, ship[i].horizontal) && (24 - x) >= (ship[i].lenth) * 2)
						{
							CON_SetShip(x, y, lh, ship[i].horizontal, 0);
						}
					}
					break;
				}
				CON_ZPlayerField();
				CON_LPlayerField();
			}
			SYS_Cursor(x, y);
		} while (key != Enter);
		CON_ZPlayerField();
		CON_LPlayerField();
		CON_Barrier(0);
	}
}
void GM_AutoPlacement()
{
	SYS_Clear();
	SYS_Cursor(46, 5);
	SYS_Color(White, Black);
	cout << "РАССТАВЛЯЕМ ВАШИ КОРАБЛИ";
	SYS_Cursor(40, 6);
	SYS_Color(White, Black);
	cout << "ЭТО МОЖЕТ ЗАНЯТЬ НЕКОТОРОЕ ВРЕМЯ...";
	for (int i = 0; i < 10; i++)
	{
		int l = ship[i].lenth;
		int lv = l, lh = l * 2;
		srand(time(0));
		int x = rand() % 20 + 1;
		if (x % 2 != 0) x++;
		int y = rand() % 10 + 1;
		SYS_Cursor(x, y);
		ship[i].horizontal = rand() % 2;
		switch (ship[i].horizontal)
		{
		case 1:
			if (PRF_Space(x, y, lh, ship[i].horizontal, 0) && lh < 24 - x)
			{
				for (int j = 0; j < lh; j++)
				{
					field[y][x + j] = 1;
				}
			}
			else i--;
			break;
		case 0:
			if (PRF_Space(x, y, lv, ship[i].horizontal, 0) && lv < 11 - y)
			{
				for (int j = 0; j < lv; j++)
				{
					field[y + j][x] = 1;
					field[y + j][x + 1] = 1;
				}
			}
			else i--;
			break;
		}
		CON_Barrier(0);
	}
	CON_ZPlayerField();
}
void GM_AutoEPlacement()
{
	SYS_Clear();
	SYS_Cursor(46, 5);
	SYS_Color(White, Black);
	cout << "РАССТАВЛЯЕМ КОРАБЛИ ПРОТИВНИКА";
	SYS_Cursor(43, 6);
	SYS_Color(White, Black);
	cout << "ЭТО МОЖЕТ ЗАНЯТЬ НЕКОТОРОЕ ВРЕМЯ...";
	for (int i = 10; i < 20; i++)
	{
		int l = ship[i].lenth;
		int lv = l, lh = l * 2;
		srand(time(0));
		int x = rand() % 19 + 1;
		if (x % 2 != 0) x++;
		int y = rand() % 10 + 1;
		SYS_Cursor(x, y);
		ship[i].horizontal = rand() % 2;
		switch (ship[i].horizontal)
		{
		case 1:
			if (PRF_Space(x, y, lh, ship[i].horizontal, 1) && lh < 24 - x)
			{
				for (int j = 0; j < lh; j++)
				{
					efield[y][x + j] = 1;
				}
			}
			else i--;
			break;
		case 0:
			if (PRF_Space(x, y, lv, ship[i].horizontal, 1) && lv < 11 - y)
			{
				for (int j = 0; j < lv; j++)
				{
					efield[y + j][x] = 1;
					efield[y + j][x + 1] = 1;
				}
			}
			else i--;
			break;
		}
		CON_ZPlayerField();
		CON_Barrier(1);
	}
	CON_EPlayerField();
}
void GM_Choose()
{
	SYS_Color(Color(Red), Color(Black));
	SYS_Cursor(43, 4);
	cout << "ВЫБЕРИТЕ ТИП УСТАНОВКИ КОРАБЛЕЙ";
	SYS_Cursor(50, 6);
	SYS_Color(Color(White), Color(Black));
	cout << "РУЧНАЯ УСТВНОВКА";
	SYS_Cursor(46, 7);
	SYS_Color(Color(White), Color(Black));
	cout << "АВТОМАТИЧЕСКАЯ УСТАНОВКА";
	int key;
	bool c;
	do 
	{
		key = _getch();
		switch (key)
		{
		case Enter:
			if (c == 1)
			{
				GM_ManualPlacement(2,1);
			}
			else GM_AutoPlacement();
		case Up:
			SYS_Cursor(50, 6);
			SYS_Color(Color(Black), Color(White));
			cout << "РУЧНАЯ УСТВНОВКА";
			SYS_Cursor(46, 7);
			SYS_Color(Color(White), Color(Black));
			cout << "АВТОМАТИЧЕСКАЯ УСТАНОВКА";
			c = 1;
			break;
		case Down:
			SYS_Cursor(50, 6);
			SYS_Color(Color(White), Color(Black));
			cout << "РУЧНАЯ УСТВНОВКА";
			SYS_Cursor(46, 7);
			SYS_Color(Color(Black), Color(White));
			cout << "АВТОМАТИЧЕСКАЯ УСТАНОВКА";
			c = 0;
			break;
		}
	} while (key != Enter);
	system("cls");
}
void GM_Game()
{
	int php = 0, ehp = 0, r = 0;
	int key;
	int x = 98, y = 1;
	bool z, w= 0 , l = 0;
	while(php < 20 && ehp < 20)
	{
		r++;
		SYS_Clear();
		SYS_Color(Color(White), Color(Black));
		SYS_Cursor(54, 3);
		cout << "РАУНД " << r;
		SYS_Color(Color(Red), Color(Black));
		SYS_Cursor(52, 5);
		cout << "СдЕлАй СвОй ХоД!";
		x = 98, y = 1;
		SYS_Cursor(x, y);
		z = 0;
		while (z == 0)
		{
			key = _getch();
			switch (key)
			{
			case Enter:
				switch (efield[y][x - 95])
				{
				case 0:
					efield[y][x - 96] = 4;
					efield[y][x - 95] = 4;
					z = 1;
					break;
				case 1:
					efield[y][x - 96] = 5;
					efield[y][x - 95] = 5;
					ehp++;
					z = 1;
					break;
				case 2:
					efield[y][x - 96] = 4;
					efield[y][x - 95] = 4;
					z = 1;
					break;
				case 4:
					z = 0;
					break;
				case 5:
					z = 0;
					break;
				}
				break;
			case Up:
				if (y > 1 && y < 12) y--;
				SYS_Cursor(x, y);
				break;
			case Down:
				if (y > 0 && y < 10) y++;
				SYS_Cursor(x, y);
				break;
			case Right:
				if (98 <= x && x < 116) x += 2;
				SYS_Cursor(x, y);
				break;
			case Left:
				if (100 <= x && x <= 118) x -= 2;
				SYS_Cursor(x, y);
				break;
			}
		}
		CON_EPlayerField();
		z = 0;
		while (z == 0)
		{
			srand(time(0));
			x = rand() % 19 + 1;
			if (x % 2 != 0) x++;
			y = rand() % 11 + 1;
			switch (field[y][x])
			{
			case 0:
				field[y][x + 1] = 4;
				field[y][x] = 4;
				z = 1;
				break;
			case 1:
				field[y][x + 1] = 5;
				field[y][x] = 5;
				php++;
				z = 1;
				break;
			case 2:
				field[y][x + 1] = 4;
				field[y][x] = 4;
				z = 1;
				break;
			case 4:
				z = 0;
				break;
			case 5:
				z = 0;
				break;
			}
		}
		CON_ZPlayerField();
		if (php == 20) l = 1;
		if (ehp == 20) w = 1;
	}
	if (w == 1)
	{
		SYS_Clear();
		SYS_Cursor(46, 5);
		SYS_Color(White, Black);
		cout << "ПОЗДРАВЛЯЕМ С ПОБЕДОЙ!!!";
	}
	if (l == 1)
	{
		SYS_Clear();
		SYS_Cursor(50, 5);
		SYS_Color(White, Black);
		cout << "ТЫ ПРОИГРАЛ ЛУЗЕР!";
	}
}