#include <vector>
using namespace std;

class RegretMatching {
    
    void set(vector < vector <double> > &utility);

    double get_random();

    int get_action( vector <double> &strategy,
                    int num_actions);
    
    void normalize_strategy(    vector <double> &strategy,
                                int num_actions);

    double get_parameter(   vector <vector <double> > &utility,
                            int S1,
                            int S2);

    void get_strategy(  vector < vector <double> > &regret,
                        vector <double> &strategy,
                        int num_actions,
                        double m,
                        int prev,
                        int iteration);

    void get_strategy(  vector < vector <double> > &regret,
                        vector <double> &strategy,
                        int num_actions,
                        int iteration);

    void get_strategy(  vector <double> &regret,
                        vector <double> &strategy,
                        int num_actions);


    void unconditional_regret(  int i, int j, vector <vector <double>> &utility);

    void conditional_regret(  int i, int j, vector <vector <double>> &utility);

    double print_max_regret(  int t, ofstream &file);

    void update_strategies(int a1, int a2);

    int S1, S2;                                     // numero de acciones de cada jugador
    vector < vector <double> > regret1, regret2;    // regret condicional acumulado
    vector <double> un_regret1, un_regret2;         // regret incondicional acumulado
    vector <double> strategy1, strategy2;           // estrategia de la iteraccion respectiva
    vector <double> s1, s2;

public:
    double proc_a(  vector<vector <double> > &utility,
                    int &iterations,
                    string name,
                    double eps);

    double proc_b(  vector<vector <double> > &utility,
                    int &iterations,
                    string name,
                    double eps);

    double proc_c(  vector<vector <double> > &utility,
                    int &iterations,
                    string name,
                    double eps);

    vector <double> get_strategy(int player) {
        if (player == 1)
            return s1;
        return s2;
    }
};