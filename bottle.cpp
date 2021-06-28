#include <fstream>
#include <set>
#include <iostream>

int main() {
    std::ifstream in_file("input.txt");
    std::ofstream out_file("output.txt");
    int N, M;
    in_file >> N >> M;
    srand(N + M);
    std::multiset<long> a;
    for (int i = 0; i < N; i++) {
        long ai;
        in_file >> ai;
        a.insert(ai);
    }
    while (M--) {
        long ai = *a.rbegin() / 10;
        a.erase(std::prev(a.end()));
        a.insert(ai);
    }
    unsigned long long sum = 0;
    for (auto i = a.begin(); i != a.end(); ++i) {
        sum += *i;
    }
    out_file << sum;
    in_file.close();
    out_file.close();
    return 0;
}
