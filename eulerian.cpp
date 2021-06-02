#include <fstream>
#include <stack>
#include <vector>

struct Node {
    int val;
    Node *next;
};

struct List {
    int size = 0;
    Node *head = nullptr;
    Node *tail = nullptr;

    void push(int val) {
        ++(this->size);
        if (this->head == nullptr) {
            this->head = new Node;
            this->head->val = val;
            this->head->next = nullptr;
            this->tail = this->head;
            return;
        }
        this->tail->next = new Node;
        this->tail->next->val = val;
        this->tail = this->tail->next;
        this->tail->next = nullptr;
    }

    void pop(int val) {
        --(this->size);
        Node *tmp = this->head;
        Node *prev;
        while (tmp->val != val) {
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp == this->head) {
            tmp = tmp->next;
            delete this->head;
            this->head = tmp;
            return;
        }
        prev->next = tmp->next;
        delete tmp;
    }
};

int main() {
    std::ifstream in_file("input.txt");
    std::ofstream out_file("output.txt");
    int N, M;
    in_file >> N >> M;
    std::vector<List> array_of_list(N);
    for (int i = 0; i < M; ++i) {
        int v1, v2;
        in_file >> v1 >> v2;
        --v1;
        --v2;
        array_of_list[v1].push(v2);
        array_of_list[v2].push(v1);
    }
    for (int i = 0; i < N; ++i) {
        if (array_of_list[i].size % 2 == 1) {
            out_file << -1;
            in_file.close();
            out_file.close();
            return 0;
        }
    }
    std::stack<int> stack;
    stack.push(0);
    int v;
    while(!stack.empty()) {
        v = stack.top();
        if(array_of_list[v].head == nullptr) {
            out_file << stack.top() + 1 << ' ';
            stack.pop();
        } else {
            int v1 = array_of_list[v].head->val;
            stack.push(v1);
            array_of_list[v].pop(v1);
            array_of_list[v1].pop(v);
        }
    }
    in_file.close();
    out_file.close();
}
