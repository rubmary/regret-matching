#include "RegretMatching.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <chrono>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;


void RegretMatching::set(vector < vector <double> > &utility)
{
    S1 = utility.size();
    S2 = utility[0].size();
    s1 = vector <double>(S1, 0);
    s2 = vector <double>(S2, 0);
    strategy1 = vector <double> (S1, 0);
    strategy2 = vector <double> (S1, 0);
    regret1 = vector <vector <double> > (S1, vector <double> (S1, 0));
    regret2 = vector <vector <double> > (S2, vector <double> (S2, 0));
    un_regret1 = vector <double>(S1, 0);
    un_regret2 = vector <double>(S2, 0);
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
        if (total_regret < 1e-4)
            strategy[k] = 1/num_actions;
        else
            strategy[k] /= total_regret;
    }
}

void RegretMatching::unconditional_regret(  int i,
                                            int j,
                                            vector <vector <double>> &utility)
{
    for (int k = 0; k < S1; k++)
        un_regret1[k] +=  utility[k][j] - utility[i][j];
    for (int k = 0; k < S2; k++)
        un_regret2[k] += -utility[i][k] + utility[i][j];
}

void RegretMatching::conditional_regret(    int i,
                                            int j,
                                            vector <vector <double>> &utility)
{
    for (int k = 0; k < S1; k++)
        regret1[i][k] +=  utility[k][j] - utility[i][j];
    for (int k = 0; k < S2; k++)
        regret2[j][k] += -utility[i][k] + utility[i][j];
}

double RegretMatching::print_max_regret ( int t,
                                        ofstream &file)
{
    double max_regret1 = 0;
    double max_regret2 = 0;
    for (int k = 0; k < S1; k++)
        max_regret1 = max(max_regret1, un_regret1[k]);
    for (int k = 0; k < S2; k++)
        max_regret2 = max(max_regret2, un_regret2[k]);

    file << max_regret1/(t+1) << ' ' << max_regret2/(t+1) << endl;

    return max(max_regret1/(t+1), max_regret2/(t+1));
}

void RegretMatching::update_strategies(int i, int j)
{
    s1[i] += 1;
    s2[j] += 1;
}

double RegretMatching::proc_a(  vector<vector <double>> &utility,
                                int &iterations,
                                string name = "regret_a.txt",
                                double eps = 1e-4)
{
    set(utility);
    double m = get_parameter(utility, S1, S2);
    ofstream file(name.c_str());

    auto start = chrono::system_clock::now();
    int prev1 = 0, prev2 = 0;
    for (int t = 0; t < iterations; t++) {
        get_strategy(regret1, strategy1, S1, m, prev1, t+1);    // estrategia del jugador 1
        get_strategy(regret2, strategy2, S2, m, prev2, t+1);    // estrategia del jugador 2
        int i = get_action(strategy1, S1);                      // accion del jugador 1
        int j = get_action(strategy2, S2);                      // accion del jugador 2
        conditional_regret(i, j, utility);                      // regret condicional
        update_strategies(i, j);                                // actualizar las estrategias acumuladas
        prev1 = i;                                              // estrategia previa jugador 1
        prev2 = j;                                              // estrategia previa jugador 2
        unconditional_regret(i, j, utility);                    // regret incondicional
        double max_regret = print_max_regret(t, file);          // imprimir regret en archivo
        if (max_regret < eps){
            iterations = ++t;
            break;
        }
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;

    normalize_strategy(s1, S1);                             // normalizar estrategia jugador 1
    normalize_strategy(s2, S2);                             // normalizar estrategia jugador 2
    file.close();
    return elapsed_seconds.count();
}

double RegretMatching::proc_b(  vector<vector <double>> &utility,
                                int &iterations,
                                string name = "regret_b.txt",
                                double eps = 1e-4)
{
    set(utility);
    ofstream file(name.c_str());

    auto start = chrono::system_clock::now();
    for (int t = 0; t < iterations; t++) {
        get_strategy(regret1, strategy1, S1, t+1);      // estrategia del jugador 1
        get_strategy(regret2, strategy2, S2, t+1);      // estrategia del jugador 2
        int i = get_action(strategy1, S1);              // accion del jugador 1
        int j = get_action(strategy2, S2);              // accion del jugador 2
        conditional_regret(i, j, utility);              // regret condicional
        update_strategies(i, j);                        // actualizar las estrategias acumuladas
        unconditional_regret(i, j, utility);            // regret incondicional
        double max_regret = print_max_regret(t, file);  // imprimir regret en archivo
        if (max_regret < eps){
            iterations = ++t;
            break;
        }
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;

    normalize_strategy(s1, S1);                         // normalizar estrategia jugador 1
    normalize_strategy(s2, S2);                         // normalizar estrategia jugador 2
    file.close();
    return elapsed_seconds.count();
}

double RegretMatching::proc_c(  vector<vector <double>> &utility,
                                int &iterations,
                                string name = "regret_c.txt",
                                double eps = 1e-4)
{
    set(utility);
    ofstream file(name.c_str());

    auto start = chrono::system_clock::now();
    for (int t = 0; t < iterations; t++) {
        get_strategy(un_regret1, strategy1, S1);            // estrategia del jugador 1
        get_strategy(un_regret2, strategy2, S2);            // estrategia del jugador 2
        int i = get_action(strategy1, S1);                  // accion del jugador 1
        int j = get_action(strategy2, S2);                  // accion del jugador 2
        unconditional_regret(i, j, utility);                // actualizar regret incondicional
        update_strategies(i, j);                            // actualizar estrategias acumuladas
        double max_regret = print_max_regret(t, file);      // imprimir regret en archivo
        if (max_regret < eps){
            iterations = ++t;
            break;
        }
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;

    normalize_strategy(s1, S1);                             // normalizar estrategia jugador 1
    normalize_strategy(s2, S2);                             // normalizar estrategia jugador 2
    file.close();
    return elapsed_seconds.count();
}