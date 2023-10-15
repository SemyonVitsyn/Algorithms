#include <iostream>

int palindromes(std::string& str) {
	int** dp = new int*[str.size()];
	for (int i = 0; i < str.size(); ++i)
		dp[i] = new int[str.size()]();

	for (int i = 0; i < str.size(); ++i)
		dp[i][i] = 1;

	for (int len = 2; len <= str.size(); ++len)
		for (int start = 0; start + len <= str.size(); ++start) {
			int end = start + len - 1;
			if (str[start] == str[end])
				dp[start][end] += dp[start][end-1] + dp[start+1][end] + 1;
			else
				dp[start][end] += dp[start][end-1] + dp[start+1][end] - dp[start+1][end-1];
		}

	int answer = dp[0][str.size()-1];

	for (int i = 0; i < str.size(); i++)
		delete[] dp[i];
	delete[] dp;

	return answer;
}

int main() {
	std::string input;
	std::cin >> input;

	std::cout << palindromes(input);

	return 0;
}
