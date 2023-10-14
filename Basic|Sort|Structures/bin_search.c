#include <stdio.h>
#include <stdlib.h>
// НЕВЕРНО
int bin_search(int const *arr, int n, int elem)
{
	int left = 0, right = n;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (arr[mid] < elem || left == right)
			left = mid;
		else
			right = mid-1;
	}
	return right;
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	int *arr = calloc(n, sizeof(int));
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	int elem = 0;
	while(scanf("%d", &elem) > 0)
		printf("idx = %d\n\n", bin_search(arr, n, elem));
}
