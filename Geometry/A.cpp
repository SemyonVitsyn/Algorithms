#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

template <typename T>
class Point {
public:
    Point(T x, T y) : x_(x), y_(y) {
    }

    Point operator+(Point subtrahend) const {
        return {x_ + subtrahend.x_, y_ + subtrahend.y_};
    }

    Point operator-(Point subtrahend) const {
        return {x_ - subtrahend.x_, y_ - subtrahend.y_};
    }

    Point operator*(int k) const {
        return {k * x_, k * y_};
    }

    double Dist(Point other) const {
        return sqrt((x_ - other.x_) * (x_ - other.x_) + (y_ - other.y_) * (y_ - other.y_));
    }

    T GetX() const {
        return x_;
    }

    T GetY() const {
        return y_;
    }

private:
    T x_ = 0;
    T y_ = 0;
};

template <typename T>
class Line {
public:
    Line(Point<T> start, Point<T> end)
        : a_((start - end).GetY())
        , b_((end - start).GetX())
        , c_(start.GetX() * end.GetY() - start.GetY() * end.GetX()) {
    }

    double Dist(Point<T> dot) const {
        auto val = static_cast<double>(abs(a_ * dot.GetX() + b_ * dot.GetY() + c_)) / sqrt(a_ * a_ + b_ * b_);
        std::cout << val << '\n';
        return static_cast<double>(abs(a_ * dot.GetX() + b_ * dot.GetY() + c_)) / sqrt(a_ * a_ + b_ * b_);
    }

    int GetA() const {
        return a_;
    }

    int GetB() const {
        return b_;
    }

    int GetC() const {
        return c_;
    }

private:
    T a_ = 0;
    T b_ = 0;
    T c_ = 0;
};

template <typename T>
class LineSegment {
public:
    LineSegment(Point<T> start, Point<T> end) : start_(start), end_(end) {
    }

    double Dist(Point<T> dot) const {           //Формула Хари
        auto t = static_cast<double>((dot.GetX() - start_.GetX()) * (end_.GetX() - start_.GetX()) +
                                     (dot.GetY() - start_.GetY()) * (end_.GetY() - start_.GetY())) /
                 ((end_.GetX() - start_.GetX()) * (end_.GetX() - start_.GetX()) +
                  (end_.GetY() - start_.GetY()) * (end_.GetY() - start_.GetY()));

        if (t < 0) {
            t = 0;
        } else if (t > 1) {
            t = 1;
        }

        return sqrt((start_.GetX() - dot.GetX() + (end_.GetX() - start_.GetX()) * t) *
                        (start_.GetX() - dot.GetX() + (end_.GetX() - start_.GetX()) * t) +
                    (start_.GetY() - dot.GetY() + (end_.GetY() - start_.GetY()) * t) *
                        (start_.GetY() - dot.GetY() + (end_.GetY() - start_.GetY()) * t));
    }

    bool Intersect(LineSegment other) const {
        return Intersect1(start_.GetX(), end_.GetX(), other.start_.GetX(), other.end_.GetX()) &&
               Intersect1(start_.GetY(), end_.GetY(), other.start_.GetY(), other.end_.GetY()) &&
               Area(start_, end_, other.start_) * Area(start_, end_, other.end_) <= 0 &&
               Area(other.start_, other.end_, start_) * Area(other.start_, other.end_, end_) <= 0;
    }

    double Dist(LineSegment other) const {
        if (Intersect(other)) {
            return 0;
        }

        return std::min({Dist(other.start_), Dist(other.end_), other.Dist(start_), other.Dist(end_)});
    }

private:
    bool Intersect1(int a, int b, int c, int d) const {
        if (a > b) {
            std::swap(a, b);
        }
        if (c > d) {
            std::swap(c, d);
        }

        return std::max(a, c) <= std::min(b, d);
    }

private:
    Point<T> start_ = {0, 0};
    Point<T> end_ = {0, 0};
};

template <typename T>
T Area(Point<T> a, Point<T> b, Point<T> c) {
    return (b - a).GetX() * (c - a).GetY() - (b - a).GetY() * (c - a).GetX();
}

int main() {
    int64_t x1 = 0;
    int64_t x2 = 0;
    int64_t y1 = 0;
    int64_t y2 = 0;

    std::cin >> x1 >> y1 >> x2 >> y2;
    LineSegment<int64_t> first({x1, y1}, {x2, y2});
    std::cin >> x1 >> y1 >> x2 >> y2;
    LineSegment<int64_t> second({x1, y1}, {x2, y2});

    std::cout << std::setprecision(10) << std::fixed << first.Dist(second);

    return 0;
}