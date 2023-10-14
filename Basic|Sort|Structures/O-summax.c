//Массивы a и b оба содержат по 1 ⩽ N ⩽ 200000 элементов. Каждый из элементов по абсолютной величине не превосходит 1000000009.
//
//Нужно найти максимальную их всех возможных сумм ai+bj. Вы скажете: задача легчайшая, нужно просто найти максимальные значения массивов a и b и сложить их.
//
//Добавим к задаче обязательное условие: индекс i в сумме ai+bj не должен превосходить индекса j.
//
//Input format
//Первая строка содержит количество элементов каждого массива N.
//
//В следующей строке содержится N элементов первого массива, а в третьей — N элементов — второго массива.
//
//Output format
//Два числа i и j через пробел таких, что i ⩽ j и сумма ai+bj максимальная их всех возможных при имеющихся ограничениях.
//
//Если таких пар несколько — вывести те, в которых пара i,j лексикографически наименьшая.

#include <stdio.h>
#include <stdlib.h>

void summax(int const *arr1, int const *arr2, int N)
{
	int max_sum = arr1[0] + arr2[0], curr_max_elem = arr1[0], idx1 = 0, idx2 = 0, curr_max_idx = 0;
	for (int i = 1; i < N; i++)
	{
		if (curr_max_elem < arr1[i])
		{
			curr_max_elem = arr1[i];
			curr_max_idx = i;
		}
		if (curr_max_elem + arr2[i] > max_sum)
		{
			max_sum = curr_max_elem + arr2[i];
			idx1 = curr_max_idx;
			idx2 = i;
		}
	}
	printf("%d %d", idx1, idx2);
}

int main()
{
	int N = 0;
	scanf("%d", &N);
	int *arr1 = calloc(N, sizeof(int));
	int *arr2 = calloc(N, sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &arr1[i]);
	for (int i = 0; i < N; i++)
		scanf("%d", &arr2[i]);
	summax(arr1, arr2, N);
	free(arr1);
	free(arr2);
}