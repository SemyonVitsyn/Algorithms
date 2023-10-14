#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <cfloat>

const int64_t kMod = 1e9 + 7;

template <typename T>
class LineSegment;

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

    Point operator-(const Point& subtrahend) const {
        return {x_ - subtrahend.x_, y_ - subtrahend.y_};
    }

    Point operator-() const {
        return {-x_, -y_};
    }

    Point operator*(const int k) const {
        return {k * x_, k * y_};
    }

    T operator^(const Point& other) const {
        return x_ * other.y_ - y_ * other.x_;
    }

    bool operator==(const Point other) const {
        return x_ == other.x_ && y_ == other.y_;
    }

    bool operator!=(const Point& other) {
        return x_ != other.x_ || y_ != other.y_;
    }

    bool operator<(const Point& other) {
        return (x_ < other.x_) || (x_ == other.x_ && y_ < other.y_);
    }

    bool operator>(const Point& other) {
        return (x_ > other.x_) || (x_ == other.x_ && y_ > other.y_);
    }

    bool operator<=(const Point& other) {
        return (x_ < other.x_) || (x_ == other.x_ && y_ <= other.y_);
    }

    bool operator>=(const Point& other) {
        return (x_ > other.x_) || (x_ == other.x_ && y_ >= other.y_);
    }

    double Dist(Point other) const {
        return sqrt((x_ - other.x_) * (x_ - other.x_) + (y_ - other.y_) * (y_ - other.y_));
    }

    bool Inside(const std::vector<Point<T>>& polygon) const {
        int intersection_count = 0;
        LineSegment<T> ray({x_, y_}, {x_, static_cast<int64_t>(2e8)});
        for (size_t i = 0; i < polygon.size(); ++i) {
            LineSegment<T> segment = {polygon[i], polygon[(i + 1) % polygon.size()]};
            if (ray.Intersect(segment)) {
                intersection_count++;
            }
        }

        if (intersection_count > 2) {
            std::cout << "aaaaaaaa";
        }

        return intersection_count % 2;
    }

    T& GetX() {
        return x_;
    }

    const T& GetX() const {
        return x_;
    }

    T& GetY() {
        return y_;
    }

    const T& GetY() const {
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

int64_t TriangulationCount(std::vector<Point<int64_t>>& polygon) {
    std::vector<std::vector<int64_t>> dp(polygon.size(), std::vector<int64_t>(polygon.size(), 0));

    for (size_t size = 1; size < polygon.size(); ++size) {
        for (size_t i = 0; i < polygon.size() - size; ++i) {
            size_t j = i + size;
            if (size == 1) {
                dp[i][j] = 1;
            } else {
                for (size_t k = i + 1; k < j; ++k) {
                    if (((polygon[k] - polygon[i]) ^ (polygon[k] - polygon[j])) > 0) {
                        dp[i][j] = (dp[i][j] + dp[i][k] * dp[k][j]) % kMod;
                    }
                }            
            }
        }
    }

    return dp[0][polygon.size() - 1];
}

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<Point<int64_t>> polygon(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> polygon[i];
    }

    int64_t rotation_coefficient = 0;
    for (int i = 0; i < n; ++i) {
        rotation_coefficient += polygon[i] ^ polygon[(i+1) % n];
    }

    if (rotation_coefficient > 0) {
        std::reverse(polygon.begin(), polygon.end());
    }

    std::cout << TriangulationCount(polygon);

    return 0;
}