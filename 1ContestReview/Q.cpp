// linear algorithm(7 points)

#include <iostream>
#include <map>
#include <vector>

class SuffixTree {
private:
    struct State {
        explicit State(int vertex = 0, int position = 0) : v(vertex), pos(position) {
        }

        int v;
        int pos;
    };

    struct Node {
        explicit Node(int left = -1, int right = -1, int parent = -1) : l(left), r(right), p(parent), link(0) {
        }

        int l;
        int r;
        int p;
        int link;
        std::map<char, int> next;
    };

public:
    SuffixTree(const std::string& str, int first_str_len) : str_(str), size_(2), first_str_len_(first_str_len) {
        vertices_ = std::vector<Node>(2 * str_.size());
        Build();
    }

    void Build() {
        for (size_t i = 2; i < vertices_.size(); i++) {
            vertices_[i].r = static_cast<int>(str_.size()) - 1;
        }

        for (char c = 'a'; c <= 'z'; c++) {
            vertices_[1].next[c] = 0;
        }
        vertices_[1].next['#'] = 0;
        vertices_[1].next['$'] = 0;
        vertices_[0].link = 1;

        int pos = 0;
        State curr_st;
        for (size_t i = 0; i < str_.size(); i++) {
            Add(str_[i], pos, curr_st);
            pos++;
        }
    }

    void Add(char ch, int pos, State& curr_st) {
        bool flag1 = true;
        bool flag2 = true;
        while (flag1 || flag2) {
            flag1 = flag2 = false;
            if (vertices_[curr_st.v].r < curr_st.pos) {
                if (!vertices_[curr_st.v].next.count(ch)) {
                    vertices_[curr_st.v].next[ch] = size_;
                    vertices_[size_].l = pos;
                    vertices_[size_++].p = curr_st.v;
                    curr_st.v = vertices_[curr_st.v].link;
                    curr_st.pos = vertices_[curr_st.v].r + 1;
                    flag1 = true;
                }

                if (!flag1) {
                    curr_st.v = vertices_[curr_st.v].next[ch];
                    curr_st.pos = vertices_[curr_st.v].l;
                }
            }

            if (!flag1) {
                if (curr_st.pos == -1 || ch == str_[curr_st.pos]) {
                    curr_st.pos++;
                } else {
                    vertices_[size_] = Node(vertices_[curr_st.v].l, curr_st.pos - 1, vertices_[curr_st.v].p);
                    vertices_[size_].next[str_[curr_st.pos]] = curr_st.v;

                    vertices_[size_].next[ch] = size_ + 1;
                    vertices_[size_ + 1].l = pos;
                    vertices_[size_ + 1].p = size_;

                    vertices_[curr_st.v].l = curr_st.pos;
                    vertices_[curr_st.v].p = size_;
                    vertices_[vertices_[size_].p].next[str_[vertices_[size_].l]] = size_;
                    size_ += 2;

                    curr_st.v = vertices_[vertices_[size_ - 2].p].link;
                    curr_st.pos = vertices_[size_ - 2].l;

                    while (curr_st.pos <= vertices_[size_ - 2].r) {
                        curr_st.v = vertices_[curr_st.v].next[str_[curr_st.pos]];
                        curr_st.pos += 1 + vertices_[curr_st.v].r - vertices_[curr_st.v].l;
                    }

                    if (curr_st.pos == vertices_[size_ - 2].r + 1) {
                        vertices_[size_ - 2].link = curr_st.v;
                    } else {
                        vertices_[size_ - 2].link = size_;
                    }

                    curr_st.pos = vertices_[curr_st.v].r - (curr_st.pos - vertices_[size_ - 2].r) + 2;
                    flag2 = true;
                }
            }
        }
    }

    void Print() {
        std::vector<int> num(size_, 0);
        std::vector<bool> visited(size_, false);
        std::cout << size_ - 1 << '\n';
        int curr = 1;
        DFS(0, visited, num, curr);
    }

private:
    void DFS(int vertex_number, std::vector<bool>& visited, std::vector<int>& num, int& curr) {
        visited[vertex_number] = true;
        if (vertex_number != 0) {
            num[vertex_number] = curr++;
            std::cout << num[vertices_[vertex_number].p] << ' ';

            if (vertices_[vertex_number].l < first_str_len_) {
                std::cout << "0 ";
                std::cout << vertices_[vertex_number].l << ' ';
                std::cout << ((vertices_[vertex_number].r < first_str_len_) ? vertices_[vertex_number].r + 1
                                                                            : first_str_len_)
                          << '\n';
            } else {
                std::cout << "1 ";
                std::cout << vertices_[vertex_number].l - first_str_len_ << ' ';
                std::cout << vertices_[vertex_number].r - first_str_len_ + 1 << '\n';
            }
        }

        for (auto elem : vertices_[vertex_number].next) {
            if (!visited[elem.second]) {
                DFS(elem.second, visited, num, curr);
            }
        }
    }

private:
    std::string str_;
    std::vector<Node> vertices_;
    int size_;
    int first_str_len_;
};

int main() {
    std::string str1;
    std::string str2;
    std::cin >> str1 >> str2;

    SuffixTree tree(str1 + str2, static_cast<int>(str1.length()));
    tree.Print();

    return 0;
}
