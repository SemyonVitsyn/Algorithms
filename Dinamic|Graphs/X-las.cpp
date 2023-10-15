#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

void largestIncreasingSubarray(int* arr, int N) {
	int* dp = new int[N+1];
	int* pos = new int[N+1]();
	int* prev = new int[N];

	dp[0] = INT_MIN;
	pos[0] = -1;
	for (int i = 1; i <= N; ++i)
		dp[i] = INT_MAX;

	int idx = 0, len = 0;
	for (int i = 0; i < N; ++i) {
		idx = ((std::upper_bound(dp, dp + N, arr[i])) - dp);
		if (dp[idx-1] < arr[i] && arr[i] < dp[idx]) {
			dp[idx] = arr[i];
			pos[idx] = i;
			prev[i] = pos[idx - 1];
			len = std::max(len, idx);
		}
	}

	std::vector<int> answer;
	int p = pos[len];
	while (p != -1) {
		answer.push_back(p);
		p = prev[p];
	}
	std::reverse(answer.begin(), answer.end());

	std::cout << len << '\n';
	for (int i = 0; i < answer.size(); ++i)
		std::cout << answer[i] << " ";

	delete[] pos;
	delete[] dp;
	delete[] prev;
}

int main()
{
	int N = 0;
	std::cin >> N;

	int* arr = new int[N];
	for (int i = 0; i < N; ++i)
		std::cin >> arr[i];

	largestIncreasingSubarray(arr, N);

	delete[] arr;

	return 0;
}
