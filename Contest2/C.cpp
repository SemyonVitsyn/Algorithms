#include <iostream>
#include <vector>
#include <climits>

int GCD(int a, int b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> array(n);
    int units_count = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
        if (array[i] == 1) {
            units_count++;
        }
    }

    if (units_count > 0) {
        std::cout << n - units_count;
    } else {
        int answer = INT_MAX;
        for (int i = 0;  i < n; ++i) {
            int val = array[i];
            for (int j = i + 1; j < n; ++j) {
                val = GCD(val, array[j]);
                if (val == 1) {
                    answer = std::min(j - i + n - 1, answer);
                    break;
                }
            }
        }
        if (answer < INT_MAX) {
            std::cout << answer;
        } else {
            std::cout << -1;
        }
    }

    return 0;
}