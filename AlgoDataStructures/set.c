//struct set *set_new(size_t capacity);
//Создать новое пустое множество, значения элементов которого могут лежать в границах от 0 до capacity-1 включительно. Вернуть указатель на него.
//int set_insert(struct set *s, size_t elem);
//Добавить во множество s элемент elem. Если элемент существовал, множество не изменится. Вернуть 0, если операция корректна, т.е. elem < capacity, иначе вернуть 1.
//int set_erase(struct set *s, size_t elem);
//Удалить элемент из множества. Если элемент не существовал, множество не изменится. Вернуть 0, если операция корректна, т.е. elem < capacity, иначе вернуть 1.
//int set_find(struct set const *s, size_t elem);
//Вернуть 1, если элемент присутствует в множестве и 0 в противном случае.
//struct set *set_delete(struct set *s);
//Удалить объект множество и вернуть NULL
//int set_empty(struct set const *s);
//Предикат: вернуть единицу, если в множестве есть хотя бы один элемент и ноль в противном случае.
//ssize_t set_findfirst(struct set const *s, size_t start);
//Вернуть наименьший из элементов множества, не меньших start. Если таких элементов нет (например, множество пустое), то вернуть -1.
//size_t set_size(struct set const *s);
//Вернуть количество элементов множества.
//void set_print(struct set const *s);
//Вывести на стандартный вывод содержимое множества в формате по образцу: []\n или [1, 2, 3]\n.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define base_type unsigned
#define base_type_size sizeof(base_type)
#define base_type_bit_size (base_type_size * 8)
#define get_elem_idx(elem) \
	size_t chunk_number = elem / base_type_bit_size, idx = elem % base_type_bit_size;

struct set
{
	base_type *chunk_arr;
	size_t chunks_count;
	size_t capacity;
};

struct set *set_new(size_t capacity)
{
	struct set *new_set = calloc(1, sizeof(struct set));
	new_set->capacity = capacity;
	new_set->chunks_count = (capacity + base_type_bit_size - 1) / base_type_bit_size;
	new_set->chunk_arr = calloc(new_set->chunks_count, base_type_size);
	return new_set;
}

int set_insert(struct set *s, size_t elem)
{
	assert(s);
	if (elem < s->capacity)
	{
		get_elem_idx(elem)
		s->chunk_arr[chunk_number] |= 1 << (base_type_bit_size - idx - 1);
		return 0;
	}
	else
		return 1;
}

int set_erase(struct set *s, size_t elem)
{
	assert(s);
	if (elem < s->capacity)
	{
		get_elem_idx(elem)
		s->chunk_arr[chunk_number] &= ~(1 << (base_type_bit_size - idx - 1));
		return 0;
	}
	else
		return 1;
}

int set_find(struct set const *s, size_t elem)
{
	assert(s);
	if (elem < s->capacity)
	{
		get_elem_idx(elem)
		if (s->chunk_arr[chunk_number] & (1 << (base_type_bit_size - idx - 1)))
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

struct set *set_delete(struct set *s)
{
	assert(s);
	free(s->chunk_arr);
	free(s);
	return NULL;
}

size_t set_size(struct set const *s)
{
	assert(s);
	size_t count = 0;
	for (int curr_chunk = 0; curr_chunk < s->chunks_count; curr_chunk++)
		count += __builtin_popcount(s->chunk_arr[curr_chunk]);
	return count;
}

int set_empty(struct set const *s)
{
	assert(s);
	return set_size(s) != 0;
}

ssize_t set_findfirst(struct set const *s, size_t start)
{
	assert(s);
	if (start < s->capacity)
	{
		get_elem_idx(start)
		for (size_t bit = idx; bit < base_type_bit_size; bit++)
			if (s->chunk_arr[chunk_number] & (1 << (base_type_bit_size - bit - 1)))
				return (ssize_t) (chunk_number * base_type_bit_size + bit);
		for (size_t curr_chunk = chunk_number + 1; curr_chunk < s->chunks_count; curr_chunk++)
			for (size_t bit = 0; bit < base_type_bit_size; bit++)
				if (s->chunk_arr[curr_chunk] & (1 << (base_type_bit_size - bit - 1)))
					return (ssize_t) (curr_chunk * base_type_bit_size + bit);
	}
	return -1;
}

void set_print(struct set const *s)
{
	assert(s);
	printf("[");
	size_t size = set_size(s), count_printed = 0;
	if (size != 0)
	{
		for (size_t curr_chunk = 0; curr_chunk < s->chunks_count; curr_chunk++)
			for(size_t bit = 0; bit < base_type_bit_size; bit++)
				if (s->chunk_arr[curr_chunk] & (1 << (base_type_bit_size - bit - 1)))
				{
					printf("%llu", curr_chunk * base_type_bit_size + bit);
					if (++count_printed < size)
						printf(", ");
				}
	}
	printf("]\n");
}

int main() {
	struct set *s = set_new(150);
	set_print(s);
	assert(set_find(s, 10) == 0);
	assert(set_erase(s, 10) == 0);
	assert(set_insert(s, 1) == 0);
	assert(set_insert(s, 2) == 0);
	assert(set_insert(s, 100) == 0);
	assert(set_size(s) == 3);
	set_print(s);
	assert(set_find(s,1) != 0);
	assert(set_find(s,100) != 0);
	assert(set_find(s, 2) != 0);
	assert(set_find(s, 499) == 0);
	assert(set_erase(s, 2) == 0);
	assert(set_find(s, 2) == 0);
	assert(set_findfirst(s, 2) == 100);
	assert(set_findfirst(s, 3) == 100);
	assert(set_findfirst(s, 100) == 100);
	set_print(s);
	assert(set_erase(s, 1) == 0);
	set_print(s);
	assert(set_delete(s) == NULL);
}
