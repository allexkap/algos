#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;



long counter = 0;
void swapInt(int &a, int &b) {
    // cout << a << '^' << b << endl;
    a ^= b ^= a ^= b;
    ++counter;
}


void bubbleSort(vector<int> &vec, int l, int r) {
    for (int j = l; j < r; ++j)
        for (int i = l; i < r-j; ++i)
            if (vec[i] > vec[i+1])
                swapInt(vec[i], vec[i+1]);
}


void quickSort(vector<int> &vec, int l, int r) {
    if (r-l < 2) return;
    int p = vec[(l+r)/2];
    int i = l, j = r-1;
    while (1) {
        while (vec[i] < p) ++i;
        while (vec[j] > p) --j;
        if (i < j) swapInt(vec[i++], vec[j--]);
        else break;
    }
    quickSort(vec, l, i);
    quickSort(vec, i, r);
}


void wuickSort(vector<int> &vec, int l, int r) {
    if (l >= r) return;
    int w = l-1;
    for (int i = l; i <= r; ++i)
        if ((vec[i] < vec[r] || i == r) && i != ++w)
            swapInt(vec[i], vec[w]);
    wuickSort(vec, l, w-1);
    wuickSort(vec, w+1, r);
}


int main(int argc, char **argv) {
    if (argc < 2) return 0;

    fstream file("sorts.in");

    int n;
    file >> n;

    vector<int> vec(n);
    for (int i = 0; i < n; ++i) file >> vec[i];

    switch (argv[1][0]) {
        case 'b':
            bubbleSort(vec, 0, vec.size());
            break;
        case 'q':
            quickSort(vec, 0, vec.size());
            break;
        case 'w':
            wuickSort(vec, 0, vec.size());
            break;
    }

    cout << counter << endl;

    return !is_sorted(vec.begin(), vec.end());
}
