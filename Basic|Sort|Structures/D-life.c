#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int div_round_up(int x, int y)
{
	return (x - 1) / y + 1;
}

static inline void table_change(unsigned char** table, int x, int y)
{
	int byte_idx = x >> 3, bit_idx = x % 8;
	table[y][byte_idx] ^= 1 << (7 - bit_idx);
}

unsigned char** table_build(int size1, int size2, int L)
{
	unsigned char** table = calloc(size1, sizeof(unsigned char*));
	for (int i = 0; i < size1; i++)
		table[i] = calloc(size2, sizeof(unsigned char));
	int x = 0, y = 0;
	for (int i = 0; i < L; i++)
	{
		scanf("%d %d", &x, &y);
		table_change(table, x, y);
	}
	return table;
}

static inline int status(unsigned char** table,int x, int y, int size1, int size2)
{
	if (x < 0 || y < 0 || x >= size2 || y >= size1)
		return 0;
	else
	{
		int byte_idx = x >> 3, bit_idx = x % 8;
		//int answ = (table[y][byte_idx] & (1 << (7 - bit_idx))) != 0;
		return (table[y][byte_idx] & (1 << (7 - bit_idx))) != 0;
	}
}

static inline int neighbors(unsigned char** table, int x, int y, int size1, int size2)
{
	return status(table, x-1, y+1, size1, size2) +
		   status(table, x, y+1, size1, size2) +
		   status(table, x+1, y+1, size1, size2) +
		   status(table, x-1, y, size1, size2) +
		   status(table, x+1, y, size1, size2) +
		   status(table, x-1, y-1, size1, size2) +
		   status(table, x, y-1, size1, size2) +
		   status(table, x+1, y-1, size1, size2);
}

static inline void table_check_change(unsigned char** table, unsigned char** temp, int x, int y, int size1, int size2)
{
	int byte_idx = x >> 3, bit_idx = x % 8;
	int neighbors_number = neighbors(table, x, y, size1, size2);
	if (table[y][byte_idx] & (1 << (7 - bit_idx)))
	{
		if (neighbors_number < 2 || neighbors_number > 3)
			temp[y][byte_idx] ^= 1 << (7 - bit_idx);
	}
	else
	{
		if (neighbors_number == 3)
			temp[y][byte_idx] ^= 1 << (7 - bit_idx);
	}
}

static inline void table_step(unsigned char** table, unsigned char** temp, int size1, int size2)
{
	for (int i = 0; i < size1; i++)
		for (int j = 0; j < size2; j++)
			table_check_change(table, temp, j, i, size1, size2);
	for (int  i = 0; i < size1; i++)
		memcpy(table[i], temp[i], div_round_up(size2, 8));
}

void print(unsigned char** table, int size1, int size2)
{
	for (int x = 0; x < size2; x++)
		for (int y = 0; y < size1; y++)
		{
			int byte_idx = x >> 3, bit_idx = x % 8;
			if (table[y][byte_idx] & (1 << (7 - bit_idx)))
				printf("%d %d\n", x, y);
		}
}

int main()
{
	int N = 0, M = 0, L = 0, K = 0;
	scanf("%d %d %d %d", &N, &M, &L, &K);
	int size = div_round_up(M, 8);
	unsigned char** table = table_build(N, size, L);

	unsigned char** temp = calloc(N, sizeof(unsigned char*));
	for (int i = 0; i < N; i++)
		temp[i] = calloc(size, sizeof(unsigned char));

	for (int  i = 0; i < N; i++)
		memcpy(temp[i], table[i], size);

	for (int i = 0; i < K; i++)
		table_step(table, temp, N, M);

	print(table, N, M);
	//for (int i = 0; i < N; i++)
	//	for (int j = 0; j < size; j++)
	//		printf("%d\n", table[i][j]);

	for (int i = 0; i < N; i++)
		free(table[i]);
	free(table);
	for (int i = 0; i < N; i++)
		free(temp[i]);
	free(temp);
	return 0;
}
