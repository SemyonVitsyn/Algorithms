#include <iostream>
#include <vector>
#include <string>

const size_t kAlphabetSize = 128;

std::string KthShift(std::string& text, int k) {
    int n = static_cast<int>(text.size());

    std::vector<int> p(n, 0);
    std::vector<int> c(n, 0);
    std::vector<int> cnt(kAlphabetSize, 0);

    for (int i = 0; i < n; ++i) {
        cnt[text[i]]++;
    }
    for (size_t i = 1; i < kAlphabetSize; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        p[--cnt[text[i]]] = i;
    }

    c[p[0]] = 0;
    for (int i = 1; i < n; ++i) {
        c[p[i]] = c[p[i - 1]];
        if (text[p[i]] != text[p[i - 1]]) {
            ++c[p[i]];
        }
    }

    int classes = c[p[n - 1]] + 1;

    for (int step = 0; (1 << step) < n; ++step) {
        std::vector<int> p_new(n, 0);
        std::vector<int> c_new(n, 0);
        for (int i = 0; i < n; ++i) {
            p_new[i] = p[i] - (1 << step);
            if (p_new[i] < 0) {
                p_new[i] += n;
            }
        }

        std::vector<int> count(classes, 0);

        for (int i = 0; i < n; ++i) {
            count[c[i]]++;
        }
        for (int i = 1; i < classes; ++i) {
            count[i] += count[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            p[--count[c[p_new[i]]]] = p_new[i];
        }

        c_new[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            c_new[p[i]] = c_new[p[i - 1]];
            if (c[p[i]] != c[p[i - 1]] || c[(p[i] + (1 << step)) % n] != c[(p[i - 1] + (1 << step)) % n]) {
                ++c_new[p[i]];
            }
        }

        c = c_new;
        classes = c[p[n - 1]] + 1;
    }

    std::vector<bool> visited(n, false);
    int cur_class = 0;

    for (int i = 0; i < n; ++i) {
        if (!visited[c[p[i]]]) {
            visited[c[p[i]]] = true;
            cur_class++;
        }

        if (cur_class == k) {
            return text.substr(p[i], n - p[i]) + text.substr(0, p[i]);
        }
    }

    return "IMPOSSIBLE";
}

int main() {
    std::string str;
    std::cin >> str;

    int k = 0;
    std::cin >> k;

    std::cout << KthShift(str, k);

    return 0;
}