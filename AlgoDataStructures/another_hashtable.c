#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	unsigned long long key;
	int* idx;
	int size;
	int capacity;
} Node;

typedef struct hash_table
{
	struct list** arr;
	size_t size;
} Hashtable;

struct list
{
	Node elem;
	struct list* next;
};

struct list* list_new(unsigned long long key, int idx)
{
	struct list* head = (struct list*)calloc(1, sizeof(struct list));
	head->next = NULL;
	head->elem.size = 1;
	head->elem.capacity = 2;
	head->elem.idx = calloc(2, sizeof(int));
	head->elem.key = key;
	head->elem.idx[0] = idx;
	return head;
}

struct list *list_insert(struct list* head, unsigned long long key, int idx)
{
	if (head == NULL)
	{
		head = list_new(key, idx);
		return head;
	}
	else
	{
		struct list* current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = list_new(key, idx);
		return head;
	}
}

struct list* list_find_before(struct list* head, unsigned long long key)
{
	if (head == NULL || head->elem.key == key)
		return NULL;
	else
	{
		struct list* current = head;
		while (current->next != NULL && current->next->elem.key != key)
			current = current->next;
		if (current->next == NULL)
			return NULL;
		else
			return current;
	}
}

struct list* list_find(struct list* head, unsigned long long key)
{
	if (head == NULL || head->elem.key == key)
		return head;
	else
	{
		struct list* find = list_find_before(head, key);
		if (find == NULL)
			return NULL;
		else
			return find->next;
	}
}

struct list* list_delete(struct list* head)
{
	if (head == NULL)
		return NULL;
	else
	{
		list_delete(head->next);
		free(head->elem.idx);
		free(head);
		head = NULL;
		return head;
	}
}

struct list* list_erase(struct list* head, unsigned long long key)
{
	if (head == NULL)
		return NULL;
	if (head->elem.key == key)
	{
		struct list* delete = head;
		head = head->next;
		free(delete->elem.idx);
		free(delete);
		return head;
	}
	else
	{
		struct list* prev_found = list_find_before(head, key);
		if (prev_found == NULL)
			return head;
		else
		{
			struct list* delete = prev_found->next;
			prev_found->next = prev_found->next->next;
			free(delete->elem.idx);
			free(delete);
			delete = NULL;
			return head;
		}
	}
}

unsigned hash_func(unsigned long long key)
{
	key = ((key >> 16) ^ key) * 0x45d9f3b;
	key = ((key >> 16) ^ key) * 0x45d9f3b;
	key = (key >> 16) ^ key;
	return key;
}

Hashtable* hashtable_create(int hash_size)
{
	Hashtable* new = calloc(1, sizeof(Hashtable));
	new->arr = calloc(hash_size, sizeof(struct list*));
	new->size = hash_size;
	return new;
}

Hashtable* hashtable_insert(Hashtable* table, unsigned long long key, int idx)
{
	unsigned hash = hash_func(key) % table->size;
	struct list* find = list_find(table->arr[hash], key);
	if (find != NULL)
	{
		find->elem.idx[find->elem.size] = idx;
		find->elem.size++;
		if (find->elem.size == find->elem.capacity)
		{
			find->elem.capacity *= 2;
			find->elem.idx = realloc(find->elem.idx,find->elem.capacity * sizeof(int));
		}
	}
	else
		table->arr[hash] = list_insert(table->arr[hash], key, idx);
	return table;
}

struct list* hashtable_find(Hashtable* table, unsigned long long key)
{
	unsigned hash = hash_func(key) % table->size;
	struct list* find = list_find(table->arr[hash], key);
	return find;
}

Hashtable* hashtable_erase(Hashtable* table, unsigned long long key)
{
	unsigned hash = hash_func(key) % table->size;
	table->arr[hash] = list_erase(table->arr[hash], key);
	return table;
}

Hashtable* hashtable_delete(Hashtable* removed)
{
	if (removed == NULL)
		return NULL;
	for (int i = 0; i < removed->size; i++)
		list_delete(removed->arr[i]);
	free(removed->arr);
	free(removed);
	return NULL;
}

int next_idx(Hashtable* table, unsigned long long key, int curr_idx)
{
	struct list* find = hashtable_find(table, key);
	if (find != NULL)
		for (int i = 0; i < find->elem.size; i++)
			if (find->elem.idx[i] >= curr_idx)
				return find->elem.idx[i];
	return -1;
}

int lowest_priority(unsigned long long* cache, Hashtable* table, int curr_idx, int N)
{
	int idx = 0, next = 0, max_dif = 0;
	for (int i = 0; i < N; i++)
	{
		next = next_idx(table, cache[i], curr_idx);
		if (next == -1)
			return i;
		if (max_dif < next - curr_idx)
		{
			max_dif = next - curr_idx;
			idx = i;
		}
	}
	return idx;
}

int count(unsigned long long* arr, Hashtable* table, int N, int M)
{
	int count = 0, size = 0, idx = 0;
	unsigned long long* cache = calloc(N, sizeof(unsigned long long));
	int temp_hash_size = N * 10;
	Hashtable* temp = hashtable_create(temp_hash_size);
	struct list* find = NULL;
	for (int i = 0; i < M; i++)
	{
		find = hashtable_find(temp, arr[i]);
		if (find == NULL)
		{
			if (size < N)
			{
				temp = hashtable_insert(temp, arr[i], i);
				cache[size] = arr[i];
				count++;
				size++;
			}
			else
			{
				idx = lowest_priority(cache, table, i, N);
				temp = hashtable_erase(temp, cache[idx]);
				temp = hashtable_insert(temp, arr[i], i);
				cache[idx] = arr[i];
				count++;
			}
		}
	}
	temp = hashtable_delete(temp);
	free(cache);
	return count;
}

int main()
{
	int N = 0, M = 0;
	scanf("%d %d", &N, &M);
	int hash_size = M * 10;
	Hashtable* table = hashtable_create(hash_size);
	unsigned long long* arr = calloc(M, sizeof(unsigned long long));
	for (int i = 0; i < M; i++)
	{
		scanf("%lld", &arr[i]);
		hashtable_insert(table, arr[i], i);
	}
	printf("%d", count(arr, table, N, M));
	free(arr);
	table = hashtable_delete(table);
	return 0;
}
