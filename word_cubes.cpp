#include <string>
#include <fstream>
#define MAX_LEN 12

std::string word;
std::string cubes[MAX_LEN];
bool has_solve = false;
int result[MAX_LEN] = {};
bool used_cubes[MAX_LEN] = {};

void permutation(std::ofstream &out_file, const int &N, int h = 0) {
    if (h == word.size()) {
        for (int i = 0; i < word.size(); ++i) {
            has_solve = true;
            out_file << result[i] << ' ';
        }
        return;
    }

    for (int i = 0; i < N && !has_solve; ++i) {
        if (used_cubes[i] > 0) {
            continue;
        }
        for (int j = 0; j < 6 && !has_solve; ++j) {
            if (cubes[i][j] == word[h]) {
                result[h] = i + 1;
                used_cubes[i] = true;
                permutation(out_file, N, h + 1);
                used_cubes[i] = false;
                break;
            }
        }
    }
}

int main() {
    std::ifstream in_file("input.txt");
    std::ofstream out_file("output.txt");
    int N;
    in_file >> N;
    in_file >> word;
    for (int i = 0; i < N; i++) {
        in_file >> cubes[i];
    }
    permutation(out_file, N);
    if (!has_solve) {
        out_file << 0;
    }
    return 0;
}
