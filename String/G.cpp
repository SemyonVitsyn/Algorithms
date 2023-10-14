#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>

const size_t kBase1 = 31;
const size_t kBase2 = 53;

struct PairHash {
    inline std::size_t operator()(const std::pair<size_t, size_t>& v) const {
        return v.first * 31 + v.second;
    }
};

std::vector<size_t> PrecalcBasePower(size_t max_power, size_t base) {
    std::vector<size_t> p(max_power);
    p[0] = 1;
    for (size_t i = 1; i < max_power; ++i) {
        p[i] = p[i - 1] * base;
    }

    return p;
}

void HashPattern(std::string& pattern, std::unordered_set<std::pair<size_t, size_t>, PairHash>& set,
                 std::vector<size_t>& p1, std::vector<size_t>& p2) {
    std::string s = pattern + pattern;
    size_t hash1 = 0;
    size_t hash2 = 0;

    for (size_t i = 0; i < pattern.size(); ++i) {
        hash1 += pattern[i] * p1[pattern.size() - i - 1];
        hash2 += pattern[i] * p2[pattern.size() - i - 1];
    }
    set.insert({hash1, hash2});

    for (size_t shift = 1; shift < pattern.size(); ++shift) {
        hash1 -= s[shift - 1] * p1[pattern.size() - 1];
        hash2 -= s[shift - 1] * p2[pattern.size() - 1];
        hash1 *= kBase1;
        hash2 *= kBase2;
        hash1 += s[shift + pattern.size() - 1];
        hash2 += s[shift + pattern.size() - 1];

        set.insert({hash1, hash2});
    }
}

size_t CyclicEntrisQuantity(std::string& pattern, std::string& text) {
    std::vector<size_t> p1 = PrecalcBasePower(pattern.size(), kBase1);
    std::vector<size_t> p2 = PrecalcBasePower(pattern.size(), kBase2);
    size_t answer = 0;
    std::unordered_set<std::pair<size_t, size_t>, PairHash> set;

    HashPattern(pattern, set, p1, p2);

    size_t hash1 = 0;
    size_t hash2 = 0;
    for (size_t i = 0; i < pattern.size(); ++i) {
        hash1 += text[i] * p1[pattern.size() - i - 1];
        hash2 += text[i] * p2[pattern.size() - i - 1];
    }
    if (set.find({hash1, hash2}) != set.end()) {
        answer++;
    }

    for (size_t shift = 1; shift <= text.size() - pattern.size(); ++shift) {
        hash1 -= text[shift - 1] * p1[pattern.size() - 1];
        hash2 -= text[shift - 1] * p2[pattern.size() - 1];
        hash1 *= kBase1;
        hash2 *= kBase2;
        hash1 += text[shift + pattern.size() - 1];
        hash2 += text[shift + pattern.size() - 1];

        if (set.find({hash1, hash2}) != set.end()) {
            answer++;
        }
    }

    return answer;
}

int main() {
    std::string pattern;
    std::string text;
    std::cin >> pattern >> text;
    if (pattern.size() > text.size()) {
        std::cout << 0;
    } else {
        std::cout << CyclicEntrisQuantity(pattern, text);
    }
    return 0;
}