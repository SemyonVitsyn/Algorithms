#include <iostream>
#include <vector>
#include <map>

class SuffixAutomaton {
private:
    struct Node {
        int len;
        int link;
        std::map<char, int> next;
    };

public:
    SuffixAutomaton() : last_(0), size_(1), str_len_(0), substrings_count_(0) {
        states_.push_back({0, -1, std::map<char, int>()});
    }

    size_t Add(char c) {
        int cur = size_++;
        str_len_++;
        states_.push_back({states_[last_].len + 1, 0, std::map<char, int>()});
        int p = 0;
        for (p = last_; p != -1 && !states_[p].next.count(c); p = states_[p].link) {
            states_[p].next[c] = cur;
        }

        if (p != -1) {
            int q = states_[p].next[c];
            if (states_[p].len + 1 == states_[q].len) {
                states_[cur].link = q;
            } else {
                int clone = size_++;
                states_.push_back({states_[p].len + 1, states_[q].link, states_[q].next});

                for (; p != -1 && states_[p].next[c] == q; p = states_[p].link) {
                    states_[p].next[c] = clone;
                }
                states_[q].link = states_[cur].link = clone;
            }
        }

        last_ = cur;
        substrings_count_ += str_len_ - states_[states_[last_].link].len;
        return substrings_count_;
    }

private:
    std::vector<Node> states_;
    int last_;
    int size_;
    int str_len_;
    size_t substrings_count_;
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