#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <vector>

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
T AreaBelow(Point<T> start, Point<T> end) {
    return (end - start).GetX() * (start + end).GetY();
}

template <typename T>
T Area(Point<T> a, Point<T> b, Point<T> c) {
    return (b - a).GetX() * (c - a).GetY() - (b - a).GetY() * (c - a).GetX();
}

std::vector<int64_t> Normalize(std::vector<Point<int64_t>> polygon) {
    int64_t rotation_coefficient = 0;
    for (size_t i = 0; i < polygon.size(); ++i) {
        rotation_coefficient += polygon[i] ^ polygon[(i+1) % polygon.size()];
    }

    bool reversed = rotation_coefficient > 0;

    std::vector<int64_t> answer;
    size_t idx = 0;
    Point<int64_t> min = polygon[0];
    for (size_t i = 0; i < polygon.size(); ++i) {
        if (min > polygon[i]) {
            min = polygon[i];
            idx = i;
        }
    }

    if (reversed) {
        for (size_t i = 0; i < polygon.size(); ++i) {
            answer.push_back(static_cast<int64_t>((static_cast<int64_t>(idx) - i + polygon.size()) % polygon.size()));
        }
    } else {
        for (size_t i = 0; i < polygon.size(); ++i) {
            answer.push_back(static_cast<int64_t>((i + idx) % polygon.size()));
        } 
    }  

    return answer;
}

int64_t FenwickSum(std::vector<int64_t>& fenwick_tree, int len) {
    int64_t answer = 0;
    for (; len > 0; len &= (len - 1)) {
        answer += fenwick_tree[len - 1];
    }

    return answer;
}

void FenwickAdd(std::vector<int64_t>& fenwick_tree, int pos, int64_t val) {
    for (; pos < static_cast<int>(fenwick_tree.size()); pos |= (pos + 1)) {
        fenwick_tree[pos] += val;
    }
}

std::pair<int64_t, int64_t> CalcArea(int64_t v1, int64_t v2, std::vector<int64_t>& fenwick_tree, std::vector<Point<int64_t>>& pillars, std::vector<int64_t>& polygon, int64_t area) {
    if (v1 > v2) {
        std::swap(v1, v2);
    }
    
    int64_t area1 = 0;
    if (v1 > 0) {
        area1 += FenwickSum(fenwick_tree, static_cast<int>(v1));
    }
    area1 += area - FenwickSum(fenwick_tree, static_cast<int>(v2));
    area1 += AreaBelow(pillars[polygon[v1]], pillars[polygon[v2]]);

    int64_t area2 = area - area1;
    if (area1 > area2) {
        std::swap(area1, area2);
    }

    return {area1, area2};
}

int main() {
    int n = 0;
    std::cin >> n;
    
    std::vector<Point<int64_t>> pillars(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> pillars[i];
    }

    auto polygon = Normalize(pillars);

    std::vector<int64_t> polygon_pos(n);
    for (int i = 0; i < n; ++i) {
        polygon_pos[polygon[i]] = i;
    }

    std::vector<int64_t> fenwick_tree(n);
    std::vector<int64_t> areas(n);
    int64_t area = 0;

    for (size_t i = 0; i < polygon.size(); ++i) {
        Point<int64_t> p1 = pillars[polygon[i]];
        Point<int64_t> p2 = pillars[polygon[(i + 1) % polygon.size()]];

        areas[i] = AreaBelow(p1, p2);
        area += areas[i];
        FenwickAdd(fenwick_tree, static_cast<int>(i), areas[i]);
    }

    int q = 0;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int request_type = 0;
        std::cin >> request_type;

        if (request_type == 1) {
            int64_t v1 = 0;
            int64_t v2 = 0;
            std::cin >> v1 >> v2;

            v1 = polygon_pos[v1 - 1];
            v2 = polygon_pos[v2 - 1];

            auto answer = CalcArea(v1, v2, fenwick_tree, pillars, polygon, area);

            std::cout << answer.first / 2;
            if (answer.first % 2 == 1) {
                std::cout << ".5";
            }
            std::cout << ' ';

            std::cout << answer.second / 2;
            if (answer.second % 2 == 1) {
                std::cout << ".5";
            }
            std::cout << '\n';
        } else if (request_type == 2) {
            int64_t v = 0;
            Point<int64_t> new_dot;

            std::cin >> v >> new_dot;
            v = polygon_pos[v - 1];

            pillars[polygon[v]] = new_dot;
            auto prev = static_cast<int64_t>((v - 1 + n) % n);
            auto prev_area = AreaBelow(pillars[polygon[prev]], pillars[polygon[v]]);
            int64_t dif = prev_area - areas[prev];
            areas[prev] += dif;
            area += dif;
            FenwickAdd(fenwick_tree, static_cast<int>(prev), dif);

            auto next = static_cast<int64_t>((v + 1) % n);
            auto next_area = AreaBelow(pillars[polygon[v]], pillars[polygon[next]]);
            dif = next_area - areas[v];
            areas[v] += dif;
            area += dif;
            FenwickAdd(fenwick_tree, static_cast<int>(v), dif);
        }
    }

    return 0;
}