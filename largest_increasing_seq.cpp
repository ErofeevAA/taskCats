#include <fstream>
#include <vector>

#define LIMIT_DATA 1000000001
//#define OUT_FILE "output.txt"

long mod_bin_search(const std::vector<long> &d, const long &key) {
    long left = 0;
    long right = d.size();
    while (right - left > 1) {
        long middle = (left + right) / 2;
        if (d[middle] >= key) {
            right = middle;
        } else {
            left = middle;
        }
    }
    return right;
}

int main() {
    std::ifstream in_file("input.txt");
    long N;
    in_file >> N;
    std::vector<long> d(N + 1);
    std::vector<long> indexes(N);
    d[0] = -LIMIT_DATA;
    indexes[0] = 0;
    for (long i = 1; i < N + 1; ++i) {
        d[i] = LIMIT_DATA;
    }
    long index_max_elem = 0;
    for (long i = 0; i < N; ++i) {
        long tmp;
        in_file >> tmp;
        long j = mod_bin_search(d, tmp);
        indexes[i] = j - 1;
        if (d[j - 1] < tmp && tmp < d[j]) {
            d[j] = tmp;
            if (indexes[i] > indexes[index_max_elem]) {
                index_max_elem = i;
            }
        }
    }
    in_file.close();
    long last_on_out_i = index_max_elem;
    long l_res = indexes[index_max_elem] + 1;
    std::vector<long> res(l_res);
    res[l_res - 1] = index_max_elem + 1;
    long k = l_res - 2;
    for (long i = index_max_elem - 1; i >= 0; --i) {
        if (indexes[i] + 1 != indexes[last_on_out_i]) {
            continue;
        }
        last_on_out_i = i;
        res[k] = i + 1;
        --k;
        if(indexes[i] == 0) {
            break;
        }
    }
    std::ofstream out_file("output.txt");
    out_file << l_res << std::endl;
    for (long i = 0; i < l_res; ++i) {
        out_file << res[i] << ' ';
    }
    out_file.close();
    return 0;
}
