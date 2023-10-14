#include <iostream>
#include <unordered_map>

const int64_t kMod = 119;
int a = 0;
int b = 0;
int p = 0;
int q = 0;
std::unordered_map<int, int64_t> map;

int64_t RecursiveProportion(int n) {
    if (n <= 0) {
        return 1;
    }

    if (map.count(n)) {
        return map[n];
    } 

    int64_t val = (a * RecursiveProportion(n - p) + b * RecursiveProportion(n - q)) % kMod;
    map.insert({n, val});
    return val;
}

int main() {
    int n = 0;
    std::cin >> n >> a >> b >> p >> q;
    std::unordered_map<int, int64_t> map;
    std::cout << RecursiveProportion(n);
    return 0;
}