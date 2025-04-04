#include <iostream>
#include <fstream>
#include <climits>
#include <Color.Dlg>

#define INFINIT (INT_MAX/2 - 10000)

using namespace std;
ifstream f("labirint_1.txt");

//	3.Sa se scrie un program care gaseste o solutie pentru unul din umratoarele labirinturi: labirnit_1.txt,
//	labirint_2.txt,labirint_cuvinte.txt.
//	Aceasta este rezolvarea pentru labirintul 1 si labirintul 2

int a[501][501], n, m, istart, jstart, istop, jstop;
char s[501];

void bordare() {
	int i, j;
	for (i = 0; i <= n + 1; i++) {
		a[i][0] = -1;
		a[i][m + 1] = -1;
	}
	for (j = 0; j <= m + 1; j++) {
		a[0][j] = -1;
		a[n + 1][j] = -1;
	}
}

void Lee(int x, int y) {
	if (x == istop && y == jstop) {
		return;
	}
	if (a[x + 1][y] == 0 || a[x][y] + 1 < a[x + 1][y]) {
		a[x + 1][y] = a[x][y] + 1;
		Lee(x + 1, y);
	}
	if (a[x - 1][y] == 0 || a[x][y] + 1 < a[x - 1][y]) {
		a[x - 1][y] = a[x][y] + 1;
		Lee(x - 1, y);
	}
	if (a[x][y + 1] == 0 || a[x][y] + 1 < a[x][y + 1]) {
		a[x][y + 1] = a[x][y] + 1;
		Lee(x, y + 1);
	}
	if (a[x][y - 1] == 0 || a[x][y] + 1 < a[x][y - 1]) {
		a[x][y - 1] = a[x][y] + 1;
		Lee(x, y - 1);
	}
}

int main(){
	int x, y, i, j;
	while (f.getline(s, 501)) {
		n++;
		m = strlen(s);
		for (i = 0; i < m; i++) {
			if (s[i] == '1') {
				a[n][i + 1] = -1;
			}
			else if (s[i] == ' ') {
				a[n][i + 1] = 0;
			}
			else if (s[i] == 'S') {
				a[n][i + 1] = 1;
				istart = n;
				jstart = i + 1;
			}
			else {
				istop = n;
				jstop = i + 1;
			}
		}
	}
	bordare();
	Lee(istart, jstart);
	x = istop;
	y = jstop;
	while (x != istart || y != jstart) {
		if (a[x - 1][y] + 1 == a[x][y]) {
			a[x][y] = -2;
			x--;
		}
		else if (a[x + 1][y] + 1 == a[x][y]) {
			a[x][y] = -2;
			x++;
		}
		else if (a[x][y - 1] + 1 == a[x][y]) {
			a[x][y] = -2;
			y--;
		}
		else if (a[x][y + 1] + 1 == a[x][y]) {
			a[x][y] = - 2;
			y++;
		}
	}
	a[istop][jstop] = -3;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			if (a[i][j] == 1) {
				cout << "S";
			}
			else if (a[i][j] == -2) {
				cout << "X";
			}
			else if (a[i][j] == -3) {
				cout << "F";
			}
			else if (a[i][j] == -1) {
				cout << "1";
			}
			else {
				cout << " ";
			}
		}
		cout << "\n";
	}

	return 0;
}