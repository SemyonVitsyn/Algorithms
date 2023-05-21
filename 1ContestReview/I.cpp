#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

std::vector<std::pair<size_t, size_t>> PalindromeConcatPairs(std::vector<std::string>& word_list) {
    std::vector<std::pair<size_t, size_t>> answer;
    std::unordered_map<std::string, size_t> map;

    for (size_t i = 0; i < word_list.size(); ++i) {
        map[std::string(word_list[i].rbegin(), word_list[i].rend())] = i + 1;
    }

    for (size_t i = 0; i < word_list.size(); ++i) {
        std::string word = word_list[i];
        for (size_t j = 0; j < word.size(); ++j) {
            std::string left = word.substr(0, j + 1);
            std::string right = word.substr(j + 1);

            // the left side is the center of the palindrome
            if (left == std::string(left.rbegin(), left.rend()) && map.count(right) && map[right] != i + 1) {
                answer.emplace_back(map[right], i + 1);
            }

            // the right side is the center of the palindrome
            if (right == std::string(right.rbegin(), right.rend()) && map.count(left) && map[left] != i + 1) {
                answer.emplace_back(i + 1, map[left]);
            }
        }
    }

    return answer;
}

int main() {
    size_t n = 0;
    std::cin >> n;
    std::vector<std::string> word_list(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> word_list[i];
    }

    std::vector<std::pair<size_t, size_t>> palindrome_pairs = PalindromeConcatPairs(word_list);
    std::sort(palindrome_pairs.begin(), palindrome_pairs.end());

    std::cout << palindrome_pairs.size() << '\n';
    for (size_t i = 0; i < palindrome_pairs.size(); ++i) {
        std::cout << palindrome_pairs[i].first << ' ' << palindrome_pairs[i].second << '\n';
    }

    return 0;
}
