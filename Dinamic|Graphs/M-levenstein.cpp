#include <iostream>

int minimal_penalty(const std::string& first, const std::string& second) {
	int** dp = new int*[first.size() + 1];
	for (int i = 0; i <= first.size(); i++)
		dp[i] = new int[second.size() + 1];

	for (int i = 0; i <= first.size(); i++)
		dp[i][0] = i;

	for (int j = 1; j <= second.size(); j++)
		dp[0][j] = j;

	for (int i = 1; i <= first.size(); i++)
		for (int j = 1; j <= second.size(); j++)
			dp[i][j] = std::min(std::min(dp[i-1][j] + 1, dp[i][j-1] + 1),
			                    ((first[i-1] == second[j-1])? (dp[i-1][j-1]) : (dp[i-1][j-1] + 1)));

	int answ = dp[first.size()][second.size()];

	for (int i = 0; i <= first.size(); i++)
		delete[] dp[i];
	delete[] dp;

	return answ;
}

int main() {
	std::string first, second;
	std::cin >> first >> second;
	std::cout << minimal_penalty(first, second);
	return 0;
}
