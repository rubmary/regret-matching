#include <iostream>
#include <vector>
using namespace std;

bool next(vector <int> &P, int N, int S) {
    for (int i = N-1; i > 0; i--) {
        if (P[i] > 0){
            P[i-1]++;
            P[N-1] = P[i] - 1;
            if (i < N-1) P[i] = 0;
            return true;
        }
    }
    return false;
}
int match(vector <int> P1, vector <int> P2, int N) {
    int p1 = 0, p2 = 0;

    for (int i = 0; i < N; i++) {
        if (P1[i] > P2[i])
            p1++;
        if (P2[i] > P1[i])
            p2++;
    }
    return p1 - p2;
}
int com(int n, int m) {
    int ans = 1;
    for (int k = 0; k < m; k++)
        ans *= (n-k);
    for (int k = 1; k <= m; k++)
        ans /= k;
    return ans;
}
int main() {
    int N, S;
    cin >> N >> S;
    int M = com(S + N -1, N-1);
    cout << M << ' ' << M << endl;
    vector <int> P1(N, 0), P2(N, 0);
    P1[N-1] = S;
    while (true) {
        P2[0]   = 0;
        P2[N-1] = S;
        while (true) {
            cout << match(P1, P2, N) << ' ';
            if (!next(P2, N, S))
                break;
        }
        cout << endl;
        if (!next(P1, N, S))
            break;
    }
}