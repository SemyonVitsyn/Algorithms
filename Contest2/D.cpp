#include <iostream>
#include <vector>

const int kMod = 1e9 + 7;

uint64_t BinPow(uint64_t a, int k) {
    uint64_t ans = 1;
    while (k > 0) {
        if (k & 1) {
            ans *= a;
            ans %= kMod;
        }
        a *= a;
        a %= kMod;
        k >>= 1;
    }

    return ans;
}

uint64_t Stirling(int n, int k) {
    if (n == 0) {
        return k == 0;
    }
    if (k == 0) {
        return n == 0;
    }
    if (n == k) {
        return 1;
    }

    std::vector<uint64_t> fact(n);
    std::vector<uint64_t> inf(n);
    fact[0] = inf[0] = 1;
    for (int i = 1; i < n; ++i) {
        fact[i] = (fact[i - 1] * i) % kMod;
        inf[i] = (inf[i - 1] * BinPow(i, kMod - 2)) % kMod;
    }

    auto c = [&](int n1, int k1) -> uint64_t {
        if (k1 > n1 || n1 < 0) {
            return 0;
        }
        if (k1 == 0 || n1 == k1) {
            return 1;
        }

        return (fact[n1] * ((inf[n1 - k1] * inf[k1]) % kMod)) % kMod;
    };

    uint64_t ans = 0;
    uint64_t sign[2] = {1, kMod - 1};
    for (int cnt = 0; cnt < k; ++cnt) {
        ans += (sign[cnt & 1] * ((BinPow(k - cnt, n) * c(k, cnt)) % kMod)) % kMod;
        ans %= kMod;
    }

    return (ans * inf[k]) % kMod;
}

uint64_t CalcCoef(int n, int k) {
    uint64_t coef = Stirling(n, k) % kMod;
    coef += (Stirling(n - 1, k) * (n - 1)) % kMod;
    return coef % kMod;
}

int main() {
    int n = 0;
    int k = 0;
    std::cin >> n >> k;

    std::vector<int> arr(n);
    uint64_t sum = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        sum += arr[i];
        sum %= kMod;
    }

    if (n < k) {
        std::cout << 0;
    } else if (n == k) {
        std::cout << sum;
    } else {
        std::cout << (sum * CalcCoef(n, k)) % kMod;
    }

    return 0;
}