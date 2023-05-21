#include <iostream>
#include <vector>
#include <string>

void KMP(std::string s, std::string p) {
    std::string str = p + '#' + s;
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

        if (pi[i] == p.size()) {
            std::cout << i - 2 * j << '\n';
        }
    }
}

int main() {
    std::string s;
    std::string p;
    std::cin >> s >> p;

    KMP(s, p);

    return 0;
}
