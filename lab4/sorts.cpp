#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;



template <typename it>
void bubbleSort(it l, it r) {
    bool s;
    for (size_t j = 1; j < r-l; ++j, s = 0) {
        for (it i = l; i < r-j; ++i) {
            if (*i > *(i+1)) {
                swap(*i, *(i+1));
                s = 1;
            }
        }
        if (!s) break;
    }
}


template <typename it>
void quickSort(it l, it r) {
    if (r-l < 2) return;
    auto p = *(l+(r-l)/2);
    it i = l, j = r-1;
    while (1) {
        while (*i < p) ++i;
        while (*j > p) --j;
        if (i < j) swap(*i++, *j--);
        else break;
    }
    quickSort(l, i);
    quickSort(i, r);
}



int main(int argc, char **argv) {

    if (argc < 2) return 0;

    fstream file("sorts.in");

    int n;
    file >> n;

    vector<int> vec(n);
    for (int i = 0; i < n; ++i) file >> vec[i];

    auto t0 = chrono::high_resolution_clock::now();
    switch (argv[1][0]) {
        case 'b':
            bubbleSort(vec.begin(), vec.end());
            break;
        case 'q':
            quickSort(vec.begin(), vec.end());
            break;
    }
    auto t1 = chrono::high_resolution_clock::now();

    auto ms = chrono::duration_cast<chrono::milliseconds> (t1-t0);
    cout << ms.count() << " ms" << endl;

    return !is_sorted(vec.begin(), vec.end());
}
