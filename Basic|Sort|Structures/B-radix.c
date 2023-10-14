#include <stdio.h>

void expansion_coefficients(int p, int q)
{
	int curr_coef = 0, curr_denom = 2;
	while (p != 0)
	{
		p *= curr_denom;
		curr_denom++;
		curr_coef = p / q;
		printf("%d ", curr_coef);
		p %= q;
	}
}

int main()
{
	int p = 0, q = 0;
	scanf("%d %d", &p, &q);
	expansion_coefficients(p, q);
	return 0;
}

// Так как в факториальной системе счисления каждое число представимо единственным образом, а a[i] < i,
// то, выбирая на каждом шаге наибольший из возможных коэффициент, мы действительно получим необходимое разложение
// (каждое слагаемое не может быть больше (i-1) / i!, т.е. каждый последующий коэффициент меньше предыдущего и ряд сходится к 1)