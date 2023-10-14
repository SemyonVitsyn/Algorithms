//struct vector *vector_new(size_t elems, size_t elem_size);
//Создать новый вектор, который будет содержать elems элементов размера elem_size. Элементы не инициализированы.
//int vector_push(struct vector *v, void const *elem);
//Добавить ещё один элемент elem к вектору v. Функция должна вернуть 0 при успехе и 1 при неуспехе любого рода. Амортизированная сложность этой операции должна быть O(1). После успешного исполнения данной операции размер вектора должен увеличиться на единицу.
//int vector_pop (struct vector *v, void *elem);
//Убрать из вектора v последний элемент, если он существует, и положить его значение по адресу elem. Функция должна вернуть 0 при успехе и 1 при неуспехе любого рода. Амортизированная сложность этой операции должна быть O(1).
//int vector_empty(struct vector const *st);
//Функция-предикат. Она должна вернуть логическую истину (1), если вектор пуст и логический ноль (0) в противном случае.
//struct vector *vector_delete(struct vector *v);
//Удалить объект st и вернуть NULL.
//void vector_print(struct vector const *v, void (*pf)(void const *data));
//Вывести на стандартный вывод содержимое вектора v. Второй аргумент — указатель на функцию, которая должна принимать указатель на одиночный элемент данных, хранимый в векторе и вывести его в соответствующем виде на стандартный вывод.
//int vector_set(struct vector *v, size_t index, void const *elem);
//Присвоить элементу index вектора v значение elem. Вернуть 0, если операция успешна или 1 в противном случае.
//int vector_get(struct vector const *v, size_t index, void *elem);
//Присвоить elem значение элемента index вектора v. Вернуть 0, если операция успешна или 1 в противном случае.
//int vector_resize(struct vector *v, size_t new_size);
//Изменить размер вектора v на new_size. Значение старых элементов вектора не должны измениться. Остальные элементы остаются неинициализированными. Вернуть 0, если операция успешна или 1 в противном случае.
//size_t vector_size(struct vector const *v);
//Возвратить количество элементов, которым владеет вектор v.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct vector
{
	void *data;
	size_t elem_size;
	size_t size;
	size_t capacity;
};

struct vector *vector_new(size_t elems, size_t elem_size)
{
	assert(elem_size);
	struct vector *new = (struct vector*)malloc(sizeof(struct vector));
	new->data = malloc(elems * elem_size);
	new->elem_size = elem_size;
	new->capacity = elems;
	new->size = elems;
	return new;
}

int vector_push(struct vector *v, void const *elem)
{
	assert(v);
	assert(elem);
	if (v->size == v->capacity)
	{
		v->capacity = v->capacity * 2 + 1;
		void *new = realloc(v->data, v->capacity * v->elem_size);
		if (!new)
			return 1;
		else
			v->data = new;
	}
	memcpy(v->data + v->size * v->elem_size, elem, v->elem_size);
	(v->size)++;
	return 0;
}

int vector_pop(struct vector *v, void *elem)
{
	assert(v);
	assert(elem);
	if (v->size)
	{
		(v->size)--;
		memcpy(elem, v->data + v->size * v->elem_size, v->elem_size);
		return 0;
	}
	else
		return 1;
}

int vector_empty(struct vector const *v)
{
	assert(v);
	return (v->size == 0);
}

struct vector *vector_delete(struct vector *v)
{
	assert(v);
	free(v->data);
	free(v);
	return NULL;
}

void vector_print(struct vector const *v, void (*pf)(void const *data))
{
	assert(v);
	assert(pf);
	printf("[");
	if (v->size != 0)
	{
		pf(v->data);
		for (size_t i = 1; i < v->size; i++)
		{
			printf(", ");
			pf(v->data + i * v->elem_size);
		}
	}
	printf("]\n");
}

int vector_resize(struct vector *v, size_t new_size)
{
	assert(v);
	v->size = new_size;
	if (v->size > v->capacity)
	{
		v->capacity = new_size;
		void *new = realloc(v->data, v->capacity * v->elem_size);
		if (new)
			v->data = new;
		else
			return 1;
	}
	return 0;
}

int vector_set(struct vector *v, size_t index, void const *elem)
{
	assert(v);
	assert(elem);
	if (index < v->size)
	{
		memcpy(v->data + index * v->elem_size, elem, v->elem_size);
		return 0;
	}
	else
		return 1;
}

int vector_get(struct vector const *head, size_t index, void *elem)
{
	assert(head);
	assert(elem);
	if (index < head->size)
	{
		memcpy(elem, head->data + index * head->elem_size, head->elem_size);
		return 0;
	}
	else
		return 1;
}

size_t vector_size(struct vector const *v)
{
	assert(v);
	return v->size;
}
