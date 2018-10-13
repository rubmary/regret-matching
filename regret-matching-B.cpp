#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;
#define EPS 1e-6

double get_random()
{
    return rand() / ((double) RAND_MAX);
}

int get_action(vector <double> &strategy, int T)
{
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

void normalize_strategy(vector <double> &strategy, int T) {
    double cumulative = 0;
    for (int k = 0; k < T; k++)
        cumulative += strategy[k];
    for (int k = 0; k < T; k++)
        strategy[k] /= cumulative; 
}

void get_strategy(  vector < vector <double> > &regret,
                    vector <double> &strategy,
                    int num_actions,
                    int iteration)
{
    MatrixXd R(num_actions, num_actions);
    for (int i = 0; i < num_actions; i++) {
        for (int j = 0; j < num_actions; j++) {
            R(i, j) = max(0.0, regret[j][i]);
            R(i, j) /= iteration;
        }
    }

    for (int i = 0; i < num_actions; i++) {
        for (int j = 0; j < num_actions; j++){
            if (j == i)
                continue;
            R(i, i) -= R(j,i);
        }
    }

    FullPivLU<MatrixXd> lu = R.fullPivLu();
    int rank = lu.rank();
    if (!rank) {
        strategy = vector <double>(num_actions, 1);
        normalize_strategy(strategy, num_actions);
        return;
    }
    MatrixXd z = lu.kernel();
    for (int i = 0; i < num_actions; i++)
        strategy[i] = z(i, 0);
    normalize_strategy(strategy, num_actions);
}

void proc_b(    vector<vector <double>> &utility,   // matriz de pagos
                vector <double> &s1,                // vector de estrategias del jugador 1
                vector <double> &s2,                // vector de estrategias del jugador 2
                int iterations)                     // numero de iteraciones
{
    int S1 = utility.size(), S2 = utility[0].size();    // numero de acciones de cada jugador
    vector < vector <double> > cum_regret1;             // regret acumulado del jugador 1
    vector < vector <double> > cum_regret2;             // regret acumulado del jugador 2
    vector <double> strategy1(S1), strategy2(S2);       // estrategia de la iteraccion respectiva
    s1.resize(S1, 0), s2.resize(S2, 0);                 // inicializar los vectores estrategias
    cum_regret1.resize(S1, vector <double> (S1, 0));
    cum_regret2.resize(S2, vector <double> (S2, 0));    

    int prev1 = 0, prev2 = 0;
    for (int t = 0; t < iterations; t++) {
        get_strategy(cum_regret1, strategy1, S1, t+1);  // estrategia del jugador 1
        get_strategy(cum_regret2, strategy2, S2, t+1);  // estrategia del jugador 2
        int i = get_action(strategy1, S1);              // accion del jugador 1
        int j = get_action(strategy2, S2);              // accion del jugador 2

        // Actualizar los regrets acumulados
        for (int k = 0; k < S1; k++)
            cum_regret1[i][k] +=  utility[k][j] - utility[i][j];
        for (int k = 0; k < S2; k++)
            cum_regret2[j][k] += -utility[i][k] + utility[i][j];

        // Actualizar las estrategias acumuladas
        for (int k = 0; k < S1; k++)
            s1[k] += strategy1[k];
        for (int k = 0; k < S2; k++)
            s2[k] += strategy2[k];

        // Actualizar las estrategias previas
        prev1 = i;
        prev2 = j;
    }
    normalize_strategy(s1, S1);                             // normalizar estrategia jugador 1
    normalize_strategy(s2, S2);                             // normalizar estrategia jugador 2
}

int main()
{
    vector <vector <double>> A;
    int S1, S2;
    cin >> S1 >> S2;
    A = vector <vector <double> >(S1, vector <double>(S2));
    for (int i = 0; i < S1; i++)
        for (int j = 0; j < S2; j++)
            cin >> A[i][j];
    vector <double> s1, s2;
    proc_b(A, s1, s2, 1000000);
    for (int i = 0; i < S1; i++)
        cout << fixed << setprecision(3) << s1[i] << ' ';
    cout << endl;
    for (int i = 0; i < S2; i++)
        cout << fixed << setprecision(3) << s2[i] << ' ';
    cout << endl;
}