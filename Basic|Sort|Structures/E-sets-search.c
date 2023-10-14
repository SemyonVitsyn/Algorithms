#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list
{
	int *set;
	struct list* next;
} List;

typedef struct hash_table
{
	List** arr;
	size_t size;
} Hashtable;

int compare(const void* elem1, const void* elem2)
{
	return *(int*)elem1 - *(int*)elem2;
}

List* list_new(int* set, size_t size)
{
	List* head = (List*)calloc(1, sizeof(List));
	head->next = NULL;
	head->set = calloc(size, sizeof(int));
	memcpy(head->set, set, size * sizeof(int));
	return head;
}

List *list_insert(List* head, int* set, size_t size)
{
	if (head == NULL)
	{
		head = list_new(set, size);
		return head;
	}
	else
	{
		List* current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = list_new(set, size);
		return head;
	}
}

List* list_find_before(List* head, int* set, size_t size)
{
	if (head == NULL || memcmp(head->set, set, size * sizeof(int)) == 0)
		return NULL;
	else
	{
		List* current = head;
		while (current->next != NULL && memcmp(current->next->set, set, size * sizeof(int)) != 0)
			current = current->next;
		if (current->next == NULL)
			return NULL;
		else
			return current;
	}
}

List* list_find(List* head, int* set, size_t size)
{
	if (head == NULL || memcmp(head->set, set, size * sizeof(int)) == 0)
		return head;
	else
	{
		List* find = list_find_before(head, set, size);
		if (find == NULL)
			return NULL;
		else
			return find->next;
	}
}

List* list_delete(List* head)
{
	if (head == NULL)
		return NULL;
	else
	{
		list_delete(head->next);
		free(head->set);
		free(head);
		head = NULL;
		return head;
	}
}

List* list_erase(List* head, int* set, size_t size)
{
	if (head == NULL)
		return NULL;
	if (memcmp(head->set, set, size * sizeof(int)) == 0)
	{
		List* delete = head;
		head = head->next;
		free(delete);
		return head;
	}
	else
	{
		List* prev_found = list_find_before(head, set, size);
		if (prev_found == NULL)
			return head;
		else
		{
			List* delete = prev_found->next;
			prev_found->next = prev_found->next->next;
			free(delete);
			delete = NULL;
			return head;
		}
	}
}

unsigned hash_func(int* set, size_t size)
{
	unsigned hash = 0;
	for (int i = 0; i < size; i++)
		hash = hash * 31 + set[i];
	return hash;
}

Hashtable* hashtable_create(size_t size)
{
	Hashtable* new = calloc(1, sizeof(Hashtable));
	new->arr = calloc(size, sizeof(List*));
	new->size = size;
	return new;
}

Hashtable* hashtable_insert(Hashtable* table, int* set, size_t size, size_t hash_size)
{
	unsigned hash = hash_func(set, size) % hash_size;
	table->arr[hash] = list_insert(table->arr[hash], set, size);
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

int main()
{
	int N = 0, M = 0, K = 0;
	scanf("%d %d %d", &N, &M, &K);
	int *buf = calloc(M, sizeof(int));
	Hashtable *table = hashtable_create(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			scanf("%d", &buf[j]);
		qsort(buf, M, sizeof(int), compare);
		hashtable_insert(table, buf, M, N);
	}
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < M; j++)
			scanf("%d", &buf[j]);
		qsort(buf, M, sizeof(int), compare);
		unsigned hash = hash_func(buf, M) % N;
		List* find = list_find(table->arr[hash], buf, M);
		if (find == NULL)
			printf("0\n");
		else
			printf("1\n");
	}
	table = hashtable_delete(table);
	free(buf);
	return 0;
}