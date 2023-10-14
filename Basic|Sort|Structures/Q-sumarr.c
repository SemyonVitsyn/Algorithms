//Имеется массив V целых чисел, состоящий из 1⩽N⩽108 элементов, −2×109⩽Vi⩽2×109. Требуется найти наибольшую из возможных сумм всех подмассивов.
//
//Input format
//N
//
//V1
//
//V2
//
//...
//
//VN
//
//Output format
//MaximalSubarraysSum

#include <stdio.h>

long long int max(long long int elem1, long long int elem2)
{
	return (elem1 > elem2) ? elem1 : elem2;
}

int main()
{
	long long int N = 0, temp = 0, sum = 0, curr = 0;
	scanf("%lld", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%lld", &curr);
		if (i == 0)
			sum = curr;
		temp += curr;
		sum = max(temp, sum);
		if (temp < 0)
			temp = 0;
	}
	printf("%lld", sum);
}