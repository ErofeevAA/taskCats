#include <fstream>
//#include <vector>
//#include <set>
#include <map>
#include <queue>

struct ElemWithIndex {
    long long value;
    long long index;

    bool operator>(const ElemWithIndex &elem) const {
        if (this->value == elem.value) {
            return this->index > elem.index;
        }
        return this->value > elem.value;
    }
};

int main() {
    int N, M;
    std::ifstream in_file("input.txt");
    std::ofstream  out_file("output.txt");
    in_file >> N >> M;
    std::priority_queue<ElemWithIndex, std::deque<ElemWithIndex>, std::greater<>> queue;
    long long index;
    for (index = 0; index < N; ++index) {
        ElemWithIndex tmp{};
        in_file >> tmp.value;
        tmp.index = index;
        queue.push(tmp);
    }
    for (int i = 0; i < M; ++i) {
        ElemWithIndex f = queue.top();
        queue.pop();
        ElemWithIndex s = queue.top();
        queue.pop();
        ElemWithIndex sum{f.value + s.value, index++};
        queue.push(sum);
    }
    std::map<long long, long long> set;
    for (int i = 0; i < queue.size();) {
        ElemWithIndex tmp = queue.top();
        set[tmp.index] = tmp.value;
        queue.pop();
    }
    for (auto it = set.begin(); it != set.end(); ++it) {
        out_file << it->second << ' ';
    }
    in_file.close();
    out_file.close();
    return 0;
}
