#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	int N = 0, val = 0, sum = 0, prev = 0;
	std::cin >> N;
	std::vector<int> X;

	for (int i = 0; i < N; i++) {
		std::cin >> val;
		X.push_back(val);
	}

	std::sort(X.begin(), X.end());

	if (N == 2) {
		std::cout << X[1] - X[0];
	}
	else {
		prev = X[1] - X[0];
		sum = X[2] - X[0];
		for (int i = 2; i < X.size() - 1; i++) {
			val = sum;
			sum = std::min(sum, prev) + X[i + 1] - X[i];
			prev = val;
		}
		std::cout << sum;
	}

	return 0;
}
