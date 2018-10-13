#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
#define EPS 1e-6

double get_random() {
    return rand() / ((double) RAND_MAX);
}

int get_action(vector <double> &strategy, int T) {
    double r = get_random();
    T = strategy.size();
    int action = 0;
    double cumulative_probability = 0;
    while (action < T - 1) {
        cumulative_probability += strategy[action];
        if (r < cumulative_probability)
            break;
        action++;
    }
    return action;
}

void get_strategy(vector <double> &regret, vector <double> &strategy, int T) {
    double total_regret = 0;
    for (int k = 0; k < T; k++)
        total_regret += max(0.0, regret[k]);
    for (int k = 0; k < T; k++) {
        strategy[k] = max(0.0, regret[k]);
        if (total_regret < EPS)
            strategy[k] = 1/T;
        else
            strategy[k] /= total_regret;
    }
}

void normalize_strategy(vector <double> &strategy, int T) {
    double cumulative = 0;
    for (int k = 0; k < T; k++)
        cumulative += strategy[k];
    for (int k = 0; k < T; k++)
        strategy[k] /= cumulative;
}

void proc_c(    vector<vector <double>> &utility,   // matriz de pagos
                vector <double> &s1,                // vector de estrategias del jugador 1
                vector <double> &s2,                // vector de estrategias del jugador 2
                int iterations)                     // numero de iteraciones
{
    int S1 = utility.size(), S2 = utility[0].size();    // numero de acciones de cada jugador
    vector <double> cumulative_regret1(S1, 0);          // regret acumulado del jugador 1
    vector <double> cumulative_regret2(S2, 0);          // regret acumulado del jugador 2
    vector <double> strategy1(S1), strategy2(S2);       // estrategia de la iteraccion respectiva
    s1.resize(S1, 0), s2.resize(S2, 0);                 // inicializar los vectores estrategias

    for (int t = 0; t < iterations; t++) {
        get_strategy(cumulative_regret1, strategy1, S1);    // estrategia del jugador 1
        get_strategy(cumulative_regret2, strategy2, S2);    // estrategia del jugador 2
        int i = get_action(strategy1, S1);                  // accion del jugador 1
        int j = get_action(strategy2, S2);                  // accion del jugador 2

        // Actualizar los regrets acumulados
        for (int k = 0; k < S1; k++)
            cumulative_regret1[k] +=  utility[k][j] - utility[i][j];
        for (int k = 0; k < S2; k++)
            cumulative_regret2[k] += -utility[i][k] + utility[i][j];

        // Actualizar las estrategias acumuladas
        for (int k = 0; k < S1; k++)
            s1[k] += strategy1[k];
        for (int k = 0; k < S2; k++)
            s2[k] += strategy2[k];
    }
    normalize_strategy(s1, S1);                             // normalizar estrategia jugador 1
    normalize_strategy(s2, S2);                             // normalizar estrategia jugador 2
}

int main() {
    vector <vector <double>> A;
    int S1, S2;
    cin >> S1 >> S2;
    A = vector <vector <double> >(S1, vector <double>(S2));
    for (int i = 0; i < S1; i++)
        for (int j = 0; j < S2; j++)
            cin >> A[i][j];
    vector <double> s1, s2;
    proc_c(A, s1, s2, 1000000);
    for (int i = 0; i < S1; i++)
        cout << fixed << setprecision(3) << s1[i] << ' ';
    cout << endl;
    for (int i = 0; i < S2; i++)
        cout << fixed << setprecision(3) << s2[i] << ' ';
    cout << endl;
}