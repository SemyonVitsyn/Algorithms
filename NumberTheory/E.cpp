#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

std::vector<int> PrecalcEraseToReceiveGCD(int n) {
    std::vector<bool> table(n + 1, true);
    std::vector<int> f(n / 2 + 1, INT_MAX);
    f[n / 2] = 0; 
    for (int i = n / 2 - 1; i > 0; --i) {
        f[i] = f[i + 1];
        for (int k = (i + 1) * 2; k <= n; k += i + 1) {
                if (table[k]) {
                table[k] = false;
                f[i]++;
            }
        }
    }

    return f;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;
    std::vector<int> erase_to_receive_gcd = PrecalcEraseToReceiveGCD(n);

    int q = 0;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int size = 0;
        std::cin >> size;
        std::cout << std::lower_bound(erase_to_receive_gcd.begin(), erase_to_receive_gcd.end(), n - size, std::greater<int>()) - erase_to_receive_gcd.begin() << ' ';
    }

    return 0;
}