//Умеете ли вы быстро искать нужное? На вход программы подаётся массив V размером 10⩽N⩽100000 целых чисел, каждое из которых лежит в диапазоне от -109 до 109 и 1⩽M⩽100000 образцов. Для каждого образца требуется определить, существует ли такая пара чисел, принадлежащих массиву, которая даёт в сумме ровно значение образца.
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
//Требуется вывести ровно M строк. Если не существует такой пары чисел в массиве, сумма которых равна Pi, то нужно вывести строку Not found. Если же такая пара существует, нужно её вывести в порядке неубывания. Если таких пар несколько, вывести ту из возможных пар, первый элемент которой наименьший из всех возможных.

#include <stdio.h>
#include <stdlib.h>

int compare(const void *elem1, const void *elem2)
{
	return *((int*)elem1) - *((int*)elem2);
}

void find_pair(int *arr, int N, int elem)
{
	int start_idx = 0, end_idx = N-1;
	while (start_idx < end_idx)
	{
		if (arr[start_idx] + arr[end_idx] == elem)
		{
			printf("%d %d\n", arr[start_idx], arr[end_idx]);
			return;
		}
		if (arr[start_idx] + arr[end_idx] < elem)
			start_idx++;
		else
			end_idx--;
	}
	printf("Not found\n");
}

int main()
{
	int N = 0, M = 0;
	scanf("%d %d", &N, &M);
	int *arr = calloc(N, sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	qsort(arr, N, sizeof(int), compare);
	int elem = 0;
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &elem);
		find_pair(arr, N, elem);
	}
	free(arr);
	return 0;
}