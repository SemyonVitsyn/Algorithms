#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

#define _USE_MATH_DEFINES

struct LightHouse {
    int x = 0;
    int y = 0;
    int a = 0;
};

bool EnoughToFinish(std::pair<double, double> p1, std::pair<double, double> p2, double angle) {
    double val = p1.first * p2.first + p1.second * p2.second;
    val /= sqrt(p1.first * p1.first + p1.second * p1.second) * sqrt(p2.first * p2.first + p2.second * p2.second);
    return val >= std::cos(angle); 
}

double NewDist(double l, double r, LightHouse point) {
    auto x = static_cast<double>(point.x);
    auto y = static_cast<double>(point.y);
    auto angle = static_cast<double>(point.a) * M_PI / 180;

    std::pair<double, double> dif = {l - x, -y};

    if (EnoughToFinish(dif, {r - x, -y}, angle)) {
        return __DBL_MAX__;
    }

    dif = {dif.first * std::cos(angle) - dif.second * std::sin(angle),
           dif.first * std::sin(angle) + dif.second * std::cos(angle)};

    return x - y * (dif.first / dif.second);
}

double MaxDist(int l, int r, std::vector<LightHouse>& points) {
    std::vector<double> dist(1 << points.size(), l);
    for (size_t i = 0; i < dist.size(); ++i) {
        for (size_t j = 0; j < points.size(); ++j) {
            if (!(i & (1 << j))) {
                dist[i | (1 << j)] = std::max(dist[i | (1 << j)], NewDist(dist[i], r, points[j]));
                if (dist[i | (1 << j)] >= static_cast<double>(r)) {
                    return static_cast<double>(r - l);
                }
            }
        }
    }

    return dist[(1 << (points.size())) - 1] - l;
}

int main() {
    int n = 0;
    int l = 0;
    int r = 0;

    std::cin >> n >> l >> r;

    std::vector<LightHouse> points(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y >> points[i].a;
    }

    std::cout << std::setprecision(10) << std::fixed << MaxDist(l, r, points);

    return 0;
}