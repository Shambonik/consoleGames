#include <iostream>

using namespace std;

int main()
{
	while (true) {
		setlocale(0, "");
		short n;
		cout << "Введите n (ширина и длина): ";
		cin >> n;
		int** array = new int* [n];
		int** game = new int* [n];
		int r = 1;
		for (short i = 0; i < n; i++) {
			array[i] = new int[n];
			game[i] = new int[n];
			for (short j = 0; j < n; j++) {
				array[i][j] = i * n + j;
				game[i][j] = i * n + j;
			}
		}

		short i0 = 0;
		short j0 = 0;
		short i = 0;
		short j = 0;
		bool sw = true;
		while (sw) {
			for (int l = 0; l < n * n; l++) {
				bool sw2 = true;
				while (sw2) {
					i = i0;
					j = j0;
					short z = rand() % 4;
					switch (z) {
					case 0:
						i = i0 - 1;
						sw = false;
						break;
					case 1:
						i = i0 + 1;
						sw = false;
						break;
					case 2:
						j = j0 - 1;
						sw = false;
						break;
					case 3:
						j = j0 + 1;
						sw = false;
						break;
					}
					if ((i >= 0) && (j >= 0) && (i < n) && (j < n)) {
						sw2 = false;
					}
				}
				short x = game[i][j];
				game[i][j] = game[i0][j0];
				game[i0][j0] = x;
				i0 = i;
				j0 = j;
			}
			sw = false;
			for (short i = 0; i < n; i++) {
				for (short j = 0; j < n; j++) {
					if (game[i][j] == array[i][j]) {
						sw = true;
					}
				}
			}
		}

		bool result = true;
		cout << "Для конца игры пустая ячейка должна стоять в левом верхнем углу!\n";
		cout << "0 - пустая ячейка\n";
		while (result) {
			for (short i = 0; i < n; i++) {
				for (short j = 0; j < n; j++) {
					cout << game[i][j];
					if (game[i][j] > 99) {
						cout << " ";
					}
					else if (game[i][j] > 9) {
						cout << "  ";
					}
					else {
						cout << "   ";
					}
				}
				cout << endl;
			}

			sw = true;
			while (sw) {
				cout << "Введите строку и столбец ненулевой ячейки через пробел (нумераци с 1) : ";
				cin >> i0 >> j0;
				i0--;
				j0--;
				if ((i0 >= 0) && (j0 >= 0) && (i0 < n) && (j0 < n) && (game[i0][j0] != 0)) {
					sw = false;
				}
				else {
					cout << "Неверный ввод\n";
				}
			}
			cout << "Выбранное число: " << game[i0][j0] << endl;
			i = i0;
			j = j0;
			sw = true;
			bool izm = false;
			while (sw) {
				cout << "Действие:\n1-наверх\n2-вниз\n3-влево\n4-вправо\n5-изменить ячейку\n";
				short z = 0;
				cin >> z;
				switch (z) {
				case 1:
					i = i0 - 1;
					sw = false;
					break;
				case 2:
					i = i0 + 1;
					sw = false;
					break;
				case 3:
					j = j0 - 1;
					sw = false;
					break;
				case 4:
					j = j0 + 1;
					sw = false;
					break;
				case 5:
					izm = true;
					sw = false;
					break;
				default:
					cout << "Неверный ввод\n";
					break;
				}
			}
			if (!izm) {
				if ((i >= 0) && (j >= 0) && (i < n) && (j < n) && (game[i][j] == 0)) {
					game[i][j] = game[i0][j0];
					game[i0][j0] = 0;
					result = false;
					for (short i = 0; i < n; i++) {
						for (short j = 0; j < n; j++) {
							if (game[i][j] != array[i][j]) {
								result = true;
							}
						}
					}
				}
				else {
					cout << "Действие невозможно\n";
				}
			}
		}
		cout << "Победа!\n";
	}

}
