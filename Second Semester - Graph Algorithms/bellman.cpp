#include <iostream>
#include <fstream>
#define inf 999

using namespace std;
ifstream f("graf.txt");

// vector pt stocarea distantelor minime de la sursa la fiecare nod
int d[1005];

struct bellman {
	int x, y, c; //sursa dest si cost
}muchie[10005];

void relax(int u, int v, int c) {
	if (d[v] > d[u] + c) {
		d[v] = d[u] + c;
	}
}

bool bellman_ford(int n, int v, int s) {
	for (int i = 1; i <= n; i++) {
		d[i] = inf;
	}
	d[s] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= v; j++) {
			relax(muchie[j].x, muchie[j].y, muchie[j].c);
		}
	}
	for (int j = 1; j <= v; j++) {
		//Daca distanta catre nodul destinatie al unei muchii poate fi redus
		// mai mult decat prin intermediul nodului sursa al acelei muchii, atunci
		//exista ciclu negativ
		if (d[muchie[j].y] > d[muchie[j].x] + muchie[j].c)
			return false;
	}
	return true;
}

int main()
{
	int x, y, c;
	int nr_noduri = 0;
	int nr_muchii = 0;
	while (f >> x >> y >> c) {
		nr_muchii++;
		muchie[nr_muchii].x = x;
		muchie[nr_muchii].y = y;
		muchie[nr_muchii].c = c;

		if (nr_noduri < x) {
			nr_noduri = x;
		}
		if(nr_noduri < y) {
			nr_noduri = y;
		}
	}
	int sursa;
	cout << "Introduceti nodul sursa: ";
	cin >> sursa;
	if (!bellman_ford(nr_noduri, nr_muchii, sursa))
		cout << "ciclu negativ";
	else {
		for (int i = 1; i <= nr_noduri; i++) {
			if (d[i] == inf) {
				cout << "inf";
			}
			else {
				cout << d[i] << " ";
			}
		}
	}
	f.close();
	return 0;
}
