#include "Node.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

Node::Node(ifstream &file) {
    file >> p >> information_set >> N;
    if (is_chance()) {
        pi = vector <double>(N);
        for (int i = 0; i < N; i++)
            file >> pi[i];
    }
    children = vector <Node*>(N);
    for (int i = 0; i < N; i++)
        children[i] = new Node(file);
    if (is_terminal())
        file >> utility;
}

bool Node::is_terminal() {
    return N == 0;
}

int Node::player() {
    return p;
}

bool Node::is_chance() {
    return player() == 0;
}

int Node::I() {
    return information_set;
}

int Node::num_children() {
    return N;
}

double Node::random() {
    return 1*((double)rand() / RAND_MAX);
}

int Node::action() {
    double cum = 0, x = random();
    for (int i = 0; i < num_children(); i++) {
        cum += pi[i];
        if (x < cum)
            return i;
    }
    return N-1;
}

Node* Node::child(int i) {
    return children[i];
}
void Node::print(int h, int &n) {
    for (int i = 0; i < h; i++)
        cout << "  ";
    cout << n << ". ";
    if (is_terminal())
        cout << "T, u = " << utility;
    else if(is_chance()){
        cout << "C";
    } else{
        cout << p << ", I = " << I();
    }
    cout << endl;
    for (int i = 0; i < num_children(); i++)
        child(i)-> print(h+1, ++n);
}

double Node::u(int i) {
    double sign = (i == 1) ? 1 : -1;
    return sign*utility;
}


void Node::set_strategy(vector <double> strategy) {
    pi = strategy;
}

double Node::probability(int i) {
    return pi[i];
}

double Node::util() {
    return utility;
}