#include <iostream>
#include <map>
#include <string>
using namespace std;

int I = 0;
map <string, int> set_inf;

int c1, c2;

bool is_terminal(string h) {
    int len = h.size();
    if (len < 2)
        return false;
    if (h[len-1] == h[len-2])
        return true;
    if(h[len-1] == 'p' && h[len-2] == 'b')
        return true;
    return false;
}

int player(string h) {
    int len = h.size();
    return (len&1) ? 1 : 0; 
}

int information_set(string h) {
    string mycard = to_string(player(h) == 0 ? c1 : c2);
    string information = h + mycard;
    if(set_inf.find(information) == set_inf.end())
        set_inf[information] = I++;
    return set_inf[information];
}

int u(string h, int b1, int b2) {
    int winner;
    int len = h.size(); 
    if(h[len-1] == 'p' && h[len-2] == 'b')
        winner = player(h);
    else
        winner = c1 > c2 ? 0 : 1;
    return !winner ? b2 : -b1;
}

void dfs(string h, int b1, int b2) { 
    if (is_terminal(h)) {
        cout << "-1 -1 0 " << u(h, b1, b2) << endl;
        return;
    }
    cout << player(h)+1 << " " << information_set(h) << " 2" << endl;
    dfs(h + "p", b1, b2);
    if (player(h) == 0)
        dfs(h + "b", b1+1, b2);
    else
        dfs(h + "b", b1, b2+1);
}

int main() {
    cout << 0 << " -1 6 " ;
    for (int i = 0; i < 6; i++)
        cout << 1.00/6 << ' ';
    cout << endl;
    for (c1 = 1; c1 < 4; c1++) {
        for (c2 = 1; c2 < 4; c2++) {
            if (c1 == c2)
                continue;
            dfs("", 1, 1);
        }
    }
}
