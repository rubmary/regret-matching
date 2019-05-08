#include <iostream>
#include <fstream>
#include <iomanip>
#include "RegretMatching.cpp"
using namespace std;


void print_strategy(RegretMatching &regret_matching, 
                    string path, 
                    int S1,
                    int S2)
{
    ofstream file(path.c_str());
    vector <double> s1, s2;
    s1 = regret_matching.get_strategy(1);
    s2 = regret_matching.get_strategy(2);
    file << S1 << ' ' << S2 << endl;
    for (int i = 0; i < S1; i++)
        file << fixed << setprecision(4) << s1[i] << ' ';
    file << endl;
    for (int i = 0; i < S2; i++)
        file << fixed << setprecision(4) << s2[i] << ' ';
    file << endl;
    file.close();
}

int main(int argc, char **argv) {
    srand(time(NULL));
    string path_regret = argv[1];
    double eps = stod(argv[2]);
    ifstream file("../juegos/forma_normal/tree_kuhn.txt");
    vector <vector <double>> A;
    int S1, S2;
    file >> S1 >> S2;
    A = vector <vector <double> >(S1, vector <double>(S2));
    for (int i = 0; i < S1; i++)
        for (int j = 0; j < S2; j++)
            file >> A[i][j];

    RegretMatching regret_matching;
    int iterations = 0;
    string path = "../regret/kuhn/procedimiento-C.txt";
    double time = regret_matching.proc_c(A, iterations, path, eps);
    print_strategy(regret_matching, path_regret, S1, S2);
    cout << "time = " << time << endl;
    cout << "iterations = " << iterations << endl;
}