#include <iostream>
#include <vector>
#include <string>

void Check(std::string s, std::string t) {
    std::string str = s + '#' + t;
    std::vector<size_t> pi(str.size(), 0);

    for (size_t i = 1; i < str.size(); ++i) {
        size_t j = pi[i - 1];
        while (j > 0 && str[i] != str[j]) {
            j = pi[j - 1];
        }

        if (str[i] == str[j]) {
            ++j;
        }

        pi[i] = j;

        if (i >= s.size() + 1 && pi[i] == 0) {
            std::cout << "Yes";
            return;
        }
    }

    std::cout << "No" << '\n';

    std::vector<std::string> partition;

    for (size_t i = str.size() - 1; i >= s.size() + 1;) {
        size_t size = pi[i];
        i -= pi[i];
        partition.push_back(str.substr(i + 1, size));
    }

    for (size_t i = partition.size() - 1; i > 0; --i) {
        std::cout << partition[i] << ' ';
    }

    std::cout << partition[0];
}

int main() {
    std::string s;
    std::string t;
    std::cin >> s >> t;

    Check(s, t);

    return 0;
}
