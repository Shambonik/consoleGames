#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

bool figure[4][4];
bool sledFigure[4][4];
int schet = 0;
bool fo[4][4] = { {true, true, false, false}, {true, true, false, false}, { false, false, false, false}, { false, false, false, false} };
bool fi[4][4] = { {true, false, false, false}, {true, false, false, false}, { true, false, false, false}, { true, false, false, false} };
bool fz[4][4] = { {true, true, false, false}, {false, true, true, false}, { false, false, false, false}, { false, false, false, false} };
bool fs[4][4] = { {false, true, true, false}, {true, true, false, false}, { false, false, false, false}, { false, false, false, false} };
bool fj[4][4] = { {false, true, false, false}, {false, true, false, false}, { true, true, false, false}, { false, false, false, false} };
bool fl[4][4] = { {true, false, false, false}, {true, false, false, false}, { true, true, false, false}, { false, false, false, false} };
bool ft[4][4] = { {true, true, true, false}, {false, true, false, false}, {false, false, false, false}, { false, false, false, false} };

string vivesti0[20][20];

short yFigure(bool pole[22][22], short y, short x) {
	bool stop = false;
	while (!stop) {
		y += 1;
		for (int i = 0; i < 4; i++) {
			for (int z = 0; z < 4; z++) {
				if (figure[i][z]) {
					if (pole[i + y][z + x]) {
						stop = true;
					}
				}
			}
		}
	}
	return y;
}

void drawField() {
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (short i = 0; i < 20; i++) {
		position = { 20, i };
		SetConsoleCursorPosition(hConsole, position);
		cout << "|";
	}
	position = { 0, 20 };
	SetConsoleCursorPosition(hConsole, position);
	for (short i = 1; i < 21; i++) {
		cout << ">";
	}
}

void vivod(bool pole[22][22], short y, short x) {
	short y2 = yFigure(pole, y, x) - 1;
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (short i = 1; i < 21; i++) {
		for (short z = 1; z < 21; z++) {
			position = { z - 1 , i - 1 };
			if ((pole[i][z])||((z-x>=0)&&(z-x<=3)&&(i - y >= 0)&&(i - y <= 3)&&(figure[i-y][z-x]))) {
				if (vivesti0[i - 1][z - 1] != "@") {
					vivesti0[i - 1][z - 1] = "@";
					SetConsoleCursorPosition(hConsole, position);
					cout << "@";
				}
			}
			else {
				if ((z - x >= 0) && (z - x <= 3) && (i - y2 >= 0) && (i - y2 <= 3) && (figure[i - y2][z - x])) {
					if (vivesti0[i - 1][z - 1] != "+") {
						vivesti0[i - 1][z - 1] = "+";
						SetConsoleCursorPosition(hConsole, position);
						cout << "+";
					}
				}
				else {
					if (vivesti0[i - 1][z - 1] != " ") {
						vivesti0[i - 1][z - 1] = " ";
						SetConsoleCursorPosition(hConsole, position);
						cout << " ";
					}
				}
			}
		}
	}
	position = { 0 , 21 };
	SetConsoleCursorPosition(hConsole, position);
	cout << endl << "Следующая фигура:       Счёт: " << schet << endl;;
	for (int i = 0; i < 4; i++) {
		for (int z = 0; z < 4; z++) {
			if (sledFigure[i][z]) {
				cout << "@";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl << x;
}

bool proverka(bool pole[22][22], short y, short x, short chY, short chX) {
	bool result = true;
	for (int i = 0; i < 4; i++) {
		for (int z = 0; z < 4; z++) {
			if (figure[i][z]) {
				if (pole[i + y + chY][z + x + chX]) {
					result = false;
				}
			}
		}
	}
	return result;
}

bool stolb4(bool fig[4][4]) {
	bool result = false;
	for (int i = 0; i < 4; i++) {
		if (fig[i][3]) {
			result = true;
		}
	}
	return result;
}




short minX(bool fig[4][4]) {
	short min = 4;
	for (int i = 0; i < 4; i++) {
		for (int z = 0; z < 4; z++) {
			if (fig[i][z]) {
				if (z < min) {
					min = z;
				}
				break;
			}
		}
	}
	return min;
}

short minY(bool fig[4][4]) {
	short min = 4;
	for (int i = 0; i < 4; i++) {
		for (int z = 0; z < 4; z++) {
			if (fig[i][z]) {
				min = i;
				break;
			}
		}
		if (min < 4) break;
	}
	return min;
}

void left() {
	for (int l = 0; l < 4; l++) {
		for (int r = 0; r < 3; r++) {
			figure[l][r] = figure[l][r + 1];
		}
	}
	for (int l = 0; l < 4; l++) {
		figure[l][3] = false;
	}
}

void right() {
	for (int l = 0; l < 4; l++) {
		for (int r = 3; r > 0; r--) {
			figure[l][r] = figure[l][r - 1];
		}
	}
	for (int l = 0; l < 4; l++) {
		figure[l][0] = false;
	}
}

void up() {
	for (int l = 0; l < 3; l++) {
		for (int r = 0; r < 4; r++) {
			figure[l][r] = figure[l + 1][r];
		}
	}
	for (int l = 0; l < 4; l++) {
		figure[3][l] = false;
	}
}

void leftSled() {
	for (int l = 0; l < 4; l++) {
		for (int r = 0; r < 3; r++) {
			sledFigure[l][r] = sledFigure[l][r + 1];
		}
	}
	for (int l = 0; l < 4; l++) {
		sledFigure[l][3] = false;
	}
}

void rightSled() {
	for (int l = 0; l < 4; l++) {
		for (int r = 3; r > 0; r--) {
			sledFigure[l][r] = sledFigure[l][r - 1];
		}
	}
	for (int l = 0; l < 4; l++) {
		sledFigure[l][0] = false;
	}
}

void upSled() {
	for (int l = 0; l < 3; l++) {
		for (int r = 0; r < 4; r++) {
			sledFigure[l][r] = sledFigure[l + 1][r];
		}
	}
	for (int l = 0; l < 4; l++) {
		sledFigure[3][l] = false;
	}
}

void naznachSledFigure(bool f[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int z = 0; z < 4; z++) {
			sledFigure[i][z] = f[i][z];
		}
	}
}

void naznachFigure() {
	for (int i = 0; i < 4; i++) {
		for (int z = 0; z < 4; z++) {
			figure[i][z] = sledFigure[i][z];
		}
	}
}

void povorot() {
	bool figPovorot[4][4];
	short mx = minX(figure);
	for (int i = 0; i < 4; i++) {
		for (int z = 0; z < 4; z++) {
			figPovorot[z][3 - i] = figure[i][z];
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int z = 0; z < 4; z++) {
			figure[i][z] = figPovorot[i][z];
		}
	}

	while (minX(figure) != mx) {
		if (minX(figure) < mx) {
			if (!stolb4(figure)) {
				right();
			}
			else {
				break;
			}
		}
		else {
			left();
		}

	}

	while (minY(figure) > 0) {
		up();
	}
}

void povorotSled() {
	bool figPovorot[4][4];
	short mx = minX(sledFigure);
	for (int i = 0; i < 4; i++) {
		for (int z = 0; z < 4; z++) {
			figPovorot[z][3 - i] = sledFigure[i][z];
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int z = 0; z < 4; z++) {
			sledFigure[i][z] = figPovorot[i][z];
		}
	}

	while (minX(sledFigure) != mx) {
		if (minX(sledFigure) < mx) {
			if (!stolb4(sledFigure)) {
				rightSled();
			}
			else {
				break;
			}
		}
		else {
			leftSled();
		}

	}

	while (minY(sledFigure) > 0) {
		upSled();
	}
}

void randSled() {
	int randFigure = rand() % 7;
	int maxPovorot = 0;
	int maxSmeschenie = 0;
	switch (randFigure) {
	case 0:
		naznachSledFigure(fo); //0
		maxSmeschenie = 2;
		maxPovorot = 1;
		break;
	case 1:
		naznachSledFigure(fi); //I
		maxSmeschenie = 3;
		maxPovorot = 2;
		break;
	case 2:
		naznachSledFigure(fz); //Z
		maxSmeschenie = 1;
		maxPovorot = 2;
		break;
	case 3:
		naznachSledFigure(fs); //S
		maxSmeschenie = 1;
		maxPovorot = 2;
		break;
	case 4:
		naznachSledFigure(fj); //J
		maxSmeschenie = 2;
		maxPovorot = 4;
		break;
	case 5:
		naznachSledFigure(fl); //L
		maxSmeschenie = 2;
		maxPovorot = 4;
		break;
	case 6:
		naznachSledFigure(ft); //T
		maxSmeschenie = 1;
		maxPovorot = 4;
		break;
	}
	randFigure = (rand() * clock()) % maxSmeschenie;
	for (int i = 0; i < randFigure; i++) {
		rightSled();
	}
	randFigure = (rand() * clock()) % maxPovorot;
	for (int i = 0; i < randFigure; i++) {
		povorotSled();
	}
}

int main(){
	srand(time(nullptr));
	setlocale(LC_CTYPE, "Russian");
	bool pole[22][22];
	for (int i = 1; i < 21; i++) {
		pole[i][0] = true;
		for (int z = 1; z < 21; z++) {
			pole[i][z] = false;
		}
		pole[i][21] = true;
	}

	for (int z = 1; z < 21; z++) {
		pole[21][z] = true;
		pole[0][z] = true;
	}

	short x = 0;
	short y = 0;
	bool stop = false;
	bool gameover = false;
	drawField();
	randSled();
	while (!gameover) {
		naznachFigure();
		randSled();
		x = abs((rand()*clock())%16)+1;
		y = 0;
		stop = false;
		while (!stop) {
			y += 1;
			int start = clock();
			int end = clock();
			int period = 1000;
			vivod(pole, y, x);
			while (end - start < period) {
				if (GetAsyncKeyState(VK_LEFT)) {
					if (proverka(pole, y, x, 0, -1)) {
						if (x == 1) {
							left();
						}
						else {
							x--;
						}
						vivod(pole, y, x);
					}
				}
				else if (GetAsyncKeyState(VK_RIGHT)) {
					if (proverka(pole, y, x, 0, 1)){
						if (x == 17) {
							right();
						}
						else {
							x++;
						}
						vivod(pole, y, x);
					}
				}

				else if (GetAsyncKeyState(VK_UP)) {
					povorot();
					vivod(pole, y, x);
				}
				Sleep(80);
				stop = !(proverka(pole, y, x, 1, 0));
				if (stop) {
					break;
				}
				if (GetAsyncKeyState(VK_DOWN)) {
					period = 200;
				}
				else {
					period = 800;
				}

				end = clock();
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int z = 0; z < 4; z++) {
				if (figure[i][z]) {
					pole[i + y][z + x] = true;
				}
			}
		}
		for (int i = 1; i < 21; i++) {
			bool obnul = true;
			for (int z = 1; z < 21; z++) {
				if (!pole[i][z]) {
					obnul = false;
					break;
				}
			}
			if (obnul) {
				schet += 1;
				for (int k = i; k > 1; k--) {
					for (int z = 1; z < 21; z++) {
						pole[k][z] = pole[k-1][z];
					}
				}
				for (int z = 1; z < 21; z++) {
					pole[1][z] = false;
				}
			}
		}
		for (int i = 1; i < 21; i++) {
			if (pole[1][i]) {
				gameover = true;
			}
		}
	}
	cout << "\n\n\n\n\n\n\n\n\nКОНЕЦ ИГРЫ\n\nВАШ СЧЁТ: " << schet;
	cin >> x;
}

