#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <cfloat>

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

template <typename T>
class Line {
public:
    Line(Point<T> start, Point<T> end)
        : a_((start - end).GetY())
        , b_((end - start).GetX())
        , c_(start.GetX() * end.GetY() - start.GetY() * end.GetX()) {
    }

    double Dist(Point<T> dot) const {
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

    double Dist(Point<T> dot) const {  //Формула Хари
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
               ((Area(start_, end_, other.start_) >= 0 && Area(start_, end_, other.end_) <= 0) || (Area(start_, end_, other.start_) <= 0 && Area(start_, end_, other.end_) >= 0)) &&
               ((Area(other.start_, other.end_, start_) >= 0 && Area(other.start_, other.end_, end_) <= 0) || (Area(other.start_, other.end_, start_) <= 0 && Area(other.start_, other.end_, end_) >= 0));
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

std::vector<Point<int64_t>> Normalize(std::vector<Point<int64_t>>& polygon) {
    std::vector<Point<int64_t>> answer;
    size_t idx = 0;
    Point<int64_t> min = polygon[0];
    for (size_t i = 0; i < polygon.size(); ++i) {
        if (min > polygon[i]) {
            min = polygon[i];
            idx = i;
        }
    }

    for (size_t i = 0; i < polygon.size(); ++i) {
        answer.push_back(polygon[(i + idx) % polygon.size()]);
    }   

    return answer;
}

std::vector<Point<int64_t>> RevPolygon(const std::vector<Point<int64_t>>& polygon) {
    std::vector<Point<int64_t>> temp(polygon.size());
    size_t idx = 0;
    Point<int64_t> min = -polygon[0];
    for (size_t i = 0; i < temp.size(); ++i) {
        temp[i] = -polygon[i];
        if (min > temp[i]) {
            min = temp[i];
            idx = i;
        }
    }

    std::vector<Point<int64_t>> answer;
    for (size_t i = idx; i < temp.size(); ++i) {
        answer.push_back(temp[i]);
    }
    for (size_t i = 0; i < idx; ++i) {
        answer.push_back(temp[i]);
    }

    return answer;
}

std::vector<Point<int64_t>> MinkowskiAddition(std::vector<Point<int64_t>> polygon1,
                                              std::vector<Point<int64_t>> polygon2) {
    polygon1.push_back(polygon1[0]);
    polygon1.push_back(polygon1[1]);
    polygon2.push_back(polygon2[0]);
    polygon2.push_back(polygon2[1]);

    std::vector<Point<int64_t>> answer;
    size_t i = 0;
    size_t j = 0;

    while (i < polygon1.size() - 2 || j < polygon2.size() - 2) {
        answer.push_back(polygon1[i] + polygon2[j]);

        if (((polygon1[i + 1] - polygon1[i]) ^ (polygon2[j + 1] - polygon2[j])) >= 0) {
            i++;
        } else if (((polygon1[i + 1] - polygon1[i]) ^ (polygon2[j + 1] - polygon2[j])) <= 0) {
            j++;
        }
    }

    return answer;
}

double MinDist(std::vector<Point<int64_t>>& polygon1, std::vector<Point<int64_t>>& polygon2) {
    auto normalized_polygon1 = Normalize(polygon1);
    auto rev_polygon2 = RevPolygon(polygon2);
    auto polygon = MinkowskiAddition(normalized_polygon1, rev_polygon2);

    Point<int64_t> dot = {0, 0};
    if (dot.Inside(polygon)) {
        double answer = DBL_MAX;
        for (size_t i = 0; i < polygon.size(); ++i) {
            LineSegment<int64_t> segment(polygon[i], polygon[(i + 1) % polygon.size()]);
            answer = std::min(answer, segment.Dist(dot));
        }

        answer = std::max(0.0, answer - 60);

        return answer;
    }

    return 0;
}

int main() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    std::vector<Point<int64_t>> airport(n);
    std::vector<Point<int64_t>> cloud(m);

    for (int i = 0; i < n; ++i) {
        std::cin >> airport[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> cloud[i];
    }

    std::cout << std::setprecision(20) << std::fixed << MinDist(airport, cloud);

    return 0;
}