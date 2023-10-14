#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> ManacherEven(std::vector<int>& str) {
    std::vector<int> answer;

    int center = 0;
    int radius = 0;
    std::vector<int> even_palindromes(str.size(), 0);

    for (int i = 0; i < static_cast<int>(str.size() / 2 + 1); ++i) {
        int val = 0;
        if (i <= center + radius - 1) {
            val = std::min(even_palindromes[center + radius - i - 1], center + radius - i);
        }
        while (i + val < static_cast<int>(str.size()) && i - val - 1 >= 0 && str[i + val] == str[i - val - 1]) {
            val++;
        }
        even_palindromes[i] = val;
        if (i + val > center + radius) {
            center = i;
            radius = val;
        }
        if (even_palindromes[i] == i) {
            answer.push_back(static_cast<int>(str.size() - i));
        }
    }

    return answer;
}

int main() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;

    std::vector<int> str(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> str[i];
    }

    std::vector<int> answer = ManacherEven(str);
    std::reverse(answer.begin(), answer.end());

    for (auto i : answer) {
        std::cout << i << ' ';
    }

    return 0;
}