#include <vector>
#include <climits>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

string proc(string x) {
    return "procedimiento-" + x + ".txt";
}

int main(int argc, char **argv) {
    string game_name, matrix_path, strategy_path;
    game_name = argv[1];
    matrix_path = "../juegos/forma_normal/" + game_name + ".txt";
    strategy_path = "../estrategias/mixtas/" + game_name + "/";

    ifstream matrix_file(matrix_path.c_str());

    int N, M;
    matrix_file >> N >> M;
    vector <vector <double>> A(N, vector <double>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrix_file >> A[i][j];
    matrix_file.close();

    vector <double> s1(N);
    vector <double> s2(M);
    vector <string> procs({"A", "B", "C"});

    for (int i = 0; i < 3; i++) {
        string name_file = strategy_path + proc(procs[i]);
        ifstream file(name_file.c_str());
        file >> N >> M;
        for (int i = 0; i < N; i++)
            file >> s1[i];
        for (int j = 0; j < M; j++)
            file >> s2[j];
        file.close();

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
        cout << "Procedimiento " + procs[i] + ": v1 v2 = ";
        cout << fixed << setprecision(3) << v1 << ' ' << -v2 << endl;
    }

    double u = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            u += A[i][j]*s1[i]*s2[j];
    cout << "u = " << u << endl;
}