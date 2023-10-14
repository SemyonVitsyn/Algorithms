//У покупателя имеется набор N монет A1⩽A2⩽···⩽AN, каждой монеты ровно по одной штуке.
//
//Найти наименьшую стоимость предмета, который нельзя купить без сдачи, используя только эти монеты.
//
//Input format
//N
//
//A1
//
//A2
//
//...
//
//AN
//
//Output format
//TheMinimalCostOfItemCantBuy

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int* form_array(int N)
{
	int *arr = calloc(N, sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	return arr;
}

int find_min_cost(int *arr, int N)
{
	assert(N);
	assert(arr);
	int min_cost = 1;
	for (int i = 0, available_value = 0; i < N; i++)
	{
		if (arr[i] <= available_value + 1)
		{
			available_value += arr[i];
			min_cost = available_value + 1;
		}
		else
			return min_cost;
	}
	return min_cost;
}

int main()
{
	int N = 0;
	scanf("%d", &N);
	int *arr = form_array(N);
	find_min_cost(arr, N);
	printf("%d", find_min_cost(arr, N));
	free(arr);
	return 0;
}