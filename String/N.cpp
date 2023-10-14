#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> SuffixArrayLCP(std::string& str, std::vector<int>& suffix_array) {
    int n = static_cast<int>(suffix_array.size());
    std::vector<int> lcp(n - 1);
    std::vector<int> pos(suffix_array.size());
    for (int i = 0; i < n; ++i) {
        pos[suffix_array[i]] = i;
    }

    int max_prefix = 0;
    for (int i = 0; i < n; ++i) {
        max_prefix = std::max(max_prefix - 1, 0);
        if (pos[i] == n - 1) {
            continue;
        }
        int j = suffix_array[pos[i] + 1];
        while (i + max_prefix < n && j + max_prefix < n && str[i + max_prefix] == str[j + max_prefix]) {
            max_prefix++;
        }
        lcp[pos[i]] = max_prefix;
    }

    return lcp;
}

int main() {
    int n = 0;
    std::cin >> n;

    std::string str;
    std::cin >> str;

    std::vector<int> suffix_array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> suffix_array[i];
        suffix_array[i]--;
    }

    std::vector<int> lcp = SuffixArrayLCP(str, suffix_array);

    for (int num : lcp) {
        std::cout << num << ' ';
    }

    return 0;
}