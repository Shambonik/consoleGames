#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

int n;
short cursorPositionOld[2];
short cursorPosition[2];
int** bombs;
bool** opened;
bool** flagged;
int status;
int n_bombs;
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
	SetConsoleCursorPosition(hConsole, { (short)n * 4 + 1,(short) n*2 });
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
	SetConsoleCursorPosition(hConsole, { (short)n * 4 + 1, (short)n * 2 });
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
			SetConsoleCursorPosition(hConsole, { 2, (short)n * 4 });
			cout << "Поражение :(\n";
		}
		else {
			if(bombs[x][y]!=0) cout << bombs[x][y];
			clearBorder(x, y);
			SetConsoleCursorPosition(hConsole, { (short)n * 4 + 1, (short)n * 2 });
		}
		if (bombs[x][y] == 0) {
			for (int i = minimum(y); i <= maximum(y); i++) {
				for (int j = minimum(x); j <= maximum(x); j++) {
					open(j, i);
				}
			}
		}
	}
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
		while (((x >= minimum(cursorPosition[0])) && (x <= maximum(cursorPosition[0])) && (y >= minimum(cursorPosition[1])) && (y <= maximum(cursorPosition[1])))||(bombs[x][y] == -1)){
			x = (x + 4) % n;
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
	position = { cursorPositionOld[0] * 4 + 3, cursorPositionOld[1] * 3 + 2 };
	SetConsoleCursorPosition(hConsole, position);
	cout << " ";
	position = { cursorPositionOld[0] * 4 + 2, cursorPositionOld[1] * 3 + 2 };
	SetConsoleCursorPosition(hConsole, position);
	cout << " ";
	position = { cursorPosition[0] * 4 + 3, cursorPosition[1] * 3 + 2 };
	SetConsoleCursorPosition(hConsole, position);
	cout << "|";
	position = { cursorPosition[0] * 4 + 2, cursorPosition[1] * 3 + 2 };
	SetConsoleCursorPosition(hConsole, position);
	cout << "_";
	SetConsoleCursorPosition(hConsole, { (short)n * 4+1, (short)n * 2 });

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
	cout << "Перемещение курсора <- ->; Поставить флаг \"NUMPAD5\"; Рискнуть \"SPACE\"";
	cout << "\nКоличество бомб = " << n_bombs;
}

bool checkWin() {
	bool result = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result = (bombs[i][j] == -1)||((bombs[i][j] != -1)&&(opened[i][j]));
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
	while (true) {
		//system("cls"); //очистить консоль
		SetConsoleTextAttribute(hConsole, 15); //Цвет текста - белый
		status = 0;
		for (int i = 0; i < 2; i++) {
			cursorPositionOld[i] = 0;
			cursorPosition[i] = 0;
		}
		cout << "Размер поля = n*n \nВведите n: ";
		cin >> n;
		bombs = new int* [n];
		opened = new bool* [n];
		flagged = new bool* [n];
		for (int i = 0; i < n; i++) {
			bombs[i] = new int[n];
			opened[i] = new bool[n];
			flagged[i] = new bool[n];
			for (int j = 0; j < n; j++) {
				bombs[i][j] = 0;
				opened[i][j] = false;
				flagged[i][j] = false;
			}
		}


		int endIn = 0;
		while (endIn == 0) {
			cout << "Выберите сложность:\n1-легкий уровень\n2-средний уровень\n3-сложный уровень\n";
			cin >> endIn;
			if ((endIn < 1) || (endIn > 3)) {
				cout << "Неверный ввод\n";
				endIn = 0;
			}
			switch (endIn) {
			case 1:
				n_bombs = n * n / 10;
				break;
			case 2:
				n_bombs = n * n / 8;
				break;
			case 3:
				n_bombs = n * n / 5;
				break;
			}
		}
		int gen = 0;

		

		system("cls"); //очистить консоль
		drawField();
		drawCursor();
		while (status == 0) {
			cursorPositionOld[0] = cursorPosition[0];
			cursorPositionOld[1] = cursorPosition[1];

			if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
				cursorPosition[0] = (cursorPosition[0] + n - 1) % n;
				drawCursor();
				Sleep(120);
			}
			else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
				cursorPosition[0] = (cursorPosition[0] + 1) % n;
				drawCursor();
				Sleep(120);
			}
			else if (GetAsyncKeyState(VK_UP) & 0x8000) {
				cursorPosition[1] = (cursorPosition[1] + n - 1) % n;
				drawCursor();
				Sleep(120);
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
				cursorPosition[1] = (cursorPosition[1] + 1) % n;
				drawCursor();
				Sleep(120);
			}
			else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
				if (gen == 0) {
					gen++;
					generate();
				}
				open(cursorPosition[0], cursorPosition[1]);
				Sleep(120);
			}
			else if ((GetAsyncKeyState(VK_NUMPAD5) & 0x8000) && (gen != 0)) {
				flag();
				Sleep(120);
			}
			if (checkWin()) {
				SetConsoleCursorPosition(hConsole, { 2, (short)n * 4 + 2 });
				SetConsoleTextAttribute(hConsole, 10); //Цвет текста - светло-зеленый
				status = 1;
				cout << "Победа!!! :)" << endl;
			}
		}
		for (int i = 0; i < n; i++) {
			delete[] bombs[i];
			delete[] opened[i];
			delete[] flagged[i];
		}
		delete[] bombs;
		delete[] opened;
		delete[] flagged;


		system("pause");
	}
}

