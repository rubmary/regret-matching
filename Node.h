#include <vector>
#include <fstream>
using namespace std;

/**
    Class Node
    @p:                 player
    @information_set:   dimension el vector de entrada
    @N:                 numero de hijos
    @pi:                distribucion de probabilidad para un nodo de azar
    @children:          hijos del nodo
    @utility:           ganancia del jugador 1 si el nodo es terminal
 */
class Node {
    int p;
    int information_set;
    int N;
    vector <double> pi;
    vector <Node*> children;
    double utility;

public:
    /**
        Node:
        constructor de la clase
     */
    Node(ifstream &file);

    /**
        I - conjunto de informacion
        @return conjuto de informacion del nodo actual
     */
    int I();

    /**
        num_children - numero de hijos
        @return numero de hijos del nodo actual
     */
    int num_children();


    /**
        random
        @return numero aleatorio en [0, 1]
     */
    double random();

    /**
        action
        si el nodo es un nodo de azar, elegi
        una accion segun su distribucion de
        probabilidad

        @return accion escogida
     */
    int action();

    /**
        child
        devuelve un apuntador al k-esimo hijo del
        nodo actual

        parametros
        @k: indice del hijo buscado

        @return k-esimo hijo
     */
    Node* child(int k);

    /**
        child
        verifica si el nodo actual es terminal o no

        @return true sii el nodo es terminal
     */
    bool is_terminal();

    /**
        is_chance
        verifica si el nodo actual es un nodo
        de azar o no

        @return true sii el nodo es de azar
     */
    bool is_chance();

    /**
        player
        retorna el jugador del nodo

        @return id del jugador
     */
    int player();

    /**
        print
        imprime el nodo actual y sus hijos

        parametros
        @h: profundidad del nodo
        @n: id del nodo
     */
    void print(int h, int &n);

    /**
        u
        utilidad de un jugador si es un nodo terminal

        parametros
        @i: jugador

        @return: utilididad del i-esimo jugador
     */
    double u(int i);

    /**
        set_strategy
        establece la estrategia al nodo

        parametros
        @strategy:  estrategia para el nodo

     */
    void set_strategy(vector <double> strategy);

    double probability(int i);
};
