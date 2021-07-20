#include <fstream>
#include <vector>

#define MAX_N 100000
#define GRAY 2
#define BLACK 1

int g_used[MAX_N];
int g_answer[MAX_N];
std::vector<int> g_array_of_list[MAX_N];
bool g_has_cycle = false;
int g_index_ans = 0;

void DFS(int v){
    g_used[v] = GRAY;
    for (int i = 0; i < g_array_of_list[v].size(); ++i) {
        if (!g_used[g_array_of_list[v][i]]) {
            DFS(g_array_of_list[v][i]);
        } else if (g_used[g_array_of_list[v][i]] == GRAY) {
            g_has_cycle = true;
            return;
        }
    }
    g_answer[g_index_ans++] = v + 1;
    g_used[v] = BLACK;
}

int main() {
    std::ifstream in_file("input.txt");
    std::ofstream out_file("output.txt");
    int N, M;
    in_file >> N >> M;
    for (int i = 0; i < M; ++i) {
        int v1, v2;
        in_file >> v1 >> v2;
        g_array_of_list[v1 - 1].push_back(v2 - 1);
    }
    for (int i = 0; i < N; ++i) {
        if (!g_used[i]){
            DFS(i);
            if (g_has_cycle) {
                out_file << -1;
                in_file.close();
                out_file.close();
                return 0;
            }
        }
    }
    for (int i = N - 1; i >= 0; --i) {
        out_file << g_answer[i] << ' ';
    }
    in_file.close();
    out_file.close();
    return 0;
}
