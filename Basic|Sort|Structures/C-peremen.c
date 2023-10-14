#include <stdio.h>
#include <stdlib.h>

int min(int x1, int x2)
{
	return (x1 < x2)? x1 : x2;
}

int max(int x1, int x2)
{
	return (x1 > x2)? x1 : x2;
}

int logarithm2(int x)
{
	int res = 0;
	while (x != 0)
	{
		res++;
		x = x >> 1;
	}
	return res;
}

void tree_build(int* odd_tree, int* even_tree,int* arr, int idx, int tree_left, int tree_right)
{
	if (tree_left == tree_right)
	{
		if (tree_left % 2 == 0)
		{
			even_tree[idx] = arr[tree_left];
			odd_tree[idx] = 0;
		}
		else
		{
			odd_tree[idx] = arr[tree_left];
			even_tree[idx] = 0;
		}
	}
	else
	{
		int middle = tree_left + (tree_right - tree_left) / 2;
		tree_build(odd_tree, even_tree, arr, 2 * idx, tree_left, middle);
		tree_build(odd_tree, even_tree, arr, 2 * idx + 1, middle + 1, tree_right);
		even_tree[idx] = even_tree[2*idx] + even_tree[2*idx+1];
		odd_tree[idx] = odd_tree[2*idx] + odd_tree[2*idx+1];
	}
}

static inline int d_sum(int* tree, int idx, int tree_left, int tree_right, int left, int right)
{
	if (left > right)
		return 0;
	if (left == tree_left && right == tree_right)
		return tree[idx];
	int middle = tree_left + (tree_right - tree_left) / 2;
	return d_sum(tree, idx * 2, tree_left , middle, left, min(right, middle)) +
		   d_sum(tree, idx * 2 + 1, middle + 1, tree_right, max(left, middle + 1), right);
}

static inline void tree_update(int* tree, int idx, int arr_idx, int new_val, int tree_left, int tree_right)
{
	if (tree_left == tree_right)
		tree[idx] = new_val;
	else
	{
		int middle = tree_left + (tree_right - tree_left) / 2;
		if (arr_idx <= middle)
			tree_update(tree, idx * 2, arr_idx, new_val, tree_left, middle);
		else
			tree_update(tree, idx * 2 + 1, arr_idx, new_val, middle + 1, tree_right);
		tree[idx] = tree[idx*2] + tree[idx*2+1];
	}
}

int main()
{
	int N = 0, M = 0;
	scanf("%d", &N);
	int* arr = calloc(N, sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	scanf("%d", &M);
	int size = 1 << (logarithm2(N) + 2);
	int* even_tree = calloc(size, sizeof(int));
	int* odd_tree = calloc(size, sizeof(int));
	tree_build(odd_tree, even_tree, arr, 1, 0, N - 1); //??
	int op = 0, left = 0, right = 0, idx = 0, new_val = 0;
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &op);
		switch (op)
		{
			case 0:
			{
				scanf("%d %d", &idx, &new_val);
				idx--;
				if (idx % 2 == 0)
					tree_update(even_tree, 1, idx, new_val, 0, N - 1); // ?
				else
					tree_update(odd_tree, 1, idx, new_val, 0, N -1);
				break;
			}
			case 1:
			{
				scanf("%d %d", &left, &right);
				left--;
				right--;
				if (left % 2 == 0)
					printf("%d\n", d_sum(even_tree, 1, 0, N - 1, left, right) - d_sum(odd_tree, 1, 0, N - 1, left, right)); // ?
				else
					printf("%d\n", d_sum(odd_tree, 1, 0, N - 1, left, right) - d_sum(even_tree, 1, 0, N - 1, left, right));
				break;
			}
			default:
				break;
		}
	}
	free(arr);
	free(odd_tree);
	free(even_tree);
	return 0;
}