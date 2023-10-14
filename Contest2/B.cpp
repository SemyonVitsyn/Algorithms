#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<bool> prime(n + 1, true);
    uint64_t answer = 0;

    for (int p = 2; p * p <= n; ++p) {
        if (prime[p]) {
            for (int k = p * p; k <= n; k += p) {
                if (prime[k]) {
                    prime[k] = false;
                    answer += p;
                }
            }
        }
    }

    std::cout << answer;

    return 0;
}