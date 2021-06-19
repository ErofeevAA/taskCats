#include <fstream>
#include <set>
#include <string>
#include <vector>

std::string get_letters(const std::vector<std::string> &words) {
    std::string res;
    for (int i = 0; i < 3; ++i) {
        for (const char &l : words[i]) {
            if (l < 48 || l > 57) {
                if (res.find(l) == std::string::npos) {
                    res.push_back(l);
                }
            }
        }
    }
    return res;
}

bool next_seq(int *seq, const int &M) {
    const int N = 10;
    int j;
    do {
        j = N - 2;
        while (j > -1 && seq[j] > seq[j + 1]) {
            --j;
        }
        if (j == -1) {
            return false;
        }
        int k = N - 1;
        while (seq[j] > seq[k]) {
            --k;
        }
        std::swap(seq[j], seq[k]);
        int l = j + 1;
        int r = N - 1;
        while (l < r) {
            std::swap(seq[l], seq[r]);
            ++l;
            --r;
        }
    } while (j > M - 1);
    return true;
}

std::vector<std::string> convert_to_num(const int *seq, const std::vector<std::string> &words,
                                        const std::string &letters) {
    std::vector<std::string> res(3);
    for (int i = 0; i < 3; ++i) {
        res[i] = words[i];
        for (int j = 0; j < res[0].size(); ++j) {
            if (res[i][j] > 57 || res[i][j] < 48) {
                res[i][j] = seq[letters.find(res[i][j])] + '0';
            }
        }
    }
    return res;
}

std::vector<std::string> result(const int *seq, const std::vector<std::string> &words, const std::string &letters) {
    std::vector<std::string> res = convert_to_num(seq, words, letters);
    if (res[0][0] == '0' || res[1][0] == '0' || res[2][0] == '0') {
        return std::vector<std::string>(0);
    }
    int first = std::stoi(res[0]);
    int second = std::stoi(res[1]);
    int sum = std::stoi(res[2]);
        if (first + second == sum) {
            return res;
        }
    return std::vector<std::string>(0);
}

void permutations(std::string &letters, std::vector<std::string> &words, std::ofstream &out_file) {
    int seq[10];
    for (int i = 0; i < 10; ++i) {
        seq[i] = i;
    }
    bool flag = true;
    while (flag) {
        std::vector<std::string> res = result(seq, words, letters);
        if (!res.empty()) {
            for(int j = 0; j < 3; ++j) {
                out_file << res[j] << std::endl;
            }
            out_file << std::endl;
        }
        flag = next_seq(seq, letters.size());
    }
}

int main() {
    std::ifstream in_file("input.txt");
    std::vector<std::string> words(3);
    for (int i = 0; i < 3; ++i) {
        in_file >> words[i];
    }
    std::string letters = get_letters(words);
    std::ofstream out_file("output.txt");
    permutations(letters, words, out_file);
}
