#include <iostream>
#include <vector>

int binary_search(const std::vector<long long> &a, const long long &key, int left, int right) {
    while (left <= right) {
        int mid = (right + left) / 2;
        if (a[mid] == key) {
            return mid;
        }
        if (a[mid] > key) {
            right = mid - 1;
            continue;
        }
        left = mid + 1;
    }
    return -1;
}

int main() {
    int N;
    std::cin >> N;
    int L, M, R;
    L = 0;
    std::vector<long long> sums(N + 1);
    for (int i = 1; i < N + 1; ++i) {
        std::cin >> sums[i];
        sums[i] += sums[i - 1];
    }
    long long max_sum = 0;
    for (int i = 1; i < N; ++i) {
        sums[i] -= sums[i - 1];
        for (int j = i + 1; j < N + 1; ++j) {
            sums[j] -= sums[i - 1];
            if (sums[j] % 2 == 0) {
                if (L == 0) {
                    int k = binary_search(sums, sums[j] / 2, i, j);
                    if (k == -1) {
                        continue;
                    }
                    M = k;
                    L = i;
                    R = j;
                    max_sum = sums[R];
                    continue;
                }
                if (sums[j] > max_sum) {
                    int k = binary_search(sums, sums[j] / 2, i, j);
                    if (k == -1) {
                        continue;
                    }
                    M = k;
                    R = j;
                    L = i;
                    max_sum = sums[R];
                }
            }
        }
    }
    if (L == 0) {
        std::cout << -1;
        return 0;
    }
    std::cout << L << ' ' << M << ' ' << R;
    return 0;
}
