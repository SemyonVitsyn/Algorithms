#include <iostream>
#include <vector>
#include <stack>

const size_t kAlphabetSize = 128;

std::vector<int> SuffixArray(std::string& text) {
    text.push_back('\0');
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

    for (int step = 0; classes < n; ++step) {
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

    text.pop_back();

    return {p.begin() + 1, p.end()};
}

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

struct Info {
    size_t val;
    size_t id;
    size_t len;
};

void Refren(std::string& text) {
    std::vector<int> suffix_array = SuffixArray(text);
    std::vector<int> lcp = SuffixArrayLCP(text, suffix_array);
    lcp.push_back(0);

    int n = static_cast<int>(text.size());
    std::stack<Info> st;
    size_t maxlen = n;
    size_t maxval = 1;
    size_t start = 0;

    for (size_t i = 0; i < n; i++) {
        size_t x = 1;
        while (!st.empty() && lcp[i] <= st.top().len) {
            Info elem = st.top();
            st.pop();
            x += elem.val;
            if (x * elem.len > maxval * maxlen) {
                maxval = x;
                maxlen = elem.len;
                start = suffix_array[elem.id];
            }
        }
        if (st.empty() || lcp[i] > st.top().len) {
            st.push({x, i, static_cast<size_t>(lcp[i])});
        }
    }

    std::cout << maxval * maxlen << '\n';
    std::cout << maxlen << '\n';
    for (size_t i = start; i < start + maxlen; ++i) {
        std::cout << static_cast<int>(text[i] - '0') << ' ';
    }
}

int main() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;

    std::string text;

    for (int i = 0; i < n; ++i) {
        int val = 0;
        std::cin >> val;
        text.push_back(static_cast<char>('0' + val));
    }

    Refren(text);

    return 0;
}