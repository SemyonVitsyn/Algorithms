#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Base_type;

typedef struct node
{
	Base_type val;
	size_t idx;
} Node;

struct binary_heap
{
	Node *arr;
	size_t size;
	size_t capacity;
};

struct binom_heap
{
	struct binary_heap **heap_arr;
	size_t curr_idx;
	size_t heap_count;
};

struct binary_heap *heap_new()
{
	struct binary_heap *new = calloc(1, sizeof(struct binary_heap));
	new->size = 0;
	new->capacity = 2;
	new->arr = calloc(new->capacity, sizeof(Node));
	return new;
}

struct binom_heap *binom_heap_new(size_t heap_count)
{
	struct binom_heap *new = calloc(1, sizeof(struct binom_heap));
	new->heap_arr = calloc(heap_count, sizeof(struct binary_heap*));
	for (int i = 0; i < heap_count; i++)
		new->heap_arr[i] = heap_new();
	new->heap_count = heap_count;
	new->curr_idx = 1;
	return new;
}

void heap_swap_elems(struct binary_heap *heap, size_t idx1, size_t idx2)
{
	assert(heap);
	Node temp = heap->arr[idx1];
	heap->arr[idx1] = heap->arr[idx2];
	heap->arr[idx2] = temp;
}

void heap_siftUp(struct binary_heap *heap, size_t idx)
{
	assert(heap);
	size_t parent_idx = (idx-1) / 2;
	while (idx > 0 && ((heap->arr[idx].val < heap->arr[parent_idx].val)
	                    || (heap->arr[idx].val == heap->arr[parent_idx].val
	                        && heap->arr[idx].idx < heap->arr[parent_idx].idx)))
	{
		heap_swap_elems(heap, idx, parent_idx);
		idx = parent_idx;
		parent_idx = (idx-1) / 2;
	}
}

void heap_siftDown(struct binary_heap *heap, size_t idx)
{
	while (2 *)
}

void heap_insert(struct binary_heap *heap, Node elem)
{
	heap->arr[heap->size] = elem;
	heap_siftUp(heap, heap->size);
	heap->size++;
	if (heap->size == heap->capacity)
	{
		heap->capacity *= 2;
		heap->arr = realloc(heap->arr, heap->capacity * sizeof(Node));
	}
}

void binom_heap_insert(struct binom_heap *binomial_heap, size_t heap_idx, Base_type elem)
{
	assert(heap_idx < binomial_heap->heap_count);
	Node new;
	new.val = elem;
	new.idx = binomial_heap->curr_idx++;
	heap_insert(binomial_heap->heap_arr[heap_idx], new);
}

Node heap_top(struct binary_heap *heap)
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
		if (left_child < heap->size && ((heap->arr[left_child].val < heap->arr[priority].val)
										|| (heap->arr[left_child].val == heap->arr[priority].val
											&& heap->arr[left_child].idx < heap->arr[priority].idx)))
			priority = left_child;
		if (right_child < heap->size && ((heap->arr[right_child].val < heap->arr[priority].val)
		                                || (heap->arr[right_child].val == heap->arr[priority].val
		                                    && heap->arr[right_child].idx < heap->arr[priority].idx)))
			priority = right_child;
		if (idx == priority)
			break;
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

int find_elem(struct binom_heap * binomial_heap, size_t search_idx, size_t *heap_idx, size_t *idx)
{
	for (*heap_idx = 0; *heap_idx < binomial_heap->heap_count; (*heap_idx)++)
		for (*idx = 0; *idx < binomial_heap->heap_arr[*heap_idx]->size; (*idx)++)
			if (binomial_heap->heap_arr[*heap_idx]->arr[*idx].idx == search_idx)
				return 1;
	return 0;
}

void erase_elem(struct binom_heap *binomial_heap, size_t search_idx)
{
	assert(binomial_heap->curr_idx > search_idx);
	size_t heap_idx = 0, idx = 0;
	if (find_elem(binomial_heap, search_idx, &heap_idx, &idx))
	{
		Node elem = heap_top(binomial_heap->heap_arr[heap_idx]);
		binomial_heap->heap_arr[heap_idx]->arr[idx].val = elem.val - 1;
		heap_siftUp(binomial_heap->heap_arr[heap_idx], idx);
		heap_erase_top(binomial_heap->heap_arr[heap_idx]);
	}
}

void change_elem(struct binom_heap *binomial_heap, size_t search_idx, Base_type val)
{
	assert(binomial_heap->curr_idx > search_idx);
	size_t heap_idx = 0, idx = 0;
	if (find_elem(binomial_heap, search_idx, &heap_idx, &idx))
	{
		struct binary_heap* b = binomial_heap->heap_arr[heap_idx];
		binomial_heap->heap_arr[heap_idx]->arr[idx].val = val;
		heap_siftUp(binomial_heap->heap_arr[heap_idx], idx);
		heapify(binomial_heap->heap_arr[heap_idx], idx);
	}
}

void heap_merge(struct binary_heap *destination, struct binary_heap *source)
{
	assert(destination);
	assert(source);
	for (int i = 0; i < source->size; i++)
		heap_insert(destination, source->arr[i]);
	source->size = 0;
}

struct heap *heap_delete(struct binary_heap *heap)
{
	assert(heap);
	free(heap->arr);
	free(heap);
	return NULL;
}

struct binom_heap *delete_binom_heap(struct binom_heap *binomial_heap)
{
	for (int i = 0; i < binomial_heap->heap_count; i++)
		heap_delete(binomial_heap->heap_arr[i]);
	free(binomial_heap->heap_arr);
	free(binomial_heap);
	return NULL;
}

int main()
{
	int N = 0, M = 0;
	scanf("%d %d", &N, &M);
	struct binom_heap *binomial_heap = binom_heap_new(N);
	size_t operation = 0;
	for (int i = 0; i < M; i++)
	{
		scanf("%zu", &operation);
		switch (operation)
		{
			case 0:
			{
				size_t heap_idx = 0;
				Base_type elem = 0;
				scanf("%zu %d", &heap_idx, &elem);
				binom_heap_insert(binomial_heap, heap_idx - 1, elem);
				break;
			}
			case 1:
			{
				size_t heap_idx1 = 0;
				size_t heap_idx2 = 0;
				scanf("%zu %zu", &heap_idx1, &heap_idx2);
				heap_merge(binomial_heap->heap_arr[heap_idx2-1], binomial_heap->heap_arr[heap_idx1-1]);
				break;
			}
			case 2:
			{
				size_t idx = 0;
				scanf("%zu", &idx);
				erase_elem(binomial_heap, idx);
				break;
			}
			case 3:
			{
				size_t idx = 0;
				Base_type val = 0;
				scanf("%zu %d", &idx, &val);
				change_elem(binomial_heap, idx, val);
				break;
			}
			case 4:
			{
				size_t heap_idx = 0;
				scanf("%zu", &heap_idx);
				printf("%d\n", heap_top(binomial_heap->heap_arr[heap_idx-1]).val);
				break;
			}
			case 5:
			{
				size_t heap_idx = 0;
				scanf("%zu", &heap_idx);
				heap_erase_top(binomial_heap->heap_arr[heap_idx-1]);
				break;
			}
			default:
				break;
		}
	}
	delete_binom_heap(binomial_heap);
	return 0;
}
