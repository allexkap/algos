#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    fstream file("gauss.in");

    int n, m;
    file >> n >> m;

    vector<vector<float>> Matrix(n, vector<float>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            file >> Matrix[i][j];
        }
    }

    float factor;
    for (int k = 0; k < n; ++k) {
        for (int i = k+1; i < n; ++i) {
            factor = Matrix[i][k] / Matrix[k][k];
            for (int j = k; j < m; ++j) {
                Matrix[i][j] -= factor * Matrix[k][j];
            }
        }
    }

    for (int i = n-1; i >= 0; --i) {
        for (int j = i+1; j < n; ++j) {
            Matrix[i][m-1] -= Matrix[j][m-1] * Matrix[i][j];
        }
        Matrix[i][m-1] /= Matrix[i][i];
    }

    for (int i = 0; i < n; ++i) {
        if (Matrix[i][m-1] != Matrix[i][m-1]) {
            cout << "No Solution" << endl;
            return 0;
        }
    }

    cout << "Solution: ";
    for (int i = 0; i < n; ++i) {
        cout << Matrix[i][m-1] << ' ';
    }
    cout << endl;

    return 0;
}
