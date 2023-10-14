#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node
{
	int xor_val;
	int max_val;
} Node;

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

void tree_build(Node* tree,int* arr, int idx, int tree_left, int tree_right)
{
	if (tree_left == tree_right)
	{
		tree[idx].max_val = arr[tree_left];
		tree[idx].xor_val = arr[tree_left];
	}
	else
	{
		int middle = tree_left + (tree_right - tree_left) / 2;
		tree_build(tree, arr, 2 * idx, tree_left, middle);
		tree_build(tree, arr, 2 * idx + 1, middle + 1, tree_right);
		tree[idx].xor_val = tree[2*idx].xor_val ^ tree[2*idx+1].xor_val;
		tree[idx].max_val = max(tree[2*idx].max_val, tree[2*idx+1].max_val);
	}
}

static inline int tree_xor(Node* tree, int idx, int tree_left, int tree_right, int left, int right)
{
	if (left > right)
		return 0;
	if (left == tree_left && right == tree_right)
		return tree[idx].xor_val;
	int middle = tree_left + (tree_right - tree_left) / 2;
	return tree_xor(tree, idx * 2, tree_left, middle, left, min(right, middle)) ^
		   tree_xor(tree, idx * 2 + 1, middle + 1, tree_right, max(left, middle + 1), right);
}

static inline int tree_max(Node* tree, int idx, int tree_left, int tree_right, int left, int right)
{
	if (left > right)
		return INT_MIN;
	if (left == tree_left && right == tree_right)
		return tree[idx].max_val;
	int middle = tree_left + (tree_right - tree_left) / 2;
	return max(tree_max(tree, idx * 2, tree_left , middle, left, min(right, middle)),
			   tree_max(tree, idx * 2 + 1, middle + 1, tree_right, max(left, middle + 1), right));
}

static inline void tree_update(Node* tree, int idx, int arr_idx, int new_val, int tree_left, int tree_right)
{
	if (tree_left == tree_right )
	{
		tree[idx].xor_val = new_val;
		tree[idx].max_val = new_val;
	}
	else
	{
		int middle = tree_left + (tree_right - tree_left) / 2;
		if (arr_idx <= middle)
			tree_update(tree, idx * 2, arr_idx, new_val, tree_left, middle);
		else
			tree_update(tree, idx * 2 + 1, arr_idx, new_val, middle + 1, tree_right);
		tree[idx].xor_val = tree[idx*2].xor_val ^ tree[idx*2+1].xor_val;
		tree[idx].max_val = max(tree[idx*2].max_val, tree[idx*2+1].max_val);
	}
}

int main()
{
	int N = 0, M = 0;
	scanf("%d %d", &N, &M);
	int* arr = calloc(N, sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	int size = 1 << (logarithm2(N) + 1);
	Node* tree = calloc(size, sizeof(Node));
	tree_build(tree, arr, 1, 0, N - 1); //??
	int op = 0, left = 0, right = 0, idx = 0, new_val = 0;
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &op);
		switch (op)
		{
			case 1:
			{
				scanf("%d %d", &left, &right);
				printf("%d\n", tree_xor(tree, 1, 0, N - 1, left, right)); // ?
				break;
			}
			case 2:
			{
				scanf("%d %d", &left, &right);
				printf("%d\n", tree_max(tree, 1, 0, N - 1, left, right)); // ?
				break;
			}
			case 3:
			{
				scanf("%d %d", &idx, &new_val);
				tree_update(tree, 1, idx, new_val, 0, N - 1); // ?
				break;
			}
			default:
				break;
		}
	}
	free(arr);
	free(tree);
	return 0;
}
