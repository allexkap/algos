#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include "counter.cpp"
using namespace std;



template <typename it>
void gnomeSort(it l, it r) {
    for (it i = l; i < r; )
        if (i == l || *(i-1) <= *i) ++i;
        else counter::swap(*(i-1), *i), --i;
}


template <typename it>
void bubbleSort(it l, it r) {
    bool swapped;
    for (size_t j = 1; j < r-l; ++j, swapped = false) {
        for (it i = l; i < r-j; ++i) {
            if (*i > *(i+1)) {
                counter::swap(*i, *(i+1));
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}


template <typename it>
void insertionSort(it l, it r) {
    for (it j, i = l+1; i < r; ++i) {
        auto t = *i;
        for (j = i; j > l && *(j-1) > t; --j)
            *j = *(j-1);
        *j = t;
        counter::xors += (i-j)/3;
    }
}


template <typename it>
it partition(it l, it r) {
    auto p = *(l+(r-l)/2);
    it i = l, j = r-1;
    while (1) {
        while (*i < p) ++i;
        while (*j > p) --j;
        if (i < j) counter::swap(*i++, *j--);
        else break;
    }
    return i;
}

template <typename it>
void quickSort(it l, it r) {
    if (r-l < 2) return;
    it i = partition(l, r);
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
        counter::swap(*i, *m);
        i = m;
    }
}

template <typename it>
void heapSort(it l, it r) {
    for (it i = l + (r-l-1)/2; i > l; --i)
        heapify(l, r, i);
    for (; r-l >= 2; --r) {
        heapify(l, r, l);
        counter::swap(*l, *(r-1));
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
                counter::swap(*i, *(i+gap));
                swapped = true;
            }
        }
    }
}


template <typename it>
void introSort(it l, it r, int depth, int chunk) {
    if (r-l < chunk) insertionSort(l, r);
    else if (depth) {
        it i = partition(l, r);
        introSort(l, i, depth-1, chunk);
        introSort(i, r, depth-1, chunk);
    }
    else heapSort(l, r);
}

template <typename it>
void introSort(it l, it r) {
    introSort(l, r, log2(r-l), 128);
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
        case 'g':
            gnomeSort(vec.begin(), vec.end());
            break;
        case 'b':
            bubbleSort(vec.begin(), vec.end());
            break;
        case 'I':
            insertionSort(vec.begin(), vec.end());
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
        case 'i':
            introSort(vec.begin(), vec.end());
            break;
    }
    auto t1 = chrono::high_resolution_clock::now();

    auto dt = chrono::duration_cast<chrono::microseconds> (t1-t0);
    cout << counter::xors << " xors" << endl;
    cout << dt.count() << " µs" << endl;

    return !is_sorted(vec.begin(), vec.end());
}
