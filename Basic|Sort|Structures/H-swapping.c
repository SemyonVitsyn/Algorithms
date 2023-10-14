#include <stdio.h>
#include <stdlib.h>

#define hash_size 1000000

typedef struct node
{
	int key;
	int val;
} Node;

typedef struct hash_table
{
	struct list** arr;
	size_t size;
} Hashtable;

typedef struct list
{
	Node elem;
	struct list* next;
} List;

int abs_dif(int x, int y)
{
	return (x > y)? x - y : y - x;
}

List* list_new(int key, int val)
{
	List* head = (List*)calloc(1, sizeof(List));
	head->next = NULL;
	head->elem.key = key;
	head->elem.val = val;
	return head;
}

List *list_insert(List* head, int key, int val)
{
	if (head == NULL)
	{
		head = list_new(key, val);
		return head;
	}
	else
	{
		List* current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = list_new(key, val);
		return head;
	}
}

List* list_find_before(List* head, int key)
{
	if (head == NULL || head->elem.key == key)
		return NULL;
	else
	{
		List* current = head;
		while (current->next != NULL && current->next->elem.key != key)
			current = current->next;
		if (current->next == NULL)
			return NULL;
		else
			return current;
	}
}

List* list_find(List* head, int key)
{
	if (head == NULL || head->elem.key == key)
		return head;
	else
	{
		List* find = list_find_before(head, key);
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

List* list_erase(List* head, int key)
{
	if (head == NULL)
		return NULL;
	if (head->elem.key == key)
	{
		List* delete = head;
		head = head->next;
		free(delete);
		return head;
	}
	else
	{
		List* prev_found = list_find_before(head, key);
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

Hashtable* hashtable_insert(Hashtable* table, int key, int val)
{
	unsigned hash = hash_func(key) % hash_size;
	List *find = list_find(table->arr[hash], key);
	if (find == NULL)
		table->arr[hash] = list_insert(table->arr[hash], key, val);
	else
		find->elem.val = val;
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

int swap(Hashtable* table, int val1, int val2)
{
	int res = 0;
	unsigned hash1 = hash_func(val1) % hash_size, hash2 = hash_func(val2) % hash_size;
	List* item1 = list_find(table->arr[hash1], val1);
	List* item2 = list_find(table->arr[hash2], val2);
	if (item1 == NULL)
	{
		if (item2 == NULL)
		{
			res = abs_dif(val1, val2);
			table->arr[hash1] = list_insert(table->arr[hash1], val1, val2);
			table->arr[hash2] = list_insert(table->arr[hash2], val2, val1);
		}
		else
		{
			res = abs_dif(val1, item2->elem.val);
			table->arr[hash1] = list_insert(table->arr[hash1], val1, item2->elem.val);
			item2->elem.val = val1;
		}
	}
	else
	{
		if (item2 == NULL)
		{
			res = abs_dif(item1->elem.val, val2);
			table->arr[hash2] = list_insert(table->arr[hash2], val2, item1->elem.val);
			item1->elem.val = val2;
		}
		else
		{
			res = abs_dif(item1->elem.val, item2->elem.val);
			int temp = item1->elem.val;
			item1->elem.val = item2->elem.val;
			item2->elem.val = temp;
		}
	}
	return res;
}

int main()
{
	Hashtable *table = hashtable_create(hash_size + 1);
	int N = 0, val1 = 0, val2 = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &val1, &val2);
		printf("%d\n", swap(table, val1, val2));
	}
	table = hashtable_delete(table);
	return 0;
}