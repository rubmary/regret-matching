#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;

int main() {
	int N, M;
	cin >> N >> M;
	vector <vector <double>> A(N, vector <double>(M));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> A[i][j];

	vector <double> s1(N);
	vector <double> s2(M);

	for (int i = 0; i < N; i++)
		cin >> s1[i];
	for (int j = 0; j < M; j++)
		cin >> s2[j];

	double v1 = 1e100, v2 = -1e100;

	for (int j = 0; j < M; j++) {
		double v = 0;
		for (int i = 0; i < N; i++)
			v += A[i][j]*s1[i];
		v1 = min(v, v1);
	}

	for (int i = 0; i < N; i++) {
		double v = 0;
		for (int j = 0; j < M; j++)
			v += A[i][j]*s2[j];
		v2 = max(v2, v);
	}
	cout << fixed << setprecision(3) << v1 << ' ' << -v2 << endl;

	double u = 0;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			u += A[i][j]*s1[i]*s2[j];

	cout << u << endl;
	// cout << endl;
	// for (int i = 0; i < N; i++)
	// 	cout << s1[i] << ' ';
	// cout << endl;
	// for (int j = 0; j < M; j++)
	// 	cout << s2[j] << ' ';
	// cout << endl;
}