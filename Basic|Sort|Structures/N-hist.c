//Над прямой X расположено несколько столбиков из звёздочек. Все столбики находятся рядом, количество звёздочек в них неотрицательно и все звёздочки, если они есть, начинаются сразу над прямой.
//
//Всё это описывается следующим образом. В первой строке — число столбиков 1 ⩽ N ⩽ 1000. Остальные N чисел располагаются в следующей строке и обозначают высоты столбиков. Высоты столбиков не превосходят 1000.
//
//Например, входные данные из первого примера выглядят так:
//
//
//........
//....*..*
//*.*.****
//***.****
//--------
//
//Второй пример выглядит так:
//....*
//...**
//..***
//.****
//*****
//-----
//
//Из звёздочек можно составлять прямоугольники и площадью такого прямоугольника будет количество звёздочек в нём.
//
//Output format
//Одно число - максимальная площадь из всех прямоугольников, состоящих только из звёздочек.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct stack
{
	void *data;
	size_t elem_size;
	size_t size;
	size_t capacity;
};

struct stack *stack_new(size_t elem_size)
{
	assert(elem_size);
	struct stack *new = malloc(sizeof(struct stack));
	new->data = calloc(1, elem_size);
	new->elem_size = elem_size;
	new->size = 0;
	new->capacity = 1;
	return new;
}

int stack_push(struct stack *st, const void *elem)
{
	assert(st);
	assert(elem);
	if (st->size == st->capacity)
	{
		st->capacity *= 2;
		void *new = realloc(st->data, st->capacity * st->elem_size);
		if (new)
			st->data = new;
		else
			return 1;
	}
	memcpy(st->data + st->size * st->elem_size, elem, st->elem_size);
	(st->size)++;
	return 0;
}

int stack_top(struct stack *st, void *elem)
{
	assert(st);
	assert(elem);
	if (st->size != 0)
	{
		memcpy(elem, st->data + (st->size-1) * st->elem_size, st->elem_size);
		return 0;
	}
	else
		return 1;
}

int stack_pop(struct stack *st, void *elem)
{
	assert(st);
	assert(elem);
	int res = stack_top(st, elem);
	if (st->size)
		(st->size)--;
	return res;
}

int stack_empty(struct stack const *st)
{
	assert(st);
	return st->size == 0;
}

struct stack *stack_delete(struct stack *st)
{
	assert(st);
	free(st->data);
	free(st);
	return NULL;
}

int max_area(int const *height, int N)
{
	assert(height);
	int max_area = 0, curr_area = 0, curr_idx = 0, prev_idx = 0, idx = 0;
	struct stack *st = stack_new(sizeof(int));
	while (idx < N)
	{
		if (stack_top(st, &curr_idx) || height[curr_idx] <= height[idx]) // Пуст или высота не меньше
		{
			stack_push(st, &idx);
			idx++;
		}
		else
		{
			stack_pop(st, &curr_idx);
			stack_top(st, &prev_idx);
			curr_area = height[curr_idx] * (stack_empty(st) ? idx : idx - prev_idx - 1);
			if (curr_area > max_area)
				max_area = curr_area;
		}
	}
	while (!stack_empty(st))
	{
		stack_pop(st, &curr_idx);
		stack_top(st, &prev_idx);
		curr_area = height[curr_idx] * (stack_empty(st) ? idx : idx - prev_idx - 1);
		if (curr_area > max_area)
			max_area = curr_area;
	}
	stack_delete(st);
	return max_area;
}

int main()
{
	int N = 0;
	scanf("%d", &N);
	int *height = calloc(N, sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &height[i]);
	printf("%d", max_area(height, N));
	free(height);
	return 0;
}