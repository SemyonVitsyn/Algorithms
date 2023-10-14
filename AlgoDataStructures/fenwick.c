#include <stdio.h>
#include <stdlib.h>

#define size 1001

static inline int f(int i)
{
	return i & (i + 1);
}

static inline int g(int i)
{
	return i | (i + 1);
}

void ADD(long long** S, int v, int x, int y)
{
	for (int i = x; i < size; i = g(i))
		for (int j = y; j < size; j = g(j))
			S[i][j] += v;
}

long long PREFIX_SUM(long long **S, int x, int y)
{
	long long res = 0;
	for (int i = x; i >= 0; i = f(i) - 1)
		for (int j = y; j >= 0; j = f(j) - 1)
			res += S[i][j];
	return res;
}

long long SUM(long long** S, int x1, int y1, int x2, int y2)
{
	return PREFIX_SUM(S, x2, y2) + PREFIX_SUM(S, x1 - 1, y1 - 1) - PREFIX_SUM(S, x2, y1 - 1) - PREFIX_SUM(S, x1 - 1, y2);
}

void CHANGE(long long** S, int v, int x, int y)
{
	int val = v - SUM(S, x, y, x, y);
	for (int i = x; i < size; i = g(i))
		for (int j = y; j < size; j = g(j))
			S[i][j] += val;
}

void REMOVE(long long** S, int x, int y)
{
	int v = SUM(S, x, y, x, y);
	for (int i = x; i < size; i = g(i))
		for (int j = y; j < size; j = g(j))
			S[i][j] -= v;
}

int main()
{
	int v = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	char op[10] = {0};
	long long** S = calloc(size, sizeof(long long*));
	for (int i = 0; i < size; i++)
		S[i] = calloc(size, sizeof(long long));
	while (scanf("%10s", op) != EOF)
	{
		switch(op[0])
		{
			case 'A':
			{
				scanf( "%d %s %d %d", &v, op, &x1, &y1);
				ADD(S, v, x1, y1);
				break;
			}
			case 'R':
			{
				scanf("%d %d", &x1, &y1);
				REMOVE(S, x1, y1);
				break;
			}
			case 'C':
			{
				scanf("%s %d %d %s %d", op, &x1, &y1, op, &v);
				CHANGE(S, v, x1, y1);
				break;
			}
			case 'S':
			{
				scanf("%s %d %d %s %d %d", op, &x1, &y1, op, &x2, &y2);
				printf("%lld\n", SUM(S, x1, y1, x2, y2));
				break;
			}
			default:
				break;
		}
	}
	for (int i = 0; i < size; i++)
		free(S[i]);
	free(S);
	return 0;
}
