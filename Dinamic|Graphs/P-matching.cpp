#include <iostream>
#include <vector>

void matching(const std::string& word, const std::string& pattern) {
	std::vector<std::vector<bool>> dp(pattern.size() + 1, std::vector<bool>(word.size() + 1, false));
	dp[0][0] = true;

	for (int i = 1; i <= pattern.size(); ++i)
		for (int j = 1; j <= word.size(); ++j)
			if (pattern[i-1] == '?' || pattern[i-1] == word[j-1])
				dp[i][j] = dp[i-1][j-1];
			else if (pattern[i-1] == '*') {
				if (i == 1 && j == 1)
					dp[i][j] = true;
				else
					dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
				if (j == 1 && dp[i-1][j-1])
					dp[i][j-1] = true;
			}

	if (dp[pattern.size()][word.size()])
		std::cout << "YES";
	else
		std::cout << "NO";
}

int main() {
	std::string word, pattern;
	std::cin >> word >> pattern;

	matching(word, pattern);

	return 0;
}
