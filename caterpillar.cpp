#include <iostream>
#include <queue>

using namespace std;

int main() {
    int L, N;
    cin >> L >> N;
    int *array_hill = new int[N];
    int cur, prev;
    int counter = 0;
    cin >> prev;
    array_hill[0] = 0;
    for (int i = 1; i < N; ++i) {
        cin >> cur;
        if (cur < prev) {
            array_hill[i] = -1;
        } else {
            array_hill[i] = 1;
        }
        prev = cur;
    }
    //cout << array_hill[0] << ' ';
    for (int i = 1; i < N; ++i) {
        array_hill[i] += array_hill[i - 1];
        //cout << array_hill[i] << ' ';
    }
    //cout << endl;
    for (int i = L; i < N; ++i) {
        int tmp1 = i - 1;
        int tmp2 = i - L;
        if (array_hill[i] < array_hill[tmp1]) {
            if (array_hill[i] - array_hill[tmp2] < 0) {
                continue;
            }
        }
        ++counter;
    }
    cout << counter;
    delete[] array_hill;
    return 0;
}
