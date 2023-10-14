#include <stdio.h>
#include <stdlib.h>

size_t get_time()
{
	size_t val = 0, res;
	scanf("%zu", &val);
	res = val * 3600;
	getchar();
	scanf("%zu", &val);
	res += (val * 60);
	getchar();
	scanf("%zu", &val);
	res += val;
	return res;
}

int compare(const void *elem1, const void *elem2)
{
	return *(int*)elem1 - *(int*)elem2;
}

size_t find_max(size_t *start, size_t *end, int N)
{
	qsort(start, N, sizeof(size_t), compare);
	qsort(end, N, sizeof(size_t), compare);
	size_t idx1 = 0, idx2 = 0, max = 0, curr = 0;
	while (idx1 < N)
	{
		if (start[idx1] <= end[idx2])
		{
			idx1++;
			curr++;
			if (max < curr)
				max = curr;
		}
		else
		{
			idx2++;
			curr--;
		}
	}
	return max;
}

int main()
{
	int N = 0;
	scanf("%d", &N);
	size_t *start = calloc(N, sizeof(size_t));
	size_t *end = calloc(N, sizeof(size_t));
	for (int i = 0; i < N; i++)
	{
		start[i] = get_time();
		end[i] = get_time();
	}
	printf("%zu", find_max(start, end, N));
	free(start);
	free(end);
	return 0;
}
