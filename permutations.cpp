#include <iostream>

using namespace std;

void print(int *a, const int &N) {
    for (int i = 0; i < N; ++i) {
        cout << a[i] << ' ';
    }
    cout << endl;
}

void swap(const int &i, const int &j, int *array) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

void permutations(const int &N) {
    int *array = new int[N];
    for (int i = 0; i < N; ++i) {
        array[i] = i + 1;
    }
    while (true) {
        print(array, N);
        int i = N - 2;
        while (i != -1 && array[i] > array[i + 1]) {
            i--;
        }
        if (i == -1) {
            break;
        }
        int k = N - 1;
        while (array[i] > array[k]) {
            k--;
        }
        swap(i, k, array);
        int l = i + 1;
        int r = N - 1;
        while (l < r) {
            swap(l++, r--, array);
        }
    }

}

int main() {
    int N;
    cin  >> N;
    permutations(N);
    return 0;
}