#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <map>
#include <string>

using namespace std;

class Graf {
private:
	ifstream fin;
	ofstream fout;
public:
	void codarePrufer();
	void DecodarePrufer();
	void CodareHuffman();
	void DecodareHuffman();
	void ArboreMinimAcoperire();
	Graf(string in, string out) :
		fin{ in }, fout{ out } {}
	~Graf() {
		fin.close();
		fout.close();
	}

};

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "Invalid syntax!\n";
		return 1;
	}
	Graf G{ argv[2], argv[3] };
	switch (atoi(argv[1])) {
	case 1:
		G.codarePrufer();
		break;
	case 2:
		G.DecodarePrufer();
		break;
	case 3:
		G.CodareHuffman();
		break;
	case 4:
		G.DecodareHuffman();
		break;
	case 5:
		G.ArboreMinimAcoperire();
		break;
	default:
		cout << "Aceasta problema nu exista!";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}



void Graf::codarePrufer() {
	int n;
	fin >> n;

	int* deg = new int[n] {}; 
	for (int i = 0; i < n; ++i) {
		deg[i] = 0;
	}
	int* pi = new int[n] {}; 
	set<int> frunze; 

	for (int i = 0; i < n; ++i) {
		fin >> pi[i];
		deg[i]++;
		pi[i] != -1 ? deg[pi[i]]++ : 0;
	}

	for (int i = 0; i < n; ++i) {
		if (deg[i] == 1 && pi[i] != -1) {
			frunze.insert(i);
		}
	}

	int* coduri = new int[n - 1] {}; 

	for (int i = 0; i < n - 1; ++i) {
		int frunzamin = *(frunze.begin()); 
		frunze.erase(frunze.begin()); 

		int frunzaminimaP = pi[frunzamin]; 

		coduri[i] = frunzaminimaP;
		deg[frunzamin]--;
		deg[frunzaminimaP]--;

		if (pi[frunzaminimaP] != -1 && deg[frunzaminimaP] == 1) { 
			frunze.insert(frunzaminimaP);
		}
	}

	fout << n - 1 << "\n";
	for (int i = 0; i < n - 1; ++i) {
		fout << coduri[i] << " ";
	}
	delete[] deg;
	delete[] pi;
	delete[] coduri;
}

void Graf::DecodarePrufer() {
	int n;
	fin >> n;
	int* deg = new int[n + 1] {};
	int* pi = new int[n + 1] {};

	set<int> frunze;
	for (int i = 0; i < n + 1; ++i) {
		frunze.insert(i);
	}

	list<int> coduri;
	for (int i = 0; i < n; ++i) {
		int x;
		fin >> x;
		coduri.push_back(x);
		++deg[x];
		frunze.erase(x);
	}

	for (int i = 0; i < n; ++i) {
		int frunzaminima = *frunze.begin();
		frunze.erase(frunze.begin());
		int frunzaminimaP = coduri.front();

		pi[frunzaminima] = frunzaminimaP;
		deg[frunzaminimaP]--;
		if (deg[frunzaminimaP] == 0) {
			frunze.insert(frunzaminimaP);
		}
		coduri.pop_front();
	}

	pi[*frunze.begin()] = -1; 

	fout << n + 1 << "\n";
	for (int i = 0; i < n + 1; ++i) {
		fout << pi[i] << " ";
	}

	delete[] deg;
	delete[] pi;
}

void Graf::CodareHuffman() {
	struct FrecvPerechi {
		int frecv = 0;
		char chr = 0;
		bool operator<(const FrecvPerechi& oth) const {
			return frecv < oth.frecv || (frecv == oth.frecv && chr < oth.chr);
		}
	};

	string text;
	getline(fin, text);

	if (text == "") {
		return;
	}

	int fr[256]{};
	int litere = 0;

	for (char chr : text) {
		fr[int(chr)]++;
		fr[int(chr)] == 1 ? litere++ : 0;
	}

	multimap<FrecvPerechi, string> Q;

	fout << litere << "\n";
	for (int i = 0; i < 256; ++i) {
		if (fr[i]) {
			fout << char(i) << " " << fr[i] << "\n";
			Q.insert({ { fr[i], char(i) }, string(1, i) });
		}
	}

	string coduri[256];
	while (--litere) {
		auto x = *Q.begin();
		for (char chr : x.second) {
			coduri[int(chr)] = "0" + coduri[int(chr)];
		}
		Q.erase(Q.begin());

		auto y = *Q.begin();
		for (char chr : y.second) {
			coduri[int(chr)] = "1" + coduri[int(chr)];
		}
		Q.erase(Q.begin());

		Q.insert({ { x.first.frecv + y.first.frecv, min(x.first.chr, y.first.chr) }, x.second + y.second });
	}

	for (char chr : text) {
		fout << coduri[int(chr)];
	}
}

void Graf::DecodareHuffman() {
	struct FrecvPerechi {
		int frecv = 0;
		char chr = 0;
		bool operator<(const FrecvPerechi& oth) const {
			return frecv < oth.frecv || (frecv == oth.frecv && chr < oth.chr);
		}
	};

	multimap <FrecvPerechi, string> Q;

	int litere, fr[256]{};
	string line;

	getline(fin, line);
	litere = stoi(line);

	for (int i = 0; i < litere; ++i) {
		getline(fin, line);
		char chr = line[0];
		fr[int(chr)] = stoi(line.substr(2));
		Q.insert({ {fr[int(chr)], chr }, string(1, chr) });
	}

	string codificat;
	getline(fin, codificat);

	string text;
	map<string, char> coduri;

	string code[256]{};
	while (--litere) {
		auto x = *Q.begin();
		for (auto chr : x.second) {
			code[int(chr)] = "0" + code[int(chr)];
		}
		Q.erase(Q.begin());

		auto y = *Q.begin();
		for (auto chr : y.second) {
			code[int(chr)] = "1" + code[int(chr)];
		}
		Q.erase(Q.begin());

		Q.insert({ { x.first.frecv + y.first.frecv, min(x.first.chr, y.first.chr) }, x.second + y.second });
	}

	for (int i = 0; i < 256; ++i) {
		if (code[i] != "\0") {
			coduri.insert({ code[i], i });
		}
	}

	int ultimul = 0, lg = 0;
	string anterior, ch;

	while (coduri.size() > 1) {
		string aux = codificat.substr(ultimul, lg);
		lg++;
		auto srch = coduri.find(aux);
		if (srch != coduri.end()) {
			anterior = aux;
			ch = srch->second;
		}
		else if (srch == coduri.end() && anterior != "\0") {
			text.append(ch);
			fr[int(ch[0])]--;

			if (fr[int(ch[0])] == 0) {
				coduri.erase(anterior);
			}

			ultimul += anterior.size();
			lg = 0;
			anterior = "\0";
			ch = "\0";
		}
	}

	if (coduri.size() == 1) {
		text.append(string(1, coduri.begin()->second));
	}

	fout << text;
}

void Graf::ArboreMinimAcoperire() {
	const int INF = 1e7 + 5;
	int V, E, radacina = 0;
	fin >> V >> E; // vertices and edges
	vector<pair<int, int>>* adj = new vector<pair<int, int>>[V];
	for (int i = 0; i < E; ++i) {
		int x, y, w;
		fin >> x >> y >> w;
		adj[x].push_back({ y, w });
		adj[y].push_back({ x, w });
		// cout << x << " " << y << " " << w << "\n";
	}

	int edges = -1;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;

	vector<int> key(V);
	vector<int> pi(V);
	vector<bool> viz(V);

	for (int i = 0; i < V; ++i) {
		key[i] = INF;
		pi[i] = -1;
		viz[i] = false;
	}

	Q.push({ 0, radacina });
	key[radacina] = 0;

	while (!Q.empty()) {
		int crt = Q.top().second;
		Q.pop();
		if (viz[crt]) {
			continue;
		}
		viz[crt] = true;
		edges++;

		for (auto x : adj[crt]) {
			int y = x.first;
			int w = x.second;
			if (key[y] > w && !viz[y]) {
				key[y] = w;
				Q.push({ w, y });
				pi[y] = crt;
			}
		}
	}

	int lgmin = 0;
	for (int i = 0; i < V; ++i) {
		lgmin += key[i];
	}

	fout << lgmin << "\n" << edges << "\n";

	map<int, vector<int>> ans;

	for (int i = 0; i < V; ++i) {
		if (viz[i] && i != radacina) {
			if (i < pi[i]) {
				ans[i].push_back(pi[i]);
			}
			else {
				ans[pi[i]].push_back(i);
			}
		}
	}
	for (int i = 0; i < V; ++i) {
		sort(ans[i].begin(), ans[i].end());
		for (auto j : ans[i]) {
			fout << i << " " << j << "\n";
		}
	}
}