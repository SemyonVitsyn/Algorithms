#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

template <typename T>
class Point {
public:
    Point() = default;

    Point(const T& x, const T& y) : x_(x), y_(y) {
    }

    Point(const Point& other) : x_(other.x_), y_(other.y_) {
    }

    Point operator=(const Point& other) {
        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }

    Point operator+(const Point& added) const {
        return {x_ + added.x_, y_ + added.y_};
    }

    Point operator-(const Point subtrahend) const {
        return {x_ - subtrahend.x_, y_ - subtrahend.y_};
    }

    Point operator*(const int k) const {
        return {k * x_, k * y_};
    }

    T operator^(const Point& other) const {
        return x_ * other.y_ - y_ * other.x_;
    }

    bool operator==(const Point& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }

    double Dist(Point other) const {
        return sqrt((x_ - other.x_) * (x_ - other.x_) + (y_ - other.y_) * (y_ - other.y_));
    }

    T& GetX() {
        return x_;
    }

    T& GetY() {
        return y_;
    }

private:
    T x_ = 0;
    T y_ = 0;
};

template <typename T>
std::istream& operator>>(std::istream& in, Point<T>& p) {
    in >> p.GetX() >> p.GetY();
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, Point<T>& p) {
    out << p.GetX() << " " << p.GetY() << std::endl;
    return out;
}

template <typename T>
T Area(Point<T> a, Point<T> b, Point<T> c) {
    return (b - a).GetX() * (c - a).GetY() - (b - a).GetY() * (c - a).GetX();
}

void ConvexHull(std::vector<Point<int64_t>>& pillars) {
    Point<int64_t> p0 = pillars[0];
    for (Point<int64_t> p : pillars) {
        if (p.GetX() < p0.GetX() || (p.GetX() == p0.GetX() && p.GetY() < p0.GetY())) {
            p0 = p;
        }
    }

    std::vector<Point<int64_t>> hull;

    std::sort(pillars.begin(), pillars.end(), [&](Point<int64_t> a, Point<int64_t> b) {
        int64_t s = (a - p0) ^ (b - p0);
        return s < 0 || (s == 0 && p0.Dist(a) > p0.Dist(b));
    });

    for (Point<int64_t> p : pillars) {
        while (hull.size() >= 2) {
            Point<int64_t> new_v = p - hull.back();
            Point<int64_t> prev_v = hull.back() - hull[hull.size() - 2];
            if ((new_v ^ prev_v) <= 0) {
                hull.pop_back();
            } else {
                break;
            }
        }

        hull.push_back(p);
    }

    std::cout << hull.size() << std::endl;
    std::cout << hull[hull.size() - 1];
    for (int64_t i = 0; i < static_cast<int64_t>(hull.size() - 1); ++i) {
        std::cout << hull[i];
    }

    int64_t area = 0;
    for (int64_t i = 1; i < static_cast<int64_t>(hull.size() - 1); ++i) {
        area += Area(hull[0], hull[i + 1], hull[i]);
    }

    std::cout << std::setprecision(1) << std::fixed << (static_cast<double>(area) / 2);
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<Point<int64_t>> pillars(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> pillars[i];
    }

    ConvexHull(pillars);

    return 0;
}
