#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int64_t PrimeFunction(int64_t n) {
    std::vector<int64_t> set;
    for (int64_t k = 1; k * k <= n; ++k) {
        set.push_back(n / k);
        set.push_back(k);
    }
    std::sort(set.begin(), set.end());
    set.erase(unique(set.begin(), set.end()), set.end());

    auto sq = static_cast<int64_t>(std::sqrt(static_cast<double>(n)));
    auto getidx = [&](int64_t x) {
        if (x <= sq) {
            return x - 1;
        }

        return static_cast<int64_t>(set.size() - (n / x));
    };

    std::vector<int64_t> pi = set;

    int iter = 0;
    for (int64_t p = 2; p * p <= n; ++p) {
        if (pi[getidx(p)] != pi[getidx(p - 1)]) {
            ++iter;
            for (int i = static_cast<int>(set.size()) - 1; i >= 0; --i) {
                if (set[i] < p * p) {
                    break;
                }
                pi[i] -= pi[getidx(set[i] / p)] - iter;
            }
        }
    }

    return pi[getidx(n)] - 1;
}

int main() {
    int64_t n = 0;
    std::cin >> n;
    std::cout << PrimeFunction(n);;
    
    return 0;
}
