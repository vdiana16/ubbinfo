#include <iostream> 
#include <fstream>

using namespace std;

#define INF 1000

int dist[1001];

struct bellman {
	int x, y, c;
}muchii[1001];

void relax(int i, int j, int c) {
	if (dist[j] > dist[i] + c) {
		dist[j] = dist[i] + c;
	}
}

bool bellman_ford(int v, int e, int s) {
	int i, j;
	for (i = 0; i < v; i++) {
		dist[i] = INF;
	}
	dist[s] = 0;
	for (i = 0; i < v; i++) {
		for (j = 1; j <= e; j++) {
			relax(muchii[j].x, muchii[j].y, muchii[j].c);
		}
	}
	for (j = 1; j <= e; j++) {
		if (dist[muchii[j].y] > dist[muchii[j].x] + muchii[j].c) {
			return false;
		}
	}
	return true;
}

int main(int argc, char  *argv[]) {
	int i;
	int v, e, s;

	if (argc < 3) {
		cout << "Prea putine argumente...";
		return 0;
	}

	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);

	in >> v >> e >> s;
	for (i = 1; i <= e; i++) {
		in >> muchii[i].x >> muchii[i].y >> muchii[i].c;
	}

	if (bellman_ford(v, e, s)) {
		for (i = 0; i < v; i++) {
			if (dist[i] == INF) {
				out << "INF" <<" ";
			}
			else {
				out << dist[i] << " ";
			}
		}
	}
	in.close();
	out.close();
	return 0;
}