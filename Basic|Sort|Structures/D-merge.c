#include <stdio.h>
#include <stdlib.h>

#define mod 1000000000

unsigned long long find_sum(int const *arr, int N)
{
	unsigned long long sum = 0;
	int even = 0, curr_val = 0, idx1 = 0, idx2 = 0;
	scanf("%d", &curr_val);
	while (idx1 < N || idx2 < N)
	{
		if (idx1 < N && idx2 < N)
		{
			if (even == 0)
			{
				if (curr_val > arr[idx1])
				{
					sum += arr[idx1];
					idx1++;
				}
				else
				{
					sum += curr_val;
					idx2++;
					if (idx2 < N)
						scanf("%d", &curr_val);
				}
				sum %= mod;
				even = 1;
			}
			else
			{
				if (curr_val > arr[idx1])
					idx1++;
				else
				{
					idx2++;
					if (idx2 < N)
						scanf("%d", &curr_val);
				}
				even = 0;
			}
		}
		else if (idx2 < N)
		{
			if (even == 0)
			{
				sum += curr_val;
				sum %= mod;
				idx2++;
				even = 1;
			}
			else
			{
				idx2++;
				even = 0;
			}
			if (idx2 < N)
				scanf("%d", &curr_val);
		}
		else
		{
			if (even == 0)
			{
				sum += arr[idx1];
				sum %= mod;
				idx1++;
				even = 1;
			}
			else
			{
				idx1++;
				even = 0;
			}
		}
	}
	return sum;
}

int main()
{
	int N = 0;
	scanf("%d", &N);
	int *arr = calloc(N, sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	printf("%llu", find_sum(arr, N));
	free(arr);
	return 0;
}
