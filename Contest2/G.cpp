#include <iostream>
#include <vector>

const int64_t kMod = 1e9 + 9;
const std::vector<int64_t> kMtrx = {0, 1, 1, 1};

std::vector<int64_t> MatrixFastPow(std::vector<int64_t> mtrx, int64_t power) {
    std::vector<int64_t> res = {1, 0, 0, 1};
    while (power > 0) {
        if (power % 2 == 1) {
            std::vector<int64_t> temp = res;
            res[0] = (temp[0] * mtrx[0] + temp[1] * mtrx[2]) % kMod;
            res[1] = (temp[0] * mtrx[1] + temp[1] * mtrx[3]) % kMod;
            res[2] = (temp[2] * mtrx[0] + temp[3] * mtrx[2]) % kMod;
            res[3] = (temp[2] * mtrx[1] + temp[3] * mtrx[3]) % kMod;
        }

        std::vector<int64_t> temp = mtrx;
        mtrx[0] = (temp[0] * temp[0] + temp[1] * temp[2]) % kMod;
        mtrx[1] = (temp[0] * temp[1] + temp[1] * temp[3]) % kMod;
        mtrx[2] = (temp[2] * temp[0] + temp[3] * temp[2]) % kMod;
        mtrx[3] = (temp[2] * temp[1] + temp[3] * temp[3]) % kMod;
        power >>= 1;
    }

    return res;
}

int64_t F(int64_t n) {
    if (n == 0) {
        return 1;
    }

    std::vector<int64_t> p = MatrixFastPow(kMtrx, n);
    return p[0] + p[2];
}

int main() {
    int64_t n = 0;
    int64_t q = 0;
    std::cin >> n;
    std::cin >> q;
    std::vector<std::pair<int64_t, int64_t>> airports(n);
    std::vector<int64_t> airport_coef(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> airports[i].first >> airports[i].second;
        std::cin >> airport_coef[i];
        airport_coef[i] %= kMod;
    }

    std::vector<int64_t> coef(q);
    for (int i = 0; i < q; ++i) {
        std::cin >> coef[i];
    }

    for (int i = 0; i < q; ++i) {
        int64_t answer = 0;
        for (int j = 0; j < n; ++j) {
            if (airports[j].second - airports[j].first - coef[i] >= 0) {
                answer += ((F(airports[j].second - airports[j].first - coef[i]) % kMod) * airport_coef[j]) % kMod;
                answer %= kMod;
            }
        }
        std::cout << answer << '\n';
    }

    return 0;
}