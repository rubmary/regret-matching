#include "Node.cpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;


bool next(	vector <int> &strategy,
			vector <int> &actions,
			int N )
{
	for (int i = N-1; i >= 0; i--) {
		if (strategy[i] < actions[i]-1) {
			strategy[i]++;
			return true;
		}
		strategy[i] = 0;
	}
	return false;
}

void dfs(	Node *u,
			map <int, int>	&id1,
			map <int, int>	&id2,
			vector <int>	&num1,
			vector <int>	&num2,
			int &N1, int &N2)
{
	if (u -> is_terminal())
		return;

	int N, p, I;
	p = u -> player();
	N = u -> num_children();
	I = u -> I();
	if (p == 1 && id1.find(I) == id1.end()) {
		id1[I] = N1++;
		num1.push_back(N);
	}
	if (p == 2 && id2.find(I) == id2.end()) {
		id2[I] = N2++;
		num2.push_back(N);
	}
	for (int i = 0; i < N; i++)
		dfs(u->child(i), id1, id2, num1, num2, N1, N2);
}

double expected(	Node *u,
					map <int, int> &id1,
					map <int, int> &id2,
					vector <int> &s1,
					vector <int> &s2 )
{
	if (u -> is_terminal())
		return u -> util();

	if (u -> is_chance()) {
		double ans = 0;
		int N = u -> num_children();
		for (int i = 0; i < N; i++) {
			Node *v  = u->child(i);
			double e = expected(v, id1, id2, s1, s2);
			double p = u->probability(i);
			ans += e*p;
		}
		return ans;
	}

	int player  = u -> player();
	int inf_set = u -> I();
	Node *v;
	if (player==1)
		v = u->child(s1[id1[inf_set]]);
	else
		v = u->child(s2[id2[inf_set]]);
	return expected(v, id1, id2, s1, s2);
}

int main(int argc, char **argv)
{
	ifstream file(argv[1]);
	Node *root = new Node(file);
	map <int, int> id1, id2;
	vector <int> num1, num2;
	int N1 = 0, N2 = 0;
	dfs(root, id1, id2, num1, num2, N1, N2);
	vector <int> s1(N1, 0), s2(N2, 0);
	int k = 0;

	int N = 1, M = 1;
	for (int i = 0; i < N1; i++)
		N *= num1[i];
	for (int i = 0; i < N2; i++)
		M *= num2[i];

	cout << N << ' ' << M << endl;
	while (true) {
		while (true) {
			double val = expected(root, id1, id2, s1, s2);
			cout <<  val << ' ';
			if (!next(s2, num2, N2))
				break;
		}
		cout << endl;
		if (!next(s1, num1, N1))
			break;
	}
}