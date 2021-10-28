#include <fstream>

using namespace std;

int partition(int *array, int left, int right) {
    int piv = array[rand() % (right - left + 1) + left];
    int i = left;
    int j = right;
    while (i <= j) {
        while ((array[i] < piv) ||
               (array[i] == piv && array[i] < piv))
            i++;
        while ((array[j] > piv) ||
               (array[j] == piv && array[j] > piv))
            j--;
        if (i >= j)
            break;
        swap(array[i++], array[j--]);
    }
    return j;
}

void quick_sort(int *array, int left, int right) {
    if (left < right) {
        int p = partition(array, left, right);
        quick_sort(array, left, p);
        quick_sort(array, p + 1, right);
    }
}

int main() {
    ifstream in_file("input.txt");
    int N, L;
    in_file >> N >> L;
    int *array = new int[N];
    srand(N+L);
    for (int i = 0; i < N; ++i) {
        in_file >> array[i];
    }
    in_file.close();
    quick_sort(array, 0, N - 1);
    int count  = array[0] + L;
    for (int i = 1; i < N; ++i) {
        if (array[i] > count) {
            count = array[i] + L;
            continue;
        }
        count += L;
    }
    ofstream out_file("output.txt");
    out_file << count;
    out_file.close();
    return 0;
}
