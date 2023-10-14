#include <stdio.h>
#include <stdlib.h>

int round_up(int x, int y)
{
	return (x - 1) / y + 1;
}

int check_count(int *arr, int n, int p, int q, int count)
{
	int remain = count;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] - q * count > 0)
		{
			remain -= round_up(arr[i] - q * count, p-q);
			if (remain < 0)
				return 0;
		}
	}
	return 1;
}

void find_min_count(int left, int right, int *arr, int n, int p, int q, int *min_count)
{
	if (left > right)
		return;
	int mid = left + (right - left) / 2;
	if (check_count(arr, n, p, q, mid))
	{
		*min_count = mid;
		return find_min_count(left, mid - 1, arr, n, p, q, min_count);
	}
	else
		return find_min_count(mid + 1, right, arr, n, p, q, min_count);
}

int main()
{
	int n = 0, p = 0, q = 0;
	scanf("%d %d %d", &n, &p, &q);
	int *arr = calloc(n, sizeof(int));
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
		if (arr[i] > max)
			max = arr[i];
	}
	if (p == q)
		printf("%d", round_up(max, q));
	else
	{
		int min_count = 0;
		find_min_count(1, round_up(max, q), arr, n, p, q, &min_count);
		printf("%d", min_count);
	}
	free(arr);
	return 0;
}
