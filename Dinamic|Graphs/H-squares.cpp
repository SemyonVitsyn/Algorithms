#include <iostream>
#include <math.h>

int get_min_squares(int N) {

	int* dp = new int[N+1];

	dp[0] = 0;

	for (int i = 1; i <= N; i++) {
		dp[i] = i;
		int mx = sqrt(i);

		for (int j = 1; j <= mx; j++)
			dp[i] = std::min(dp[i], 1 + dp[i-j*j]);
	}

	int answ = dp[N];
	delete[] dp;
	return answ;
}

int main() {

	int N = 0;
	std::cin >> N;
	std::cout << get_min_squares(N);

	return 0;
}
