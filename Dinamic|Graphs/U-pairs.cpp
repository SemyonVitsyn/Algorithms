#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <cfloat>
#include <cassert>

double dist(std::pair<long long, long long> p1, std::pair<long long, long long> p2) {
	return sqrt((double)((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second)));
}

double splitDistance(std::vector<double>& dp, const std::vector<std::pair<long long, long long>>& coord, long long mask, int N) {
	if (mask == 0)
		return 0;

	if (dp[mask] > 0)
		return dp[mask];

	double answer = DBL_MAX;
	for (int i = N - 1; i >= 0; --i)
		if ((1 << i & mask) != 0) {
			for (int j = i - 1; j >= 0; --j)
				if ((1 << j & mask) != 0)
					answer = std::min(answer,dist(coord[i], coord[j]) + splitDistance(dp, coord, mask - (1 << i) - (1 << j), N));
			break;
		}

	dp[mask] = answer;
	return answer;
}

int main()
{
	int N = 0;
	std::cin >> N;
	assert(N % 2 == 0);
	std::vector<std::pair<long long, long long>> coord(N);
	std::vector<double> dp(1<<N, 0);

	for (int i = 0; i < N; ++i) {
		long long a = 0, b = 0;
		std::cin >> a >> b;
		coord[i] = std::make_pair(a, b);
	}

	double answer = splitDistance(dp, coord, (1<<N) - 1, N);

	std::cout << std::fixed;
	std::cout.precision(3);
	std::cout << answer;

	return 0;
}
