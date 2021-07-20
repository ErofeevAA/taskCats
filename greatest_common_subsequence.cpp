#include <fstream>
#include <vector>
#include <string>

int main() {
    std::ifstream in_file("input.txt");
    std::string first, second;
    in_file >> first >> second;
    in_file.close();
    int N = first.size();
    int M = second.size();
    std::vector<std::vector<int>> matrix(N + 1);
    matrix[0] = std::vector<int>(M + 1);
    for (int i = 1; i < N + 1; ++i) {
        matrix[i] = std::vector<int>(M + 1);
        for (int j = 1; j < M + 1; ++j) {
            if (first[i - 1] == second[j - 1]) {
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
                continue;
            }
            matrix[i][j] = std::max(matrix[i - 1][j], matrix[i][j - 1]);
        }
    }
    std::ofstream o_file("output.txt");
    std::string res;
    int i = N;
    int j = M;
    while (i > 0 && j > 0) {
        if (first[i - 1] == second[j - 1]) {
            res += first[i - 1];
            --i;
            --j;
        } else if (matrix[i - 1][j] == matrix[i][j]) {
            --i;
        } else
            --j;
    }
    for (int k = res.size() - 1; k >= 0; --k) {
        o_file << res[k];
    }
    o_file.close();
    return 0;
}
