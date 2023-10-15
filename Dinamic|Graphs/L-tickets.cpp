#include <iostream>
#include <vector>
#include <iomanip>

class bigInt {
private:
	std::vector<int> num;
	static const int base = 1000000000;

public:
	bigInt() = default;
	~bigInt() = default;

	bigInt& operator=(int val);
	bigInt& operator+=(const bigInt& add);

	friend bigInt operator+(bigInt lhs, const bigInt& rhs) {
		int carry = 0;
		for (int i = 0; i < std::max(lhs.num.size(), rhs.num.size()) || carry > 0; ++i) {
			if (i == lhs.num.size())
				lhs.num.push_back(0);
			lhs.num[i] += carry + (i < rhs.num.size() ? rhs.num[i] : 0);
			carry = lhs.num[i] >= base;
			if (carry > 0)
				lhs.num[i] -= base;
		}

		return lhs;
	}

	friend std::ostream& operator<<(std::ostream &out, const bigInt& elem) {
		if (elem.num.empty())
			out << 0;
		else {
			out << elem.num.back();
			for (int i = (int)elem.num.size() - 2; i >= 0; --i)
				out << std::setfill('0') << std::setw(9) << elem.num[i];
		}

		return out;
	}
};

bigInt& bigInt::operator=(int val) {
	num.push_back(val);
	return *this;
}

bigInt& bigInt::operator+=(const bigInt& add) {
	return *this = (*this + add);
}


bigInt luckyTickets(int N, int M) {
	bigInt** matrix = new bigInt*[N+1];
	for (int i = 0; i <= N; ++i)
		matrix[i] = new bigInt[(N/2)*(M-1) + 1];

	for (int j = 0; j < M; ++j)
		matrix[1][j] = 1;

	for (int i = 2; i <= N; ++i)
		for (int j = 0; j <= std::min(i*(M-1), (N/2)*(M-1)); ++j)
			for (int k = 0; k < M && j-k >= 0; ++k)
				matrix[i][j] += matrix[i-1][j-k];

	bigInt answer = matrix[N][(N/2)*(M-1)];

	for (int i = 0; i <= N; i++)
		delete[] matrix[i];
	delete[] matrix;

	return answer;
}

int main() {
	int N = 0, M = 0;

	std::cin >> N >> M;

	std::cout << luckyTickets(N, M);

	return 0;
}
