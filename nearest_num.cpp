#include <fstream>
#include <stack>

long *nextGreaterElement(long *a, const long &N) {
    long *res = new long[N];
    std::stack<long> s;
    for(long i = N - 1; i >= 0; --i) {
        while(!s.empty() && s.top() <= a[i]) {
            s.pop();
        }
        res[i] = s.empty() ? a[i] : s.top();
        s.push(a[i]);
    }
    return res;
}

int main() {
    std::ifstream in_file("input.txt");
    long N;
    in_file >> N;
    long *a = new long [N];
    for (long i = 0; i < N; ++i) {
        in_file >> a[i];
    }
    in_file.close();
    std::ofstream out_file("output.txt");
    long *res = nextGreaterElement(a, N);
    for (long i = 0; i < N; ++i) {
        out_file << res[i] << ' ';
    }
    out_file.close();
    return 0;
}
