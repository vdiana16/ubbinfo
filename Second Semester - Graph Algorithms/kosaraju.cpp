#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
ifstream f("graf.txt");

const int nmax = 1001;
vector<int> graf[nmax];
vector<int> grafinv[nmax];
vector<int> noduri;
bool viz[nmax];

void dfs(int nod) {
	viz[nod] = true;
	for (int vecin : graf[nod]) {
		if (!viz[vecin]) {
			dfs(vecin);
		}
	}
	noduri.push_back(nod);
}

void dfs2(int nod, vector<int> &grup) {
	if (viz[nod]) {
		return;
	}
	grup.push_back(nod);
	viz[nod] = true;
	for (int vecin : grafinv[nod]) {
		if (!viz[vecin]) {
			dfs2(vecin, grup);
		}
	}
}

void alg_kosaraju(int n, vector <vector<int>> &grupuri) {
	for (int i = 0; i < n; i++) {
		if (!viz[i]) {
			dfs(i);
		}
	}
	for(int i = 0; i < n; i++) {
		viz[i] = false;
	}
	for (int i = noduri.size() - 1; i >= 0; i--) {
		if (!viz[noduri[i]]) {
			vector<int> grup;
			dfs2(noduri[i], grup);
			grupuri.push_back(grup);
		}
	}
}

int main()
{
	int n, m;
	f >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y;
		f >> x >> y;
		graf[x].push_back(y);
		grafinv[y].push_back(x);
	}

	vector <vector<int>> grupuri;
	alg_kosaraju(n, grupuri);
	for (int i = 0; i < grupuri.size(); i++) {
		cout << "grup" << i + 1 << ":";
		for (int nod : grupuri[i]) {
			cout << nod << " ";
		}
		cout << "\n";
	}
	return 0;
}