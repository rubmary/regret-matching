#include <iostream>
#include <map>
#include <vector>
#include "Node.cpp"
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

void dfs_pi (	Node *u,
				int player,
				map <int, int> &id,
				vector <int> &s,
				int id_s,
				vector <double> &mix_s,
				vector <double> &pi,
				vector <vector <double>> &pi_a)
{
	if (u -> is_terminal())
		return;

	if (u -> player() == player) {
		int inf_set = u -> I();
		int id_child = s[id[inf_set]];
		Node *v = u -> child(id_child);
		pi[inf_set] += mix_s[id_s];
		pi_a[inf_set][id_child] += mix_s[id_s];
		dfs_pi(v, player, id, s, id_s, mix_s, pi, pi_a);
		return;
	}
	int N = u -> num_children();
	for (int i = 0; i < N; i++) {
		Node *v = u -> child(i);
		dfs_pi(v, player, id, s, id_s, mix_s, pi, pi_a);
	}
}

void get_strategy(	ifstream &file,
					vector <double> &sm1,
					vector <double> &sm2,
					int &N, int &M)
{

	file >> N >> M;
	sm1.resize(N);
	sm2.resize(M);
	for (int i = 0; i < N; i++)
		file >> sm1[i];
	for (int i = 0; i < M; i++)
		file >> sm2[i];
}

// N 	- numero de conjuntos de informacion del jugador 1
// N2 	- numero de conjuntos de informacion del jugador 2
// N 	- numero de estrategias puras del jugador 1
// M 	- numero de estrategias puras del jugador 2
// id1	- id de un conjunto de informacion del jugador 1
// id2  - id de un conjunto de informaciond del jugador 2
// s1   - estrategia pura utilizada por el jugador 1
// s2   - estrategia purta utilizada por el jugador 2
int main(int argc, char **argv) {
	ifstream file_tree(argv[1]);
	ifstream file_strategy(argv[2]);
	Node *root = new Node(file_tree);
	vector <double> sm1, sm2;
	int N, M;
	get_strategy(file_strategy, sm1, sm2, N, M);

	map <int, int> id1, id2;
	vector <int> num1, num2;
	int N1 = 0, N2 = 0;
	dfs(root, id1, id2, num1, num2, N1, N2);
	
	vector <int> s1(N1, 0), s2(N2, 0);
	vector <double> pi(N1 + N2, 0);
	vector <vector<double> > pi_actions(N1+N2);
	for (int i = 0; i < N1+N2; i++) {
		int A = 0;
		if (id2.find(i) == id2.end())
			A = num1[id1[i]];
		else
			A = num1[id2[i]];
		pi_actions[i] = vector <double>(A, 0);
	}

	for (int i = 0; i < N; i++) {
		dfs_pi(root, 1, id1, s1, i, sm1, pi, pi_actions);
		next(s1, num1, N1);
	}

	for (int i = 0; i < M; i++) {
		dfs_pi(root, 2, id2, s2, i, sm2, pi, pi_actions);
		next(s2, num2, N2);
	}

	cout << N1 + N2 << endl;
	for (int i = 0; i < N1 + N2; i++) {
		int T = pi_actions[i].size();
		cout << T << ' ';
		for (int j = 0; j < T; j++)
			cout << pi_actions[i][j]/pi[i] << ' ';
		cout << endl;
	}
}