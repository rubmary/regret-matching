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
        file << fixed << setprecision(3) << s1[i] << ' ';
    file << endl;
    for (int i = 0; i < S2; i++)
        file << fixed << setprecision(3) << s2[i] << ' ';
    file << endl;
    file.close();
}

int main(int argc, char **argv) {
    string path_input, path_output, path_strategy;
    path_input  = argv[1];
    path_input  = "../juegos/forma_normal/" + path_input + ".txt";

    path_output = argv[1];
    path_output = "../regret/" + path_output + "/procedimiento- "; 
    int position = path_output.size() - 1;
    path_output = path_output + ".txt";

    path_strategy = argv[1];
    path_strategy = "../estrategias/mixtas/" + path_strategy + "/procedimiento- ";
    int pos_strategy = path_strategy.size() - 1;
    path_strategy = path_strategy + ".txt";

    ifstream file(path_input.c_str());
    vector <vector <double>> A;
    int S1, S2;
    file >> S1 >> S2;
    A = vector <vector <double> >(S1, vector <double>(S2));
    for (int i = 0; i < S1; i++)
        for (int j = 0; j < S2; j++)
            file >> A[i][j];
    file.close();

    RegretMatching regret_matching;
    
    cout << "Procedimiento A del juego " << argv[1] << endl;
    path_output[position] = 'A';
    path_strategy[pos_strategy] = 'A';
    regret_matching.proc_a(A, 1000000, path_output);
    print_strategy(regret_matching, path_strategy, S1, S2);

    cout << "Procedimiento B del juego " << argv[1] << endl;
    path_output[position] = 'B';
    path_strategy[pos_strategy] = 'B';
    regret_matching.proc_b(A, 100000, path_output);
    print_strategy(regret_matching, path_strategy, S1, S2);

    cout << "Procedimiento C del juego " << argv[1] << endl;
    path_output[position] = 'C';
    path_strategy[pos_strategy] = 'C';
    regret_matching.proc_c(A, 1000000, path_output);
    print_strategy(regret_matching, path_strategy, S1, S2);
}