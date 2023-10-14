//Митрофан, путешествуя по Африке, зашёл в комисионный магазин и, к своей радости, обнаружил там редкую флейту, которую продавали ну очень недорого. Подойдя к кассе, он установил, что забыл дома как пластиковую банковскую карту, так и кошелёк с купюрами. К счастью для него, у него в кармане нашлась монетница, в которой хранились монеты различных номиналов, причём ровно по две монеты каждого номинала. Задача состоит в том, чтобы купить флейту, истратив наименьшее возможное количество монет.
//
//Input format
//В первой строке — два числа, стоимость флейты 1⩽V⩽109 и количество пар монет 1⩽N⩽15.
//
//Во второй строке — N чисел — номиналы монет 1⩽Ci⩽109 возрастающем порядке.
//
//Output format
//Если имеющимися монетами можно расплатиться за покупку без сдачи, то нужно вывести минимально возможное количество монет, требующихся для этого.
//
//Если денег хватает, но без сдачи обойтись нельзя, то вывести одно слово Change.
//
//Иначе вывести одно слово Impossible.

#include <stdio.h>
#include <stdlib.h>

struct subsum
{
	int sum;
	int elem_count;
};


static struct subsum *form_subsums(int const *arr, int N)
{
	int power = 1 << N;
	struct subsum *subsums = calloc(power, sizeof(struct subsum));
	for (int i = 0; i < power; i++)
	{
		int bits = i, idx = 0;
		while (bits > 0)
		{
			if (bits & 1)
			{
				subsums[i].sum += arr[idx];
				subsums[i].elem_count += 1;
			}
			idx += 1;
			bits = bits >> 1;
		}
	}
	return subsums;
}

int compare(const void *x1, const void *x2)
{
	struct subsum *elem1 = (struct subsum*)x1;
	struct subsum *elem2 = (struct subsum*)x2;
	if (elem1->sum == elem2->sum)
		return elem2->elem_count - elem1->elem_count;
	else
		return elem1->sum - elem2->sum;
}

void solve(int *price_arr, int V, int N)
{
	struct subsum *subsums = form_subsums(price_arr, N);
	int power = 1 << N;
	qsort(subsums, power, sizeof(struct subsum), compare);
	if (subsums[power-1].sum * 2 < V)
		printf("Impossible");
	else
	{
		struct subsum min_change;
		min_change.sum = subsums[power-1].sum * 2 - V;
		min_change.elem_count = subsums[power-1].elem_count * 2;
		for (int i = power-1; i >= 0; i--)
		{
			if (subsums[i].sum * 2 < V)
				break;
			else
				for (int j = i; j >= 0; j--)
				{
					if (subsums[i].sum + subsums[j].sum - V == 0)
					{
						if (min_change.sum != 0)
						{
							min_change.elem_count = subsums[i].elem_count + subsums[j].elem_count;
							min_change.sum = 0;
						}
						else if (subsums[i].elem_count + subsums[j].elem_count < min_change.elem_count)
							min_change.elem_count = subsums[i].elem_count + subsums[j].elem_count;
						break;
					}
					if (subsums[i].sum + subsums[j].sum < V)
						break;
				}
		}
		if (min_change.sum == 0)
			printf("%d", min_change.elem_count);
		else
			printf("Change");
	}
	free(subsums);
}

int main()
{
	int V = 0, N = 0;
	scanf("%d %d", &V, &N);
	int *price_arr = calloc(N, sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &price_arr[i]);
	solve(price_arr, V, N);
	free(price_arr);
}