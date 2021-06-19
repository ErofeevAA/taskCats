#include <fstream>
#include <string>
#include <vector>

#define EDGES "edges"
#define LISTS "lists"
//#define MAT "mat"

#define OUT_FILE "output.txt"

using namespace std;

int g_M = 0;

vector<vector<int>> edges_to_lists(int **edges, const int &N, const int &M) {
    vector<vector<int>> res(N);
    for (int i = 0; i < M; ++i) {
        res[edges[i][0] - 1].push_back(edges[i][1]);
    }
    return res;

}

int **edges_to_mat(int **edges, const int &N, const int &M) {
    int **res = new int *[N];
    for (int i = 0; i < N; ++i) {
        res[i] = new int [N]{};
    }
    for (int i = 0; i < M; ++i) {
        res[edges[i][0] - 1][edges[i][1] - 1] = 1;
    }
    return res;
}

int **lists_to_edges(const vector<vector<int>> &lists, const int M) {
    int **res = new int *[M];
    int k = 0;
    for (int i = 0; i < lists.size(); ++i) {
        for (int j = 0; j < lists[i].size(); ++j) {
            res[k] = new int [2];
            res[k][0] = i + 1;
            res[k][1] = lists[i][j];
            ++k;
        }
    }
    return res;
}

int **lists_to_mat(const vector<vector<int>> &lists, const int &N) {
    int **res = new int *[N];
    for (int i = 0; i < lists.size(); ++i) {
        res[i] = new int[N]{};
        for (int j = 0; j < lists[i].size(); ++j) {
            res[i][lists[i][j] - 1] = 1;
        }
    }
    return res;
}

int **mat_to_edges(int **mat, const int &N, const int &M) {
    int **res = new int *[M];
    int k = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (mat[i][j] == 1) {
                res[k] = new int [2];
                res[k][0] = i + 1;
                res[k][1] = j + 1;
                ++k;
            }
        }
    }
    return res;
}

vector<vector<int>> mat_to_lists(int **mat, const int &N) {
    vector<vector<int>> res(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (mat[i][j] == 1) {
                res[i].push_back(j + 1);
            }
        }
    }
    return res;
}

int **read_edges(ifstream &in_file, const int &M) {
    int **res = new int *[M];
    for (int i = 0; i < M; ++i) {
        res[i] = new int [2];
        in_file >> res[i][0] >> res[i][1];
    }
    return res;
}

vector<vector<int>> read_lists(ifstream &in_file, const int &N) {
    vector<vector<int>> res(N);
    for (int i = 0; i < N; ++i) {
        int num_ver;
        in_file >> num_ver;
        res[i] = vector<int>(num_ver);
        for (int j = 0; j < num_ver; ++j) {
            in_file >> res[i][j];
            ++g_M;
        }
    }
    return res;
}

int **read_mat(ifstream &in_file, const int &N) {
    int **res = new int *[N];
    for (int i = 0; i < N; ++i) {
        res[i] = new int [N];
        for (int j = 0; j < N; ++j) {
            in_file >> res[i][j];
            if (res[i][j] == 1) {
                ++g_M;
            }
        }
    }
    return res;
}

void print_edges(int **edges, const int &N, const int &M) {
    ofstream out_file(OUT_FILE);
    out_file << N << ' ' << M;
    for (int i = 0; i < M; ++i) {
        out_file << endl << edges[i][0] << ' ' << edges[i][1];
    }
    out_file.close();
}

void print_lists(const vector<vector<int>> &lists) {
    ofstream out_file(OUT_FILE);
    out_file << lists.size();
    for (const auto & list : lists) {
        out_file << endl << list.size();
        for (int l : list) {
            out_file << ' ' << l;
        }
    }
    out_file.close();
}

void print_mat(int **mat, const int &N) {
    ofstream out_file(OUT_FILE);
    out_file << N;
    for (int i = 0; i < N; ++i) {
        out_file << endl;
        for (int j = 0; j < N; ++j) {
            out_file << mat[i][j] << ' ';
        }
    }
    out_file.close();
}

int main() {
    ifstream in_file("input.txt");
    string from, to;
    in_file >> from >> to;
    if (from == to) {
        ofstream out_file(OUT_FILE);
        string tmp;
        getline(in_file, tmp);
        while (getline(in_file, tmp)) {
            out_file << tmp << endl;
        }
        in_file.close();
        return 0;
    }
    int N;
    in_file >> N;
    if (from == EDGES) {
        int M;
        in_file >> M;
        int **edges = read_edges(in_file, M);
        in_file.close();
        if (to == LISTS) {
            vector<vector<int>> lists = edges_to_lists(edges, N, M);
            print_lists(lists);
            return 0;
        }
        int **mat = edges_to_mat(edges, N, M);
        print_mat(mat, N);
        return 0;
    }
    if (from == LISTS) {
        vector<vector<int>> lists = read_lists(in_file, N);
        in_file.close();
        if (to == EDGES) {
            int **edges = lists_to_edges(lists, g_M);
            print_edges(edges, N, g_M);
            return 0;
        }
        int **mat = lists_to_mat(lists, N);
        print_mat(mat, N);
        return 0;
    }
    int **mat = read_mat(in_file, N);
    in_file.close();
    if (to == EDGES) {
        int **edges = mat_to_edges(mat, N, g_M);
        print_edges(edges, N, g_M);
        return 0;
    }
    vector<vector<int>> lists = mat_to_lists(mat, N);
    print_lists(lists);
    return 0;
}
