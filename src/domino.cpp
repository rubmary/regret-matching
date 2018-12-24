#include <iostream>
#include <vector>
using namespace std;

int R = 2, C = 3;
int  x[] = {0, 1, 0, 1, 0, 0, 0};
int  y[] = {0, 0, 1, 1, 0, 1, 2};
int dx[] = {0, 0, 0, 0, 1, 1, 1};
int dy[] = {1, 1, 1, 1, 0, 0, 0};

int fx(int k)
{
	return k/C;
}

int fy(int k)
{
	return k%C;
}

bool domino(int k, int i, int j)
{
	if (x[k] == i && y[k] == j)
		return true;

	if (x[k]+dx[k] == i && y[k]+dy[k] == j)
		return true;

	return false;
}

bool ficha(int k, int i, int j)
{
	if (fx(k) == i && fy(k) == j)
		return true;
	return false;
}

int match (int i, int j) {
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++)
			if (domino(i, r, c) && ficha(j, r, c))
				return -1;
	}
	return 1;
}

int N = 7, M = 6;
int main() {
	cout << N << ' ' << M << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << match(i, j) << ' ';
		}
		cout << endl;
	}
}