#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream in_file("input.txt");
    int n;
    in_file >> n;
    long long a[n + 1];
    a[0] = 0;
    in_file >> a[1];
    ofstream out_file("output.txt");
    if (n == 1) {
        out_file << a[1];
        in_file.close();
        out_file.close();
        return 0;
    }
    int tmp;
    for (int i = 2; i <= n; i++) {
        in_file >> tmp;
        a[i] = max(a[i-1], a[i-2]) + tmp;
    }
    out_file << a[n];
    in_file.close();
    out_file.close();
    return 0;
}
