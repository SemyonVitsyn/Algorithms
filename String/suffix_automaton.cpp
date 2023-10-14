#include <iostream>
#include <vector>
#include <map>

class SuffixAutomaton {
private:
    struct Node {
        int len;
        int link;
        int in;
        std::map<char, int> next;
    };

public:
    SuffixAutomaton() : last_(0), size_(1), substrings_count_(0) {
        states_.push_back({0, -1, 1, std::map<char, int>()});
    }

    int Add(char c) {
        int cur = size_++;
        states_.push_back({states_[last_].len + 1, 0, 0, std::map<char, int>()});
        int p = 0;
        for (p = last_; p != -1 && !states_[p].next.count(c); p = states_[p].link) {
            states_[p].next[c] = cur;
            states_[cur].in += states_[p].in;
        }

        if (p != -1) {
            int q = states_[p].next[c];
            if (states_[p].len + 1 == states_[q].len) {
                states_[cur].link = q;
            } else {
                states_[q].in--;
                states_[cur].in--;
                int clone = size_++;
                states_.push_back({states_[p].len + 1, states_[q].link, 0, states_[q].next});
                for (; p != -1 && states_[p].next[c] == q; p = states_[p].link) {
                    states_[p].next[c] = clone;
                    states_[clone].in += states_[p].in;
                }
                states_[cur].in += states_[clone].in;
                states_[q].link = states_[cur].link = clone;
            }
        }

        substrings_count_ += states_[last_].in;
        last_ = cur;
        return substrings_count_;
    }

private:
    std::vector<Node> states_;
    int last_;
    int size_;
    int substrings_count_;
};

int main() {
    std::string str;
    std::cin >> str;

    SuffixAutomaton scar;

    for (size_t i = 0; i < str.size(); ++i) {
        std::cout << scar.Add(str[i]) << '\n';
    }

    return 0;
}