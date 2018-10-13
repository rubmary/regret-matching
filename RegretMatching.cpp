#include "RegretMatching.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include <Eigen/Dense>
#define EPS 1e-6
using namespace Eigen;
using namespace std;


void RegretMatching::set(vector < vector <double> > &utility)
{
    S1 = utility.size();
    S2 = utility[0].size();
    s1.resize(S1, 0);
    s2.resize(S2, 0);
    regret1.resize(S1, vector <double> (S1, 0));
    regret2.resize(S2, vector <double> (S2, 0));
    un_regret1.resize(S1, 0);
    un_regret1.resize(S2, 0);
}
double RegretMatching::get_random()
{
    return rand() / ((double) RAND_MAX);
}

int RegretMatching::get_action( vector <double> &strategy,
                                int num_actions)
{
    double r = get_random();
    num_actions = strategy.size();
    int action = 0;
    double cumulative_probability = 0;
    while (action < num_actions - 1) {
        cumulative_probability += strategy[action];
        if (r < cumulative_probability)
            break;
        action++;
    }
    return action;
}

void RegretMatching::normalize_strategy(    vector <double> &strategy,
                                            int num_actions)
{
    double cumulative = 0;
    for (int k = 0; k < num_actions; k++)
        cumulative += strategy[k];
    for (int k = 0; k < num_actions; k++)
        strategy[k] /= cumulative; 
}

double RegretMatching::get_parameter(   vector <vector <double> > &utility,
                                        int S1,
                                        int S2)
{
    double M1 = 0, M2 = 0;
    for (int i = 0; i < S1; i++){
        for (int j = 0; j < S2; j++){
            M1 = max(M1,  utility[i][j]);
            M2 = max(M2, -utility[i][j]);
        }
    }
    return 2*max(M1*(S1-1), M2*(S2-1)) + 0.001;
}

void RegretMatching::get_strategy(  vector < vector <double> > &regret,
                                    vector <double> &strategy,
                                    int num_actions,
                                    double m,
                                    int prev,
                                    int iteration)
{
    for (int k = 0; k < num_actions; k++) {
        if (k == prev)
            continue;
        strategy[k] = max(0.0, regret[prev][k])/iteration;
        strategy[k] /= m;
    }
    strategy[prev] = 1;
    for (int k = 0; k < num_actions; k++) {
        if (k == prev)
            continue;
        strategy[prev] -= strategy[k];
    }
}

void RegretMatching::get_strategy(  vector < vector <double> > &regret,
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

void RegretMatching::get_strategy(  vector <double> &regret,
                                    vector <double> &strategy,
                                    int num_actions )
{
    double total_regret = 0;
    for (int k = 0; k < num_actions; k++)
        total_regret += max(0.0, regret[k]);
    for (int k = 0; k < num_actions; k++) {
        strategy[k] = max(0.0, regret[k]);
        if (total_regret < EPS)
            strategy[k] = 1/num_actions;
        else
            strategy[k] /= total_regret;
    }
}

void RegretMatching::proc_a(    vector<vector <double>> &utility,
                                int iterations)
{
    set(utility);
    double m = get_parameter(utility, S1, S2);
    int prev1 = 0, prev2 = 0;
    for (int t = 0; t < iterations; t++) {
        get_strategy(regret1, strategy1, S1, m, prev1, t+1);    // estrategia del jugador 1
        get_strategy(regret2, strategy2, S2, m, prev2, t+1);    // estrategia del jugador 2
        int i = get_action(strategy1, S1);                      // accion del jugador 1
        int j = get_action(strategy2, S2);                      // accion del jugador 2

        // Actualizar los regrets acumulados
        for (int k = 0; k < S1; k++)
            regret1[i][k] +=  utility[k][j] - utility[i][j];
        for (int k = 0; k < S2; k++)
            regret2[j][k] += -utility[i][k] + utility[i][j];

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

void RegretMatching::proc_b(    vector<vector <double>> &utility,
                                int iterations)
{
    set(utility);
    for (int t = 0; t < iterations; t++) {
        get_strategy(regret1, strategy1, S1, t+1);  // estrategia del jugador 1
        get_strategy(regret2, strategy2, S2, t+1);  // estrategia del jugador 2
        int i = get_action(strategy1, S1);              // accion del jugador 1
        int j = get_action(strategy2, S2);              // accion del jugador 2

        // Actualizar los regrets acumulados
        for (int k = 0; k < S1; k++)
            regret1[i][k] +=  utility[k][j] - utility[i][j];
        for (int k = 0; k < S2; k++)
            regret2[j][k] += -utility[i][k] + utility[i][j];

        // Actualizar las estrategias acumuladas
        for (int k = 0; k < S1; k++)
            s1[k] += strategy1[k];
        for (int k = 0; k < S2; k++)
            s2[k] += strategy2[k];
    }
    normalize_strategy(s1, S1);                             // normalizar estrategia jugador 1
    normalize_strategy(s2, S2);                             // normalizar estrategia jugador 2
}

void RegretMatching::proc_c(    vector<vector <double>> &utility,
                                int iterations)
{
    set(utility);
    for (int t = 0; t < iterations; t++) {
        get_strategy(un_regret1, strategy1, S1);    // estrategia del jugador 1
        get_strategy(un_regret2, strategy2, S2);    // estrategia del jugador 2
        int i = get_action(strategy1, S1);                  // accion del jugador 1
        int j = get_action(strategy2, S2);                  // accion del jugador 2

        // Actualizar los regrets acumulados
        for (int k = 0; k < S1; k++)
            un_regret1[k] +=  utility[k][j] - utility[i][j];
        for (int k = 0; k < S2; k++)
            un_regret2[k] += -utility[i][k] + utility[i][j];

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

}