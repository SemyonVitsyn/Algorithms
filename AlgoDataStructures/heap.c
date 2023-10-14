//Реализуйте структуру данных бинарная куча.
//
//Куча может содержать целые числа типа int.
//
//Каждая строка стандартного ввода содержит команду и операнды. Вы должны исполнить команду и, возможно, вывести результат.
//
//0 # size type — создать кучу под номером #, максимальным количеством элементов size и с дисциплиной type: type=0 — на вершине кучи лежит наименьший элемент; type=1 — на вершине кучи лежит наибольший элемент. Нумерация куч ведётся с нуля.
//1 # elem — добавить в кучу # элемент со значением elem.
//2 # — распечатать на отдельной строке элемент с вершины кучи #.
//3 # — удалить вершину кучи #.
//4 # — вывести количество элементов в куче.
//5 #1 #2 — добавить все элементы кучи #2 в кучу #1. Куча #2 становится пустой.
//6 # — удалить кучу #.
//7 # — вывод массива кучи.
//Input format
//Первая строка содержит число N — количество создаваемых куч. 1 ⩽ N ⩽ 5.
//
//Следующие строки содержат команды работы с кучами. Конец ввода определяется концом файла.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Base_type;

struct binary_heap
{
	Base_type *arr;
	size_t size;
	size_t capacity;
	size_t type;
};

struct binary_heap *heap_new(size_t capacity, size_t type)
{
	struct binary_heap *new = calloc(1, sizeof(struct binary_heap));
	new->arr = calloc(capacity, sizeof(Base_type));
	new->capacity = capacity;
	new->type = type;
	return new;
}

void heap_swap_elems(struct binary_heap *heap, size_t idx1, size_t idx2)
{
	assert(heap);
	Base_type temp = heap->arr[idx1];
	heap->arr[idx1] = heap->arr[idx2];
	heap->arr[idx2] = temp;
}

void heap_siftUp(struct binary_heap *heap, size_t idx)
{
	assert(heap);
	size_t parent_idx = (idx-1) / 2;
	if (heap->type == 0)
		while (idx > 0 && heap->arr[idx] < heap->arr[parent_idx])
		{
			heap_swap_elems(heap, idx, parent_idx);
			idx = parent_idx;
			parent_idx = (idx-1) / 2;
		}
	else
		while (idx > 0 && heap->arr[idx] > heap->arr[parent_idx])
		{
			heap_swap_elems(heap, idx, parent_idx);
			idx = parent_idx;
			parent_idx = (idx-1) / 2;
		}
}

void heap_insert(struct binary_heap *heap, Base_type elem)
{
	assert(heap);
	assert(heap->size < heap->capacity);
	heap->arr[heap->size] = elem;
	heap_siftUp(heap, heap->size);
	heap->size++;
}

Base_type heap_top(struct binary_heap *heap)
{
	assert(heap);
	assert(heap->size > 0);
	return heap->arr[0];
}

void heapify(struct binary_heap *heap, size_t idx)
{
	assert(heap);
	size_t left_child = 0, right_child = 0, priority = 0;
	for (; ; )
	{
		priority = idx;
		left_child = 2 * idx + 1;
		right_child = 2 * idx + 2;
		if (heap->type == 0)
		{
			if (left_child < heap->size && heap->arr[left_child] < heap->arr[priority])
				priority = left_child;
			if (right_child < heap->size && heap->arr[right_child] < heap->arr[priority])
				priority = right_child;
			if (idx == priority)
				break;
		}
		else
		{
			if (left_child < heap->size && heap->arr[left_child] > heap->arr[priority])
				priority = left_child;
			if (right_child < heap->size && heap->arr[right_child] > heap->arr[priority])
				priority = right_child;
			if (idx == priority)
				break;
		}
		heap_swap_elems(heap, idx, priority);
		idx = priority;
	}
}

void heap_erase_top(struct binary_heap *heap)
{
	assert(heap);
	assert(heap->size > 0);
	heap->size--;
	if (heap->size > 0)
	{
		heap_swap_elems(heap, 0, heap->size);
		heapify(heap, 0);
	}
}

size_t heap_size(struct binary_heap *heap)
{
	assert(heap);
	return heap->size;
}

void heap_merge(struct binary_heap *destination, struct binary_heap *source)
{
	assert(destination);
	assert(source);
	for (int i = 0; i < source->size; i++)
		heap_insert(destination, source->arr[i]);
	source->size = 0;
}

struct binary_heap *heap_delete(struct binary_heap *heap)
{
	assert(heap);
	free(heap->arr);
	free(heap);
	return NULL;
}

void heap_print(struct binary_heap *heap)
{
	for (int i = 0; i < heap->size; i++)
		printf("%d ", heap->arr[i]);
	printf("\n");
}

int main()
{
	int heap_count = 0;
	scanf("%d", &heap_count);
	struct binary_heap **heap_arr = calloc(heap_count, sizeof(struct binary_heap*));
	char ch = 0;
	while ((ch = getchar()) != -1)
	{
		switch(ch-48)
		{
			case 0:
			{
				size_t heap_idx = 0, capacity = 0, type = 0;
				scanf("%zu %zu %zu", &heap_idx, &capacity, &type);
				heap_arr[heap_idx] = heap_new(capacity, type);
				break;
			}
			case 1:
			{
				size_t heap_idx = 0;
				Base_type elem = 0;
				scanf("%zu %d", &heap_idx, &elem);
				heap_insert(heap_arr[heap_idx], elem);
				break;
			}
			case 2:
			{
				size_t heap_idx = 0;
				scanf("%zu", &heap_idx);
				printf("%d\n", heap_top(heap_arr[heap_idx]));
				break;
			}
			case 3:
			{
				size_t heap_idx = 0;
				scanf("%zu", &heap_idx);
				heap_erase_top(heap_arr[heap_idx]);
				break;
			}
			case 4:
			{
				size_t heap_idx = 0;
				scanf("%zu", &heap_idx);
				printf("%zu\n", heap_size(heap_arr[heap_idx]));
				break;
			}
			case 5:
			{
				size_t destination = 0, source = 0;
				scanf("%zu %zu", &destination, &source);
				heap_merge(heap_arr[destination], heap_arr[source]);
				break;
			}
			case 6:
			{
				size_t heap_idx = 0;
				scanf("%zu", &heap_idx);
				heap_delete(heap_arr[heap_idx]);
				break;
			}
			case 7:
			{
				size_t head_idx = 0;
				scanf("%zu", &head_idx);
				heap_print(heap_arr[head_idx]);
				break;
			}
			default:
			{
				break;
			}
		}
	}
	free(heap_arr);
	return 0;
}
