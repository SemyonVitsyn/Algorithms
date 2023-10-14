//Натуральные числа от 1 до N упорядочены лексикографически. Например, для N=25 результат этого упорядочения будет таким: 1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 2, 20, 21, 22, 23, 24, 25, 3, 4, 5, 6, 7, 8, 9.
//
//Требуется написать программу, которая определит, на каком месте в данной последовательности оказалось число K.
//
//Input format
//N K
//
//1⩽K⩽N⩽100000000
//
//Output format
//Выход должен содержать одно натуральное число — номер места, на котором оказалось число K

#include <stdio.h>

void find_elem(int curr_value, int *idx, int N, int K)
{
	if (curr_value > N)
		return;
	if (curr_value == K)
	{
		printf("%d", *idx);
		return;
	}
	(*idx)++;
	find_elem(curr_value * 10, idx, N, K);
	if (curr_value % 10 != 9)
		find_elem(curr_value + 1, idx, N, K);
}

int main()
{
	int N = 0, K = 0;
	scanf("%d %d", &N, &K);
	int idx = 1;
	find_elem(1, &idx, N, K);
	return 0;
}