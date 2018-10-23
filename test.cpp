#include <iostream>
#include <iomanip>
#include "RegretMatching.cpp"
using namespace std;

void print_strategy(RegretMatching &regret_matching, int S1, int S2) {
    vector <double> s1, s2;
    s1 = regret_matching.get_strategy(1);
    s2 = regret_matching.get_strategy(2);
    for (int i = 0; i < S1; i++)
        cout << fixed << setprecision(3) << s1[i] << ' ';
    cout << endl;
    for (int i = 0; i < S2; i++)
        cout << fixed << setprecision(3) << s2[i] << ' ';
    cout << endl;
}

int main() {
    vector <vector <double>> A;
    int S1, S2;
    cin >> S1 >> S2;
    A = vector <vector <double> >(S1, vector <double>(S2));
    for (int i = 0; i < S1; i++)
        for (int j = 0; j < S2; j++)
            cin >> A[i][j];

    RegretMatching regret_matching;
    
    cout << "Procedimiento A:" << endl;
    regret_matching.proc_a(A, 10000);
    print_strategy(regret_matching, S1, S2);
    cout << endl;

    cout << "Procedimiento B:" << endl;
    regret_matching.proc_b(A, 10000);
    print_strategy(regret_matching, S1, S2);
    cout << endl;

    cout << "Procedimiento C:" << endl;
    regret_matching.proc_c(A, 10000);
    print_strategy(regret_matching, S1, S2);
    cout << endl;
}