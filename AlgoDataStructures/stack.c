//struct stack *stack_new(size_t elem_size);
//Создать новый стек, который будет хранить элементы размера elem_size и вернуть указатель на него.
//int stack_push(struct stack *st, const void *elem);
//Добавить в стек st элемент elem. Обратите внимание, что из elem должно быть извлечено для хранения ровно то количество байт, которой было специфицировано при создании данного стека. Функция должна вернуть 0 при успехе и 1 при неуспехе любого рода. Амортизированная сложность этой операции должна быть O(1). После успешного исполнения данной операции стек должен содержать на один элемент больше.
//int stack_pop (struct stack *st, void *elem);
//Извлечь из стека st элемент elem и продвинуть стек вниз. Обратите внимание, что в elem должно быть положено ровно то количество байт, которой было специфицировано при создании данного стека. Функция должна вернуть 0 при успехе и 1 при неуспехе любого рода. Амортизированная сложность этой операции должна быть O(1).
//int stack_top (struct stack *st, void *elem);
//Извлечь из стека st элемент elem и оставить стек в предыдущем состоянии. Обратите внимание, что в elem должно быть положено ровно то количество байт, которой было специфицировано при создании данного стека. Функция должна вернуть 0 при успехе и 1 при неуспехе любого рода. Амортизированная сложность этой операции должна быть O(1).
//int stack_empty(struct stack const *st);
//Функция-предикат. Она должна вернуть логическую истину (1), если стек пуст и логический ноль (0) в противном случае.
//struct stack *stack_delete(struct stack *st);
//Удалить объект st и вернуть NULL.
//void stack_print(struct stack const *st, void (*pf)(void const *st));
//Так как стек может содержать произвольные данные, но выводить информацию из него необходимо, вторым аргументом функции является указатель на пользовательскую функцию, которая должна принимать указатель на элемент данных, располагающийся в стеке, и вывести его в соответствующем виде на стандартный вывод.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
	struct stack *new = NULL;
	new = (struct stack*)calloc(1, sizeof(struct stack));
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
	if (st->size)
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

void stack_print(struct stack const *st, void (*pf)(void const *st))
{
	assert(st);
	assert(pf);
	if (st->size == 0)
	{
		printf("[]\n");
		return;
	}
	printf("[");
	pf(st->data);
	for (size_t i = 1; i < st->size; i++)
	{
		printf(", ");
		pf(st->data + i * st->elem_size);
	}
	printf("]\n");
}
