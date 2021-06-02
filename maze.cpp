#include <fstream>
#include <queue>

int main() {
    std::ifstream in_file("input.txt");
    std::ofstream out_file("output.txt");
    int N, start_x, start_y, end_x, end_y;
    in_file >> N >> start_x >> start_y >> end_x >> end_y;
    int maze[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char c;
            in_file >> c;
            maze[i][j] = (c == '#' ? -1 : 0);
        }
    }
    std::queue<std::pair<int, int>> queue;
    queue.push({start_y - 1, start_x - 1});
    while (!queue.empty()) {
        int j = queue.front().first;
        int k = queue.front().second;
        if (k - 1 >= 0) {
            if (maze[j][k - 1] != -1) {
                if (j != start_y - 1 || k - 1 != start_x - 1) {
                    if (maze[j][k - 1] > (maze[j][k] + 1) || maze[j][k - 1] == 0) {
                        maze[j][k - 1] = maze[j][k] + 1;
                        queue.push({j, k - 1});
                    }
                }
            }
        }
        if (k + 1 <= N - 1) {
            if (maze[j][k + 1] != -1) {
                if (j != start_y - 1 || k + 1 != start_x - 1) {
                    if (maze[j][k + 1] > (maze[j][k] + 1) || maze[j][k + 1] == 0) {
                        maze[j][k + 1] = maze[j][k] + 1;
                        queue.push({j, k + 1});
                    }
                }
            }
        }
        if (j - 1 >= 0) {
            if (maze[j - 1][k] != -1) {
                if (j - 1 != start_y - 1 || k != start_x - 1) {
                    if (maze[j - 1][k] > (maze[j][k] + 1) || maze[j - 1][k] == 0) {
                        maze[j - 1][k] = maze[j][k] + 1;
                        queue.push({j - 1, k});
                    }
                }
            }
        }
        if (j + 1 <= N - 1) {
            if (maze[j + 1][k] != -1) {
                if (j + 1 != start_y - 1 || k != start_x - 1) {
                    if (maze[j + 1][k] > (maze[j][k] + 1) || maze[j + 1][k] == 0) {
                        maze[j + 1][k] = maze[j][k] + 1;
                        queue.push({j + 1, k});
                    }
                }
            }
        }
        queue.pop();
    }
    out_file << maze[end_y - 1][end_x - 1];
    in_file.close();
    out_file.close();
}
