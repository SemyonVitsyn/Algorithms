//Правильной скобочной последовательность назовём такую последовательность символов, которая сохраняет баланс открывающих и закрывающих скобок.
//
//В нашей задаче парами скобок являются: { }, [ ], ( ), < >.
//
//Нужно проверить много строк на предмет того, является ли данная строка правильной скобочной последовательностью. Например, строка #include <stdio.h> правильной скобочной последовательностью является, а строка x = y[10] + (a < b) не является.
//
//Input format
//У нас задача проще. В единственной строке входного файла, длиной до 102400 символов, присутствуют только упомянутые выше символы.
//
//Output format
//Вы должны вывести ровно одну строку --- это будет YES, если вход является правильной скобочной последовательностью или NO в противном случае.

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
	new = calloc(1, sizeof(struct stack));
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
	st->size++;
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
		st->size--;
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

int check_braces()
{
	struct stack *st = stack_new(sizeof(char));
	char curr = 0;
	while ((curr = getchar()) != '\n')
	{
		if (curr == '{' || curr == '[' || curr == '(' || curr == '<')
			stack_push(st, &curr);
		else if (!stack_empty(st) && (curr == '}' || curr == ']' || curr == ')' || curr == '>'))
		{
			char last = 0;
			stack_top(st, &last);
			if ((curr == '}' && last == '{') ||
			    (curr == ']' && last == '[') ||
				(curr == ')' && last == '(') ||
				(curr == '>' && last == '<'))
				stack_pop(st, &curr);
			else
			{
				stack_delete(st);
				return 0;
			}
		}
		else if (curr != '\n')
		{
			stack_delete(st);
			return 0;
		}
	}
	if (stack_empty(st))
	{
		stack_delete(st);
		return 1;
	}
	else
	{
		stack_delete(st);
		return 0;
	}
}

int main()
{
	if (check_braces())
		printf("YES");
	else
		printf("NO");
	return 0;
}