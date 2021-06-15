#include <fstream>
#include <stack>
#include <vector>


int main() {
    std::ifstream in_file("input.txt");
    int N;
    in_file >> N;
    std::vector<int> a(N);
    for(int i = 0; i < N; ++i) {
        in_file >> a[i];
    }
    in_file.close();
    std::stack<int> stack;
    std::vector<int> nums_global_end(N);
    std::vector<int> radii(N);
    for(int i = 0; i < N; ++i) {
        nums_global_end[i] = -1;
        radii[i] = 0;
    }
    for(int i = 0; i < N; ++i) {
        while (!stack.empty() && a[stack.top()] < a[i]) {
            int j = stack.top();
            stack.pop();
            if (nums_global_end[j] == -1 || i - j < j - nums_global_end[j]) {
                nums_global_end[j] = i;
                radii[j] = i - j;
            }
        }
        if (stack.empty()) {
            nums_global_end[i] = -1;
            radii[i] = 0;
        } else {
            if (a[i] != a[stack.top()]) {
                nums_global_end[i] = stack.top();
                radii[i] = i - stack.top();
            } else {
                nums_global_end[i] = nums_global_end[stack.top()];
                if (nums_global_end[i] != -1) {
                    radii[i] = i - nums_global_end[stack.top()];
                } else {
                    radii[i] = 0;
                }
            }
        }
        stack.push(i);
    }
    std::ofstream out_file("output.txt");
    for(int i = 0; i < N; ++i) {
        out_file << radii[i] << ' ';
    }
    out_file.close();
}
