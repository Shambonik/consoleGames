#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

int n = 9;
short cursorPositionOld[2] = { 0,0 };
short cursorPosition[2] = { 0,0 };
int bombs[9][9];
bool opened[9][9];
bool flagged[9][9];
int status = 0;
int n_bombs = 12;
COORD position;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int minimum(int position) {
	int m = 0;
	if (position == 0) {
		m = 0;
	}
	else {
		m = position - 1;
	}
	return m;
}

int maximum(int position) {
	int m = 0;
	if (position == n - 1) {
		m = n - 1;
	}
	else {
		m = position + 1;
	}
	return m;
}

void clearBorder(int x, int y) {
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	if ((minimum(x) != x) && (opened[x - 1][y])) {
		left = true;
	}
	if ((maximum(x) != x) && (opened[x + 1][y])) {
		right = true;
	}
	if ((minimum(y) != y) && (opened[x][y - 1])) {
		up = true;
	}
	if ((maximum(y) != y) && (opened[x][y + 1])) {
		down = true;
	}
	for (int i = 0; i < 4; i++) {
		if (i % 2 == 0) {
			if (left) {
				position = { (short)x * 4, (short)(y * 3 + (i/2)+1) };
				SetConsoleCursorPosition(hConsole, position);
				cout << " ";
			}
			if (right) {
				position = { (short)(x+1) * 4,(short)(y * 3 + (i / 2)+1) };
				SetConsoleCursorPosition(hConsole, position);
				cout << " ";
			}
		}
		if (up) {
			position = { (short)(x * 4 + i),(short)y * 3};
			SetConsoleCursorPosition(hConsole, position);
			cout << " ";
		}
		if (down) {
			position = { (short) (x * 4 + i),(short)(y+1) * 3};
			SetConsoleCursorPosition(hConsole, position);
			cout << " ";
		}
	}
	SetConsoleCursorPosition(hConsole, { 2, 34 });
}

void flag() {
	if (!opened[cursorPosition[0]][cursorPosition[1]]) {
		position = { cursorPosition[0] * 4 + 1, cursorPosition[1] * 3 + 1 };
		SetConsoleCursorPosition(hConsole, position);
		if (flagged[cursorPosition[0]][cursorPosition[1]]) {
			flagged[cursorPosition[0]][cursorPosition[1]] = false;
			cout << " ";
		}
		else {
			SetConsoleTextAttribute(hConsole, 14); //Цвет текста - желтый
			flagged[cursorPosition[0]][cursorPosition[1]] = true;
			cout << "?";
			SetConsoleTextAttribute(hConsole, 15); //Цвет текста - белый
		}
	}
	SetConsoleCursorPosition(hConsole, { 2, 34 });
}

void open(int x, int y) {
	if (!opened[x][y]) {
		position = {(short) x * 4 + 1, (short) y * 3 + 1 };
		SetConsoleCursorPosition(hConsole, position);
		opened[x][y] = true;
		if (bombs[x][y] == -1) {
			SetConsoleTextAttribute(hConsole, 12); //Цвет текста - свтело-красный
			cout << "*";
			status = -1;
			SetConsoleCursorPosition(hConsole, { 2, 32 });
			cout << "Поражение :(";
		}
		else {
			if(bombs[x][y]!=0) cout << bombs[x][y];
			clearBorder(x, y);
		}
		if (bombs[x][y] == 0) {
			for (int i = minimum(y); i <= maximum(y); i++) {
				for (int j = minimum(x); j <= maximum(x); j++) {
					open(j, i);
				}
			}
		}
	}
	SetConsoleCursorPosition(hConsole, { 2, 34 });
}

void generate() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			bombs[i][j] = 0;
			opened[i][j] = false;
			flagged[i][j] = false;
		}
	}
	for (int i = 0; i < n_bombs; i++) {
		int x = rand() % n;
		int y = rand() % n;
		while ((x >= minimum(cursorPosition[0])) && (x <= maximum(cursorPosition[0])) && (y >= minimum(cursorPosition[1])) && (y <= maximum(cursorPosition[1]))) {
			x = (x + 4) % n;
			y = (y - 4) % n;
		}
		while (bombs[x][y] == -1) {
			x = (x - 6) % n;
			y = (y + 3) % n;
		}
		bombs[x][y] = -1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (bombs[i][j] != -1) {
				for (int k = minimum(i); k <= maximum(i); k++) {
					for (int l = minimum(j); l <= maximum(j); l++) {
						if (bombs[k][l] == -1)bombs[i][j]++;
					}
				}
			}
		}
	}
}

void drawCursor() {
	position = { cursorPositionOld[0] * 4 + 3, cursorPositionOld[1] * 3 + 1 };
	SetConsoleCursorPosition(hConsole, position);
	cout << " ";
	position = { cursorPositionOld[0] * 4 + 3, cursorPositionOld[1] * 3 + 2 };
	SetConsoleCursorPosition(hConsole, position);
	cout << " ";
	position = { cursorPositionOld[0] * 4 + 2, cursorPositionOld[1] * 3 + 2 };
	SetConsoleCursorPosition(hConsole, position);
	cout << " ";
	position = { cursorPosition[0] * 4 + 3, cursorPosition[1] * 3 + 1 };
	SetConsoleCursorPosition(hConsole, position);
	cout << "|";
	position = { cursorPosition[0] * 4 + 3, cursorPosition[1] * 3 + 2 };
	SetConsoleCursorPosition(hConsole, position);
	cout << "|";
	position = { cursorPosition[0] * 4 + 2, cursorPosition[1] * 3 + 2 };
	SetConsoleCursorPosition(hConsole, position);
	cout << "_";
	SetConsoleCursorPosition(hConsole, { 2, 34 });
}

void drawField() {
	for (int i = 0; i <= n * 3; i++) {
		for (int j = 0; j <= n * 4; j++) {
			if (i % 3 == 0) {
				cout << "-";
			}
			else if (j % 4 == 0) {
				cout << "|";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	cout <<"Перемещение курсора <- ->; Поставить флаг \"NUMPAD5\"; Рискнуть \"SPACE\"";
}

bool checkWin() {
	bool result = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result = ((bombs[i][j] == -1) && (flagged[i][j]))||((bombs[i][j] != -1)&&(opened[i][j]));
			if (!result) break;
		}
		if (!result) break;
	}
	return result;
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	srand(time(nullptr));
	SetConsoleTextAttribute(hConsole, 15); //Цвет текста - белый
	drawField();
	drawCursor();
	int gen = 0;
	while (status == 0) {
		cursorPositionOld[0] = cursorPosition[0];
		cursorPositionOld[1] = cursorPosition[1]; 

		if (GetAsyncKeyState(VK_SPACE)) {
			if (gen == 0) {
				gen++;
				generate();
			}
			open(cursorPosition[0], cursorPosition[1]);
		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			cursorPosition[0] = (cursorPosition[0] + n-1) % n;
			drawCursor();
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			cursorPosition[0] = (cursorPosition[0] + 1) % n;
			drawCursor();
		}
		else if (GetAsyncKeyState(VK_UP)) {
			cursorPosition[1] = (cursorPosition[1] + n-1) % n;
			drawCursor();
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			cursorPosition[1] = (cursorPosition[1] + 1) % n;
			drawCursor();
		}
		else if ((GetAsyncKeyState(VK_NUMPAD5))&&(gen!=0)){
			flag();
		}
		Sleep(110);
		if (checkWin()) {
			SetConsoleTextAttribute(hConsole, 10); //Цвет текста - светло-зеленый
			status = 1;
			cout << "Победа!!! :)" << endl;
		}
	}
	system("pause");
}

