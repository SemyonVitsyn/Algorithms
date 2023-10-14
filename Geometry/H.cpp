#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <list>
#include <set>

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

    Point operator*(const double k) const {
        return {k * x_, k * y_};
    }

    T operator^(const Point& other) const {
        return x_ * other.y_ - y_ * other.x_;
    }

    bool operator==(const Point other) const {
        return x_ == other.x_ && y_ == other.y_;
    }

    bool operator!=(const Point& other) const {
        return x_ != other.x_ || y_ != other.y_;
    }

    bool operator<(const Point& other) const {
        return (x_ < other.x_) || (x_ == other.x_ && y_ < other.y_);
    }

    bool operator>(const Point& other) const {
        return (x_ > other.x_) || (x_ == other.x_ && y_ > other.y_);
    }

    bool operator<=(const Point& other) const {
        return (x_ < other.x_) || (x_ == other.x_ && y_ <= other.y_);
    }

    bool operator>=(const Point& other) const {
        return (x_ > other.x_) || (x_ == other.x_ && y_ >= other.y_);
    }

    double Dist(Point other) const {
        return sqrt((x_ - other.x_) * (x_ - other.x_) + (y_ - other.y_) * (y_ - other.y_));
    }

    double Sq() const {
        return sqrt(x_ * x_  + y_ * y_);
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

Point<double> NormalizeVector(Point<double> vector) {
    return {vector.GetX() / vector.Sq(), vector.GetY() / vector.Sq()};
}

Point<double> Between(Point<double> first, Point<double> second) {
    return {(first + second).GetX() / 2, (first + second).GetY() / 2};
}

Point<double> Round(Point<double> v) {
    return {(std::round(v.GetX())), (std::round(v.GetY()))};
}

int main() {
    int n = 0;
    std::cin >> n;
    
    std::vector<Point<double>> pillars(n);
    std::set<Point<double>> set;
    for (int i = 0; i < n; ++i) {
        std::cin >> pillars[i];
        set.insert(pillars[i]);
    }

    int64_t answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Point<double> vector((pillars[i] - pillars[j]).GetY(), (pillars[j] - pillars[i]).GetX());
            auto norm = NormalizeVector(vector);
            auto center = Between(pillars[i], pillars[j]);
            double dist = center.Dist(pillars[i]);
            
            Point<double> diag[2] = {center + norm * dist, center + norm * (-dist)};
            if (std::abs((Round(diag[0]) - diag[0]).GetX()) < 1e-9 && std::abs((Round(diag[0]) - diag[0]).GetY()) < 1e-9 && std::abs((Round(diag[1]) - diag[1]).GetX()) < 1e-9 && std::abs((Round(diag[1]) - diag[1]).GetY()) < 1e-9) {
                if (set.count(Round(diag[0])) && set.count(Round(diag[1]))) {
                    answer++;
                }
            }
        }
    }

    std::cout << answer / 2;

    return 0;
}