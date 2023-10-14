//Умеете ли вы быстро складывать числа? На вход программы подаётся массив V размером 10⩽N⩽100000 целых чисел, каждое из которых лежит в диапазоне от 1 до 109 и 1⩽M⩽100000 образцов. Для каждого образца требуется определить, существует ли такой подмассив массива V, сумма которого равна точно значению образца.
//
//Input format
//N M
//
//V1
//
//V2
//
//...
//
//VN
//
//P1
//
//P2
//
//...
//
//PM
//
//Output format
//Требуется вывести ровно M строк. Если не существует такого подмассива, сумма элементов которого равна в точности Pi, то нужно вывести строку Not found. Если же такой подмассив имеется, то требуется вывести координаты отрезка, закрытого слева и открытого справа данного подмассива. Нумерация элементов массива начинается с 1.
//
//Обратите внимание на формулировку ответа. Нужно вывести номер левого элемента подмассива с нужной суммой и увеличенный на единицу номер правого элемента.

#include <stdio.h>
#include <stdlib.h>

void find_subarr(unsigned int const *arr, int N, unsigned long long elem)
{
	unsigned long long curr_sum = 0;
	int start_idx = 0, end_idx = 0;
	while (end_idx < N)
	{
		if (curr_sum == elem)
		{
			printf("%d %d\n", start_idx + 1, end_idx + 1);
			return;
		}
		if (curr_sum < elem)
		{
			curr_sum += arr[end_idx];
			end_idx++;
		}
		else
		{
			curr_sum -= arr[start_idx];
			start_idx++;
		}
	}
	printf("Not found\n");
}

int main()
{
	int N = 0, M = 0;
	scanf("%d %d", &N, &M);
	unsigned int *arr = calloc(N, sizeof(unsigned long long));
	for (int i = 0; i < N; i++)
		scanf("%u", &arr[i]);
	unsigned long long elem = 0;
	for (int i = 0; i < M; i++)
	{
		scanf("%lld", &elem);
		find_subarr(arr, N, elem);
	}
	free(arr);
	return 0;
}