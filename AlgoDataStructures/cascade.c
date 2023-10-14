#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned Type;

typedef struct node
{
	Type val;
	struct node* left;
	struct node* right;
	struct node* down;
	char is_alien;
} Node;

typedef struct block
{
	Node* arr;
	size_t size;
} Block;

int binary_search(Node* arr, int size, Type x)
{
	int l = 0;
	int h = size;
	while (l < h)
	{
		int mid =  l + (h - l) / 2;
		if (x <= arr[mid].val)
			h = mid;
		else
			l = mid + 1;
	}
	return l;
}

Block* cascades_table(Block* blocks, int N)
{
	Block* table = calloc(N, sizeof(Block));
	table[N-1].size = blocks[N-1].size;
	table[N-1].arr = calloc(table[N-1].size, sizeof(Node));
	memcpy(table[N-1].arr, blocks[N-1].arr, blocks[N-1].size * sizeof(Node));
	for (int i = N - 2; i >= 0; i--)
	{
		table[i].size = blocks[i].size + (table[i+1].size / 2);
		table[i].arr = calloc(table[i].size, sizeof(Node));
		int idx = 0, idx_in_next = 1, idx_in_curr = 0;
		Node* last_non_alien = NULL;
		Node* last_alien = NULL;
		while(1)
		{
			if (idx_in_next >= table[i+1].size && idx_in_curr >= blocks[i].size)
				break;
			if (idx_in_next >= table[i+1].size || (idx_in_curr < blocks[i].size && table[i+1].arr[idx_in_next].val > blocks[i].arr[idx_in_curr].val))
			{
				table[i].arr[idx].val = blocks[i].arr[idx_in_curr].val;
				table[i].arr[idx].left = last_alien;
				last_non_alien = &table[i].arr[idx];
				idx_in_curr++;
			}
			else
			{
				table[i].arr[idx].val = table[i+1].arr[idx_in_next].val;
				table[i].arr[idx].down = &table[i+1].arr[idx_in_next];
				table[i].arr[idx].is_alien = 1;
				table[i].arr[idx].left = last_non_alien;
				last_alien = &table[i].arr[idx];
				idx_in_next += 2;
			}
			idx++;
		}

		if (!table[i].arr[idx-1].is_alien)
		{
			last_non_alien = &table[i].arr[idx-1];
			last_alien = NULL;
		}
		else
		{
			last_non_alien = NULL;
			last_non_alien = &table[i].arr[idx-1];
		}

		for (int j = table[i].size - 2; j >= 0; j--)
		{
			if (table[i].arr[j].is_alien)
			{
				table[i].arr[j].right = last_non_alien;
				last_alien = &table[i].arr[j];
			}
			else
			{
				table[i].arr[j].right = last_alien;
				last_non_alien = &table[i].arr[j];
			}
		}
	}
	for (int i = 0; i < N; i++)
		free(blocks[i].arr);
	free(blocks);
	return table;
}

void find(Block* table, int size, Type x)
{
	int idx = binary_search(table[0].arr, table[0].size, x);
	Node* cell = NULL;

	if (idx >= table[0].size)
	{
		printf("%d\n", -1);
		cell = &table[0].arr[table[0].size - 1];
		if (cell->is_alien)
		{
			if (cell->left != NULL && cell->left->val >= x)
				cell = cell->left;
			else
				cell = cell->right;
		}
	}
	else
	{
		cell = &table[0].arr[idx];
		if (cell->is_alien)
		{
			if (cell->left != NULL && cell->left->val >= x)
				cell = cell->left;
			else
				cell = cell->right;
		}
		printf("%u ", cell->val);
	}

	for (int i = 1; i < size; i++)
	{
		cell = cell->left->down;
		if ((cell->val < x || cell->is_alien) && cell->right != NULL)
			cell = cell->right;
		if ((cell->val < x || cell->is_alien) && cell->right != NULL)
			cell = cell->right;
		if (cell->is_alien)
			cell = cell->left;
		if (cell->val >= x)
			printf("%u ", cell->val);
		else
			printf("-1 ");
	}
	printf("\n");
}

int main()
{
	int N = 0, K = 0;
	scanf("%d %d", &N, &K);
	Block* blocks = calloc(N, sizeof(Block));
	for (int i = 0; i < N; i++)
	{
		scanf("%zu", &blocks[i].size);
		blocks[i].arr = calloc(blocks[i].size, sizeof(Node));
		for (int j = 0; j < blocks[i].size; j++)
			scanf("%u", &blocks[i].arr[j].val);
	}
	Block* table = cascades_table(blocks, N);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < table[i].size; j++)
			printf("%d ", table[i].arr[j].val);
		printf("\n");
	}
	printf("\n");

	Type val = 0;
	for (int i = 0; i < K; i++)
	{
		scanf("%u", &val);
		find(table, N, val);
	}

	for (int i = 0; i < N; i++)
		free(table[i].arr);
	free(table);
	return 0;
}
