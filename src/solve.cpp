#include <iostream>
#include <fstream>
#include <iomanip>
#include "RegretMatching.cpp"
#define REP 10
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

void print_time(vector <double> &times,
                vector <int> &iterations,
                string path)
{
    ofstream file(path.c_str());
    int T = times.size();
    double sum_t = 0, sum_i = 0;
    file << T << endl;
    for (int i = 0; i < T; i++){
        file << times[i] << ' ' << iterations[i] << endl;
        sum_t += times[i];
        sum_i += iterations[i];
    }
    file << fixed << setprecision(3) << sum_t/T << ' ' << sum_i/T << endl;
}

int main(int argc, char **argv) {

    double eps = stod(argv[2]);
    string path_input, path_output, path_strategy, path_time;

    string name = argv[1];
    path_input  = "../juegos/forma_normal/" + name + ".txt";

    path_output = "../regret/" + name + "/procedimiento- ";
    int position = path_output.size() - 1;
    path_output = path_output + ".txt";

    path_strategy = "../estrategias/mixtas/" + name + "/procedimiento- ";
    int pos_strategy = path_strategy.size() - 1;
    path_strategy = path_strategy + ".txt";

    path_time = "../tiempos/" + name + "/procedimiento- ";
    int pos_time = path_time.size() - 1;
    path_time = path_time + ".txt";

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
    vector <double> times;
    vector <int> its;
    double time;
    int iterations;

    cout << "Procedimiento A del juego " << argv[1] << endl;
    path_output[position] = 'A';
    path_strategy[pos_strategy] = 'A';
    path_time[pos_time] = 'A';
    times.clear();
    its.clear();
    iterations = 0;
    for (int i = 0; i < REP; i++){
        time = regret_matching.proc_a(A, iterations, path_output, eps);
        times.push_back(time);
        its.push_back(iterations);
    }
    print_strategy(regret_matching, path_strategy, S1, S2);
    print_time(times, its, path_time);

    cout << "Procedimiento B del juego " << argv[1] << endl;
    path_output[position] = 'B';
    path_strategy[pos_strategy] = 'B';
    path_time[pos_time] = 'B';
    times.clear();
    its.clear();
    iterations = 0;
    for (int i = 0; i < REP; i++){
        time = regret_matching.proc_b(A, iterations, path_output, eps);
        times.push_back(time);
        its.push_back(iterations);
    }
    print_strategy(regret_matching, path_strategy, S1, S2);
    print_time(times, its, path_time);

    cout << "Procedimiento C del juego " << argv[1] << endl;
    path_output[position] = 'C';
    path_strategy[pos_strategy] = 'C';
    path_time[pos_time] = 'C';
    times.clear();
    its.clear();
    iterations = 0;
    for (int i = 0; i < REP; i++) {
        time = regret_matching.proc_c(A, iterations, path_output, eps);
        times.push_back(time);
        its.push_back(iterations);
    }

    print_strategy(regret_matching, path_strategy, S1, S2);
    print_time(times, its, path_time);
}