#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;



template <typename it>
void bubbleSort(it l, it r) {
    bool swapped;
    for (size_t j = 1; j < r-l; ++j, swapped = false) {
        for (it i = l; i < r-j; ++i) {
            if (*i > *(i+1)) {
                swap(*i, *(i+1));
                swapped = true;
            }
        }
        if (!swapped) break;
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


template <typename it>
void heapify(it l, it r, it i) {
    while (1) {
        it m = i, c = l + 2*(i-l);
        if (c+1 < r && *(c+1) > *m) m = c+1;
        if (c+2 < r && *(c+2) > *m) m = c+2;
        if (m == i) break;
        swap(*i, *m);
        i = m;
    }
}

template <typename it>
void heapSort(it l, it r) {
    for (it i = l + (r-l-1)/2; i > l; --i)
        heapify(l, r, i);
    for (; r-l >= 2; --r) {
        heapify(l, r, l);
        swap(*l, *(r-1));
    }
}


template <typename it>
void combSort(it l, it r, double shrink=1.3) {
    size_t gap = r-l;
    bool swapped = true;
    while (swapped) {
        if (gap > 1)
            gap /= shrink;
        else
            swapped = false;
        for (it i = l; i < r-gap; ++i) {
            if (*i > *(i+gap)) {
                swap(*i, *(i+gap));
                swapped = true;
            }
        }
    }
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
        case 'h':
            heapSort(vec.begin(), vec.end());
            break;
        case 'c':
            combSort(vec.begin(), vec.end());
            break;
    }
    auto t1 = chrono::high_resolution_clock::now();

    auto dt = chrono::duration_cast<chrono::microseconds> (t1-t0);
    cout << dt.count() << " µs" << endl;

    return !is_sorted(vec.begin(), vec.end());
}
