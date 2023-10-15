#include <iostream>
#include <vector>
#include <climits>

long long minCost(const std::vector<std::vector<int>>& cost, const std::vector<int>& dist, int N, int M) {
	std::vector<std::vector<std::vector<long long>>>
			dp(2, std::vector<std::vector<long long>>(1 << M, std::vector<long long>(2, 0)));

	for (int i = 0; i < N; ++i) {

		dp[i%2][0][1] = dist[i];
		for (int j = 0; j < (1 << M); ++j) {
			if (i != 0)
				dp[i%2][j][0] = std::min(dp[(i-1)%2][j][0], dp[(i-1)%2][j][1]);
			else if (j > 0)
				dp[i%2][j][0] = INT_MAX;

			dp[i%2][j][1] = INT_MAX;
		}

		for (int j = 0; j < (1 << M); ++j)
			for (int k = 0; k < M; ++k)
				dp[i%2][j|(1<<k)][1] = std::min(dp[i%2][j|(1<<k)][1], dp[i%2][j][0] + dist[i] + cost[i][k]);

		for (int j = 0; j < (1 << M); ++j)
			for (int k = 0; k < M; ++k)
				dp[i%2][j|(1<<k)][1] = std::min(dp[i%2][j|(1<<k)][1], dp[i%2][j][1] + cost[i][k]);
	}

	return std::min(dp[(N-1)%2][(1<<M)-1][0], dp[(N-1)%2][(1<<M)-1][1]);
}

int main() {
	int N = 0, M = 0;
	std::cin >> N >> M;

	std::vector<int> dist(N);
	std::vector<std::vector<int>> cost(N, std::vector<int>(M));

	for (int i = 0; i < N; ++i) {
		std::cin >> dist[i];
		for (int j = 0; j < M; ++j)
			std::cin >> cost[i][j];
	}

	std::cout << minCost(cost, dist, N, M);

	return 0;
}
