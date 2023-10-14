#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

std::vector<size_t> PrefixFunc(std::string str) {
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
    }

    return pi;
}

std::vector<size_t> ZFunc(std::string str) {
    std::vector<size_t> z(str.size(), 0);

    for (size_t i = 1, left = 0, right = 0; i < str.size(); ++i) {
        if (i <= right) {
            z[i] = std::min(right - i + 1, z[i - left]);
        }

        while (i + z[i] < str.size() && str[z[i]] == str[i + z[i]]) {
            z[i]++;
        }

        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }

    return z;
}

size_t CyclicEntrisQuantity(std::string pattern, std::string text) {
    size_t answer = 0;
    std::vector<size_t> pi = PrefixFunc(pattern + '#' + text);
    std::reverse(pattern.begin(), pattern.end());
    std::reverse(text.begin(), text.end());
    std::vector<size_t> z_rev = ZFunc(pattern + '#' + text);
    size_t concat_size = pattern.size() + 1 + text.size();

    for (size_t i = pattern.size() * 2; i < concat_size; ++i) {
        if (pi[i] >= pattern.size() || pi[i] + z_rev[pattern.size() + concat_size - i + pi[i]] >= pattern.size()) {
            answer++;
        }
    }

    return answer;
}

int main() {
    std::string pattern;
    std::string text;
    std::cin >> pattern >> text;
    if (pattern.size() > text.size()) {
        std::cout << 0;
    } else {
        std::cout << CyclicEntrisQuantity(pattern, text);
    }
    return 0;
}