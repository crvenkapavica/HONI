//HONI 2020, 1.kolo - Patkice (3)

#include <iostream>
using namespace std;

int dX[4] = { 0, 1, 0, -1 };
int dY[4] = { 1, 0, -1, 0 };

char map[100][100];
int moves[100][100] = { 0 };

int R, S;
const int INF = INT_MAX / 2;

char start;
char mindir;
int minmoves = INF;

void reset_moves();

void BFS(int x, int y, int korak) {

	if (x < 0 || x > R || y < 0 || y > S) return; 
	if (map[x][y] == '.') return;
	if (moves[x][y] && moves[x][y] < korak) return;
	if (map[x][y] == 'x') {
		if (korak < minmoves) {
			minmoves = korak;
			mindir = start;
		}
		return;
	}

	moves[x][y] = korak;

	if (!korak) {
		for (int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				start = 'E'; break;
			case 1:
				start = 'S'; break;
			case 2:
				start = 'W'; break;
			case 3:
				start = 'N'; break;
			}
			BFS(x + dX[i], y + dY[i], korak + 1);
			reset_moves();
		}
	}

	if (map[x][y] == '^') {
		BFS(x - 1, y, korak + 1);
	}
	if (map[x][y] == 'v') {
		BFS(x + 1, y, korak + 1);
	}
	if (map[x][y] == '>') {
		BFS(x, y + 1, korak + 1);
	}
	if (map[x][y] == '<') {
		BFS(x, y - 1, korak + 1);
	}
}

void reset_moves() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < S; j++)
			moves[i][j] = 0;
}

int main() {

	int tX = 0, tY = 0;
	cin >> R >> S;

	for (int i = 0; i < R; i++)
		for (int j = 0; j < S; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'o') { tX = i; tY = j; }
		}

	BFS(tX, tY, 0);

	if (minmoves < INF) {
		cout << ":)" << endl << mindir;
	}
	else cout << ":(";
}
