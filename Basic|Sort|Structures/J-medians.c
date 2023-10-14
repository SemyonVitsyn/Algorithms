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



void find_median(int N)
{
	assert(N);
	struct binary_heap *big_elems_heap = heap_new(N / 2 + 2, 0);
	struct binary_heap *small_elems_heap = heap_new(N / 2 + 2, 1);
	int operation = 0, elem = 0;
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &operation);
		if (operation == 0)
		{
			scanf("%d", &elem);
			if (heap_size(small_elems_heap) != 0)
			{
				if (elem <= heap_top(small_elems_heap))
					heap_insert(small_elems_heap, elem);
				else
					heap_insert(big_elems_heap, elem);
			}
			else
				heap_insert(small_elems_heap, elem);
			if (heap_size(small_elems_heap) > heap_size(big_elems_heap) + 1)
			{
				elem = heap_top(small_elems_heap);
				heap_erase_top(small_elems_heap);
				heap_insert(big_elems_heap, elem);
			}
			else if (heap_size(big_elems_heap) > heap_size(small_elems_heap) + 1)
			{
				elem = heap_top(big_elems_heap);
				heap_erase_top(big_elems_heap);
				heap_insert(small_elems_heap, elem);
			}
		}
		else if (operation == 1)
		{
			if (heap_size(small_elems_heap) != 0 && heap_size(big_elems_heap) != 0)
			{
				if (heap_size(big_elems_heap) > heap_size(small_elems_heap))
					printf("%d\n", heap_top(big_elems_heap));
				else
					printf("%d\n", heap_top(small_elems_heap));
			}
			else
			{
				printf("ARRAY IS EMPTY\n");
				i--;
			}
		}
		else
		{
			printf("WRONG OPERATION\n");
			i--;
		}
	}
	small_elems_heap = heap_delete(small_elems_heap);
	big_elems_heap = heap_delete(big_elems_heap);
}

int main()
{
	int N = 0;
	scanf("%d", &N);
	find_median(N);
	return 0;
}
