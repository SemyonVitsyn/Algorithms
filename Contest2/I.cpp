#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>

const int64_t kMod = 7340033;
const int64_t kRoot = 5;
const int64_t kRootRev = 4404020;
const int64_t kRootPW = 1 << 20;

int64_t BinPow(int64_t a, int k) {
    int64_t ans = 1;
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

std::vector<int64_t> PrecalcBitRev(int64_t n, int64_t log) {
    std::vector<int64_t> rev(n, 0);
    for (int64_t i = 0; i < n; ++i) {
        for (int64_t j = 0; j < log; ++j) {
            if (i & (1 << j)) {
                rev[i] |= (1 << (log - 1 - j));
            }
        }
    }

    return rev;
}

void FFT(std::vector<int64_t>& a, std::vector<int64_t>& rev, bool invert) {
    auto size = static_cast<int64_t>(a.size());

    for (int64_t i = 0; i < size; ++i) {
        if (i < rev[i]) {
            std::swap(a[i], a[rev[i]]);
        }
    }

    for (int64_t len = 2; len <= size; len <<= 1) {
        int64_t wlen = invert ? kRootRev : kRoot;

        for (int64_t i = len; i < kRootPW; i <<= 1) {
            wlen = (wlen * wlen) % kMod;
        }

        for (int64_t i = 0; i < size; i += len) {
            int64_t w = 1;
            for (int64_t j = 0; j < len / 2; ++j) {
                int64_t u = a[i + j];
                int64_t v = (a[i + j + len / 2] * w) % kMod;
                a[i + j] = u + v < kMod ? u + v : u + v - kMod;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + kMod;
                w = (w * wlen) % kMod;
            }
        }
    }

    if (invert) {
        int64_t nrev = BinPow(size, kMod - 2);
        for (int64_t i = 0; i < size; ++i) {
            a[i] = (a[i] * nrev) % kMod;
        }
    }
}

std::vector<int64_t> Multiply(const std::vector<int64_t>& a, const std::vector<int64_t>& b) {
    int64_t size = 1;
    while (size < static_cast<int64_t>(std::max(a.size(), b.size()))) {
        size <<= 1;
    }
    size <<= 1;

    std::vector<int64_t> fft_a(size, 0);
    std::vector<int64_t> fft_b(size, 0);
    for (size_t i = 0; i < a.size(); ++i) {
        fft_a[i] = a[i];
    }
    for (size_t i = 0; i < b.size(); ++i) {
        fft_b[i] = b[i];
    }

    std::vector<int64_t> rev = PrecalcBitRev(size, static_cast<int64_t>(std::log2(size)));
    FFT(fft_a, rev, false);
    FFT(fft_b, rev, false);

    for (int64_t i = 0; i < size; ++i) {
        fft_a[i] *= fft_b[i];
        fft_a[i] %= kMod;
    }

    FFT(fft_a, rev, true);

    return fft_a;
}

void Reversed(std::vector<int64_t>& x, int64_t m) {
    int64_t size = 1;
    while (size < m) {
        size <<= 1;
    }
    size <<= 2;

    std::vector<int64_t> a = x;
    a.resize(size);

    std::vector<int64_t> answer(size, 0);
    answer[0] = BinPow(a[0], kMod - 2);
    int64_t cur_m = 1;
    while (cur_m < size / 4) {
        std::vector<int64_t> q(cur_m, 0);
        for (int64_t i = 0; i < cur_m; ++i) {
            q[i] = answer[i];
        }

        std::vector<int64_t> p0(cur_m, 0);
        for (int64_t i = 0; i < cur_m; ++i) {
            p0[i] = a[i];
        }

        std::vector<int64_t> p1(cur_m, 0);
        for (int64_t i = 0; i < cur_m; ++i) {
            p1[i] = a[cur_m + i];
        }

        auto temp = Multiply(p0, q);
        std::vector<int64_t> r(cur_m);
        for (int64_t i = 0; i < cur_m; ++i) {
            r[i] = temp[cur_m + i];
        }

        temp = Multiply(p1, q);
        for (int64_t i = 0; i < static_cast<int64_t>(temp.size()); ++i) {
            temp[i] = (kMod - temp[i]) % kMod;
            if (i < cur_m) {
                temp[i] = (temp[i] - r[i] + kMod) % kMod;
            }
        }

        temp = Multiply(temp, q);
        for (int64_t i = 0; i < cur_m; ++i) {
            answer[cur_m + i] = temp[i];
        }

        cur_m <<= 1;
    }

    for (int64_t i = 0; i < m; ++i) {
        std::cout << answer[i] << ' ';
    }
}

int main() {
    int64_t m = 0;
    int64_t n = 0;
    std::cin >> m >> n;
    std::vector<int64_t> p(n + 1, 0);
    for (int64_t i = 0; i <= n; ++i) {
        std::cin >> p[i];
    }

    if (p[0] != 0) {
        Reversed(p, m);
    } else {
        std::cout << "The ears of a dead donkey";
    }

    return 0;
}