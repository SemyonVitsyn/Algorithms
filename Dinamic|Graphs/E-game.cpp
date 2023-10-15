#include <iostream>
#include <math.h>

void get_winner(int N) {
	int* dp = new int[N+1];
	dp[0] = 0;

	for (int i = 1; i <= N; i++) {
		int step = sqrt(i);
		dp[i] = 0;

		for (int j = 1; j <= step; j++)
			if (dp[i-j] == 0) {
				dp[i] = 1;
				break;
			}
	}

	if (dp[N] == 1)
		std::cout << "First";
	else
		std::cout << "Second";

	delete[] dp;
}

int main() {
	int N;
	std::cin >> N;
	get_winner(N);
	return 0;
}
