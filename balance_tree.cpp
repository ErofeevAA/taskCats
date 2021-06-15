#include <fstream>
#include <vector>
#include <set>

#define MAX_SIZE 1000000

long long get_hash(long long key) {
    return key % (MAX_SIZE);
}

void push(std::vector<std::set<long long>> &table, long long value) {
    long long hash = get_hash(value);
    table[hash].insert(value);

}

void pop(std::vector<std::set<long long>> &table, long long value) {
    long long hash = get_hash(value);
    table[hash].erase(value);
}

int compare(const void * x1, const void * x2) {
    return ( *(int*)x1 - *(int*)x2 );
}

int main() {
    std::ifstream in_file("input.txt");
    std::ofstream out_file("output.txt");
    long long tmp;
    std::vector<std::set<long long>> table(MAX_SIZE);//= new std::set<long long> [MAX_SIZE];
    while (true) {
        in_file >> tmp;
        if (tmp == 0) {
            break;
        }
        if (tmp > 0) {
            push(table, tmp);
        } else {
            pop(table, -tmp);
        }
    }
    auto *res = new long long [MAX_SIZE]{};
    for (int i = 0, k = 0; i < MAX_SIZE; ++i) {
        if (table[i].empty()) {
            continue;
        }
        for (auto j = table[i].begin(); j != table[i].end() ; ++j) {
            res[k] = *j;
            ++k;
        }
        //res[k] = *table[i].end();
    }
    qsort(res, MAX_SIZE, sizeof (long long), compare);
    for (auto i = 0; i < MAX_SIZE; ++i) {
        if (res[i])
            out_file << res[i] << ' ';
    }
    in_file.close();
    out_file.close();
    return 0;
}
