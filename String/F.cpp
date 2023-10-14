#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> ConvertToPrefixFromZ(std::vector<int>& z) {
    std::vector<int> pi(z.size(), 0);
    for (size_t i = 1; i < z.size(); ++i) {
        for (size_t j = z[i]; j > 0; j--) {
            if (pi[i + j - 1] == 0) {
                pi[i + j - 1] = static_cast<int>(j);
            } else {
                break;
            }
        }
    }

    return pi;
}

std::string MinString(std::vector<int>& pi) {
    std::string str(pi.size(), 'a');
    for (size_t i = 1; i < pi.size(); ++i) {
        if (pi[i] > 0) {
            str[i] = str[pi[i] - 1];
        } else {
            std::vector<bool> exist(26, false);
            size_t curr_idx = i;
            while (curr_idx > 0) {
                curr_idx = pi[curr_idx - 1];
                exist[str[curr_idx] - 'a'] = true;
            }

            char symbol = 'a';
            while (exist[symbol - 'a']) {
                ++symbol;
            }

            str[i] = symbol;
        }
    }

    return str;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> z(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> z[i];
    }

    std::vector<int> pi = ConvertToPrefixFromZ(z);

    std::cout << MinString(pi);

    return 0;
}