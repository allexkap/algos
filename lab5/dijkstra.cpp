#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


int main() {
    ifstream file("dijkstra.in");

    int v, e, p;
    file >> v >> e >> p;

    vector<vector<int>> E(v, vector<int>(v, -1));
    vector<int> D(v, ~0U>>1);
    vector<int> V(v, 0);
    D[p] = 0;

    int i, j, k;
    for (int l = 0; l < e; ++l) {
        file >> i >> j >> k;
        E[i][j] = k;
        E[j][i] = k;
    }

    while (!V[p]++) {
        for (int i = 0; i < v; ++i)
            if (E[p][i] >= 0 && D[p] + E[p][i] < D[i])
                D[i] = D[p] + E[p][i];
        for (int i = 0; i < v; ++i)
            if (!V[i] && (V[p] || D[i] < D[p]))
                p = i;
    }

    for (auto &d: D)
        cout << d << ' ';
    cout << endl;

    return 0;
}
