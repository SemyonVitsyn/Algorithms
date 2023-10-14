#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct segment
{
	int left;
	int right;
	int idx;
	int count;
} Segment;

int compare1(const void* x1, const void* x2)
{
	Segment s1 = *(Segment*)x1;
	Segment s2 = *(Segment*)x2;
	if (s1.right == s2.right)
		return s2.left - s1.left;
	return s1.right - s2.right;
}

int compare2(const void* x1, const void* x2)
{
	Segment s1 = *(Segment*)x1;
	Segment s2 = *(Segment*)x2;
	if (s1.left == s2.left)
		return s2.right - s1.right;
	return s1.left - s2.left;
}

int f(int i)
{
	return i & (i + 1);
}

int g(int i)
{
	return i | (i + 1);
}

void ADD(int* S, int x, int size)
{
	for (int i = x; i < size; i = g(i))
		S[i]++;
}

int PREFIX_SUM(int* S, int x)
{
	int res = 0;
	for (int i = x; i >= 0; i = f(i) - 1)
		res += S[i];
	return res;
}

void REMOVE(int* S, int val, int x, int size)
{
	for (int i = x; i < size; i = g(i))
		S[i] -= val;
}

int* prepare_segments(Segment* segments, int* arr_size, int* tree_size, int N)
{
	int temp_idx = 0;
	*arr_size = 0, *tree_size = 0;
	int* tree = calloc(N, sizeof(int));
	qsort(segments, N, sizeof(Segment), compare1);
	for (int i = 0; i < N; i++)
	{
		if (i != 0 && segments[i].right != segments[temp_idx].right)
			(*tree_size)++;
		if (i != 0 && segments[i].left == segments[temp_idx].left && segments[i].right == segments[temp_idx].right)
		{
			segments[temp_idx].count++;
			segments[i].left = INT_MAX;
		}
		else
		{
			segments[i].idx = *tree_size;
			(*arr_size)++;
			segments[i].count = 1;
			temp_idx = i;
		}
		ADD(tree, *tree_size, N);
	}
	(*tree_size)++;
	qsort(segments, N, sizeof(Segment), compare2);
	return tree;
}

long long segment_embeddings(Segment* segments, int* tree, int arr_size, int tree_size)
{
	long long embeddings = 0;
	for (int i = 0; i < arr_size; i++)
	{
		embeddings += segments[i].count * (PREFIX_SUM(tree, segments[i].idx) - segments[i].count);
		REMOVE(tree, segments[i].count, segments[i].idx, tree_size);
	}
	return embeddings;
}

int main()
{
	int N = 0;
	scanf("%d", &N);
	Segment* segments = calloc(N, sizeof(Segment));
	for (int i = 0; i < N; i++)
		scanf("%d %d", &segments[i].left, &segments[i].right);
	int arr_size = 0, tree_size = 0;
	int* tree = prepare_segments(segments, &arr_size, &tree_size, N);
	printf("%lld", segment_embeddings(segments, tree, arr_size, tree_size));
	free(segments);
	free(tree);
	return 0;
}
