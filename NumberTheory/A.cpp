#include <iostream>
#include <cmath>

const int64_t kMod = 1e9 + 7;

int64_t Mod(int64_t x, int64_t mod) {
    return ((x % mod) + mod) % mod;
}

int64_t Add(int64_t x, int64_t y, int64_t mod) {
    return Mod(Mod(x, mod) + Mod(y, mod), mod);
}

int64_t Mul(int64_t x, int64_t y, int64_t mod) {
    return Mod(Mod(x, mod) * Mod(y, mod), mod);
}

int64_t Fastpow(int64_t a, int64_t n, int64_t mod) {
    if (n == 0) {
        return 1;
    }
    if (n % 2 == 1) {
        return (a * Fastpow(a, n - 1, mod)) % mod;
    }
    int64_t tmp = Fastpow(a, n / 2, mod);
    return (tmp * tmp) % mod;
}

int main() {
    int64_t a = 0;
    int64_t b = 0;
    int64_t c = 0;
    int64_t d = 0;
    std::cin >> a >> b >> c >> d;
    std::cout << Add(Mul(a, Fastpow(b, kMod - 2, kMod), kMod), Mul(c, Fastpow(d, kMod - 2, kMod), kMod), kMod);

    return 0;
}
