#include <stdio.h>
#include <stdlib.h>

typedef struct hash_table
{
	struct list** arr;
	size_t size;
} Hashtable;

typedef struct list
{
	int val;
	struct list* next;
} List;

List* list_new(int val)
{
	List* head = (List*)calloc(1, sizeof(List));
	head->next = NULL;
	head->val = val;
	return head;
}

List* list_insert(List* head, int val)
{
	if (head == NULL)
	{
		head = list_new(val);
		return head;
	}
	else
	{
		List* current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = list_new(val);
		return head;
	}
}

List* list_find_before(List* head, int val)
{
	if (head == NULL || head->val == val)
		return NULL;
	else
	{
		List* current = head;
		while (current->next != NULL && current->next->val != val)
			current = current->next;
		if (current->next == NULL)
			return NULL;
		else
			return current;
	}
}

List* list_find(List* head, int val)
{
	if (head == NULL || head->val == val)
		return head;
	else
	{
		List* find = list_find_before(head, val);
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
		free(head);
		head = NULL;
		return head;
	}
}

List* list_erase(List* head, int val)
{
	if (head == NULL)
		return NULL;
	if (head->val == val)
	{
		List* delete = head;
		head = head->next;
		free(delete);
		return head;
	}
	else
	{
		List* prev_found = list_find_before(head, val);
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

unsigned hash_func(int key)
{
	key = ((key >> 16) ^ key) * 0x45d9f3b;
	key = ((key >> 16) ^ key) * 0x45d9f3b;
	key = (key >> 16) ^ key;
	return key;
}

Hashtable* hashtable_create(size_t size)
{
	Hashtable* new = calloc(1, sizeof(Hashtable));
	new->arr = calloc(size, sizeof(List*));
	new->size = size;
	return new;
}

Hashtable* hashtable_insert(Hashtable* table, int val, int hash_size)
{
	unsigned hash = hash_func(val) % hash_size;
	table->arr[hash] = list_insert(table->arr[hash], val);
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

int intersection(int** matrix, int hash_idx, int arr_count, int size)
{
	int res = 0, max = 0, hash_size = size * 20;
	Hashtable* table = hashtable_create(hash_size);
	for (int i = 0; i < size; i++)
		table = hashtable_insert(table, matrix[hash_idx][i], hash_size);
	for (int i = hash_idx + 1; i < arr_count; i++)
	{
		res = 0;
		for (int j = 0; j < size; j++)
		{
			unsigned hash = hash_func(matrix[i][j]) % hash_size;
			if (list_find(table->arr[hash], matrix[i][j]) != NULL)
				res++;
		}
		if (res > max)
			max = res;
	}
	table = hashtable_delete(table);
	return max;
}

int main()
{
	int N = 0, M = 0, max = 0, size = 0;
	scanf("%d %d", &N, &M);
	int** matrix = calloc(N, sizeof(int*));
	for (int i = 0; i < N; i++)
		matrix[i] = calloc(M, sizeof(int));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &matrix[i][j]);
	for (int i = 0; i < N; i++)
	{
		size = intersection(matrix, i, N, M);
		if (max < size)
			max = size;
	}
	printf ("%d", max);
	for (int i = 0; i < N; i++)
		free(matrix[i]);
	free(matrix);
	return 0;
}