#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	long long sum;
	long long pref;
	long long suff;
	long long max_sum;
} Node;

long long max(long long x1, long long x2)
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

Node combine(Node left, Node right)
{
	Node new;
	new.sum = left.sum + right.sum;
	new.pref = max(left.pref, left.sum + right.pref);
	new.suff = max(right.sum + left.suff, right.suff);
	new.max_sum = max(max(left.max_sum, right.max_sum), left.suff + right.pref);
	return new;
}

Node new_node(int val)
{
	Node new;
	new.sum = val;
	new.pref = val;
	new.suff = val;
	new.max_sum = val;
	return new;
}

void tree_build(Node* tree, int* arr, int idx, int tree_left, int tree_right)
{
	if (tree_left == tree_right)
		tree[idx] = new_node(arr[tree_left]);
	else
	{
		int middle = tree_left + (tree_right - tree_left) / 2;
		tree_build(tree, arr, 2 * idx, tree_left, middle);
		tree_build(tree, arr, 2 * idx + 1, middle + 1, tree_right);
		tree[idx] = combine(tree[2*idx], tree[2*idx+1]);
	}
}

static inline Node max_sum(Node* tree, int idx, int tree_left, int tree_right, int left, int right)
{
	if (left == tree_left && right == tree_right)
		return tree[idx];
	int middle = tree_left + (tree_right - tree_left) / 2;
	if (right <= middle)
		return max_sum(tree, idx * 2, tree_left, middle, left, right);
	if (left > middle)
		return max_sum(tree, idx * 2 + 1, middle + 1, tree_right, left, right);
	return combine(max_sum(tree, idx * 2, tree_left, middle, left, middle),
	               max_sum(tree, idx * 2 + 1, middle + 1, tree_right, middle + 1, right));
}

static inline void tree_update(Node* tree, int idx, int arr_idx, int new_val, int tree_left, int tree_right)
{
	if (tree_left == tree_right )
		tree[idx] = new_node(new_val);
	else
	{
		int middle = tree_left + (tree_right - tree_left) / 2;
		if (arr_idx <= middle)
			tree_update(tree, idx * 2, arr_idx, new_val, tree_left, middle);
		else
			tree_update(tree, idx * 2 + 1, arr_idx, new_val, middle + 1, tree_right);
		tree[idx] = combine(tree[idx*2], tree[idx*2+1]);
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
	tree_build(tree, arr, 1, 0, N);
	int op = 0, left = 0, right = 0, idx = 0, new_val = 0;
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &op);
		switch (op)
		{
			case 1:
			{
				scanf("%d %d", &idx, &new_val);
				tree_update(tree, 1, idx, new_val, 0, N);
				break;
			}
			case 2:
			{
				scanf("%d %d", &left, &right);
				printf("%lld\n", max_sum(tree, 1, 0, N, left, right).max_sum);
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