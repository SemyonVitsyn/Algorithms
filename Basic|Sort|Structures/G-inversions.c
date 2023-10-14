#include <stdio.h>
#include <stdlib.h>

long long unsigned merge_sort(int *arr, int left, int right)
{
	long long unsigned inv_count = 0;
	if (left >= right)
		return 0;
	int middle = left + (right - left) / 2;
	inv_count += merge_sort(arr, left, middle);
	inv_count += merge_sort(arr, middle+1, right);
	int left_ptr = left, right_ptr = middle + 1, idx = 0;
	int *temp_arr = calloc(right - left + 1, sizeof(int));
	while (left_ptr <= middle && right_ptr <= right)
	{
		if (arr[left_ptr] <= arr[right_ptr])
			temp_arr[idx++] = arr[left_ptr++];
		else
		{
			temp_arr[idx++] = arr[right_ptr++];
			inv_count += middle - left_ptr + 1;
		}
	}
	while (left_ptr <= middle)
		temp_arr[idx++] = arr[left_ptr++];
	while (right_ptr <= right)
		temp_arr[idx++] = arr[right_ptr++];
	for (int i = left; i <= right; i++)
		arr[i] = temp_arr[i-left];
	free(temp_arr);
	return inv_count;
}

int main()
{
	int N = 0;
	scanf("%d", &N);
	int *arr = calloc(N, sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	printf("%llu", merge_sort(arr, 0, N-1));
	free(arr);
	return 0;
}
