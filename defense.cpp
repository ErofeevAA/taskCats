#include <fstream>

using namespace std;

typedef struct {
    long val;
    long index;
} ElemWithIndex;

long partition(ElemWithIndex *array, long left, long right) {
    long piv = array[rand() % (right - left + 1) + left].val;
    long i = left;
    long j = right;
    while (i <= j) {
        while ((array[i].val < piv) ||
               (array[i].val == piv && array[i].val < piv))
            i++;
        while ((array[j].val > piv) ||
               (array[j].val == piv && array[j].val > piv))
            j--;
        if (i >= j)
            break;
        swap(array[i++], array[j--]);
    }
    return j;
}

void quick_sort(ElemWithIndex *array, long left, long right) {
    if (left < right) {
        long p = partition(array, left, right);
        quick_sort(array, left, p);
        quick_sort(array, p + 1, right);
    }
}

long mod_bin_search(const long &key, ElemWithIndex *shelters, const long &M) {
    if (key <= shelters[0].val) {
        return shelters[0].index;
    }
    if (key >= shelters[M - 1].val) {
        return shelters[M - 1].index;
    }
    long left = 0;
    long right = M - 1;
    while (right - left > 1) {
        long m = (right + left) / 2;
        if(shelters[m].val < key) {
            left = m;
        }
        else {
            right = m;
        }
    }
    if(key - shelters[left].val < shelters[right].val - key) {
        return shelters[left].index;
    } else {
        return shelters[right].index;
    }
}

int main() {
    ifstream in_file("shelter.in");
    long N, M;
    in_file >> N;
    srand(N);
    long *villages = new long[N];
    for (long i = 0; i < N; ++i) {
        in_file >> villages[i];
    }
    in_file >> M;
    auto *shelters = new ElemWithIndex[M];
    for (int i = 0; i < M; ++i) {
        in_file >> shelters[i].val;
        shelters[i].index = i + 1;
    }
    in_file.close();
    quick_sort(shelters, 0, M - 1);
    ofstream out_file("shelter.out");
    for (int i = 0; i < N; ++i) {
        out_file << mod_bin_search(villages[i], shelters, M) << ' ';
    }
    out_file.close();
    delete[] villages;
    delete[] shelters;
    return 0;
}
