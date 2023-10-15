#include <iostream>
#include <vector>
#include <iomanip>

long double get_probability(int N, int M) {
	std::vector<std::vector<long double>> dp(N + 1, std::vector<long double> (6*N + 1));
	dp[1][1] = dp[1][2] = dp[1][3] = dp[1][4] = dp[1][5] = dp[1][6] = 1.0 / 6;

	for (int i = 2; i <= N; i++)
		for (int j = i; j <= 6*i; j++)
			for (int k = std::min(6, j); k >= 1; k--)
				if (j - k > 0)
					dp[i][j] += dp[i-1][j-k] / 6;

	return dp[N][M];
}

int main() {
	int N = 0, M = 0;
	std::cin >> N >> M;
	std::cout << std::fixed << std::setprecision(11) << get_probability(N, M) << "\n";
	return 0;
}