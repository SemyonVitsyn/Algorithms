#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>

#define _USE_MATH_DEFINES

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

void FFT(std::complex<double>* a, std::vector<int64_t>& rev, int64_t size, bool invert) {
    for (int64_t i = 0; i < size; ++i) {
        if (i < rev[i]) {
            std::swap(a[i], a[rev[i]]);
        }
    }

    for (int64_t len = 2; len <= size; len <<= 1) {
        double angle = 2 * M_PI / static_cast<double>(len * (invert ? -1 : +1));
        int64_t len2 = len >> 1;
        std::complex<double> wlen(cos(angle), sin(angle));

        auto wlen_pw = new std::complex<double>[size]();
        wlen_pw[0] = {1, 0};
		for (int i=1; i<len2; ++i) {
			wlen_pw[i] = wlen_pw[i-1] * wlen;
        }

        for (int64_t i = 0; i < size; i += len) {
            std::complex<double> temp = 0;
			std::complex<double> *pu = a + i;
			std::complex<double> *pv = a + i + len2; 
			std::complex<double> *pu_end = a + i + len2;
			std::complex<double> *pw = wlen_pw;
			for (; pu!=pu_end; ++pu, ++pv, ++pw) {
				temp = *pv * *pw;
				*pv = *pu - temp;
				*pu += temp;
			}
        }

        delete[] wlen_pw;
    }

    if (invert) {
        for (int64_t i = 0; i < size; ++i) {
            a[i] /= static_cast<double>(size);
        }
    }
}

void Multiply(const std::vector<int64_t>& a, const std::vector<int64_t>& b) {
    int64_t size = 1;
    while (size < static_cast<int64_t>(std::max(a.size(), b.size()))) {
        size <<= 1;
    }
    size <<= 1;

    auto fft_a = new std::complex<double>[size]();
    auto fft_b = new std::complex<double>[size]();
    for (size_t i = 0; i < a.size(); ++i) {
        fft_a[i] = {static_cast<double>(a[i]), 0};
    }
    for (size_t i = 0; i < b.size(); ++i) {
        fft_b[i] = {static_cast<double>(b[i]), 0};
    }

    std::vector<int64_t> rev = PrecalcBitRev(size, static_cast<int64_t>(std::log2(size)));
    FFT(fft_a, rev, size, false);
    FFT(fft_b, rev, size, false);

    for (int64_t i = 0; i < size; ++i) {
        fft_a[i] *= fft_b[i];
    }

    FFT(fft_a, rev, size, true);

    auto s = static_cast<int64_t>(a.size() + b.size() - 2);
    if (a.size() == 1 || b.size() == 1) {
        s = static_cast<int64_t>(std::max(a.size() - 1, b.size() - 1));
    }
    std::cout << s << ' ';
    for (int64_t i = s; i >= 0; --i) {      
        std::cout << ((fft_a[i].real() >= 0)? static_cast<int64_t>(fft_a[i].real() + 0.5) : static_cast<int64_t>(fft_a[i].real() - 0.5)) << ' ';
    }

    delete[] fft_a;
    delete[] fft_b;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int64_t n = 0;
    std::cin >> n;
    std::vector<int64_t> a(n + 1);
    for (int64_t i = 0; i <= n; ++i) {
        std::cin >> a[n - i];
    }

    int64_t m = 0;
    std::cin >> m;
    std::vector<int64_t> b(m + 1);
    for (int64_t i = 0; i <= m; ++i) {
        std::cin >> b[m - i];
    }

    Multiply(a, b);

    return 0;
}
