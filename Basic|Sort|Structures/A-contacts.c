#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define str_len 31
#define hash_size 100003

typedef struct node
{
	char key[str_len];
	char val[str_len];
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

struct list* list_new(char key[str_len],char val[str_len])
{
	struct list* head = (struct list*)calloc(1, sizeof(struct list));
	head->next = NULL;
	strcpy(head->elem.key, key);
	strcpy(head->elem.val, val);
	return head;
}

struct list *list_insert(struct list* head, char key[str_len], char val[str_len])
{
	if (head == NULL)
	{
		head = list_new(key, val);
		return head;
	}
	else
	{
		struct list* current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = list_new(key, val);
		return head;
	}
}

struct list* list_find_before(struct list* head, char key[str_len])
{
	if (head == NULL || strcmp(head->elem.key, key) == 0)
		return NULL;
	else
	{
		struct list* current = head;
		while (current->next != NULL && strcmp(current->next->elem.key, key) != 0)
			current = current->next;
		if (current->next == NULL)
			return NULL;
		else
			return current;
	}
}

struct list* list_find(struct list* head, char key[str_len])
{
	if (head == NULL || strcmp(head->elem.key, key) == 0)
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
		free(head);
		head = NULL;
		return head;
	}
}

struct list* list_erase(struct list* head, char key[str_len])
{
	if (head == NULL)
		return NULL;
	if (strcmp(head->elem.key, key) == 0)
	{
		struct list* delete = head;
		head = head->next;
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
			free(delete);
			delete = NULL;
			return head;
		}
	}
}

unsigned long long hash_func(char key[str_len])
{
	unsigned long long hash = 0;
	unsigned long long p = 31, p_pow = 1;
	size_t len = strlen(key);
	for (int i = 0; i < len; i++)
	{
		hash += (key[i] - 'a' + 1) * p_pow;
		p_pow *= p;
	}
	return hash;
}

Hashtable* hashtable_create(size_t size)
{
	Hashtable* new = calloc(1, sizeof(Hashtable));
	new->arr = calloc(size, sizeof(struct list*));
	new->size = size;
	return new;
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
	int N = 0;
	scanf("%d", &N);
	Hashtable* table = hashtable_create(hash_size);
	char op[20] = {0};
	char key[str_len] = {0}, value[str_len] = {0};
	for (int i = 0; i < N; i++)
	{
		scanf("%s", op);
		if (strcmp(op, "ADD") == 0)
		{
			scanf("%30s %30s", key, value);
			int hash = (int) (hash_func(key) % hash_size);
			struct list* find = list_find(table->arr[hash], key);
			if (find == NULL)
				table->arr[hash] = list_insert(table->arr[hash], key, value);
			else
				printf("ERROR\n");
		}
		else if (strcmp(op, "DELETE") == 0)
		{
			scanf("%30s", key);
			int hash = (int)(hash_func(key) % hash_size);
			struct list* find = list_find(table->arr[hash], key);
			if (find == NULL)
				printf("ERROR\n");
			else
				table->arr[hash] = list_erase(table->arr[hash], key);
		}
		else if (strcmp(op, "EDITPHONE") == 0)
		{
			scanf("%30s %30s", key, value);
			int hash = (int)(hash_func(key) % hash_size);
			struct list* find = list_find(table->arr[hash], key);
			if (find == NULL)
				printf("ERROR\n");
			else
				strcpy(find->elem.val, value);
		}
		else if (strcmp(op, "PRINT") == 0)
		{
			scanf("%30s", key);
			int hash = (int)(hash_func(key) % hash_size);
			struct list* find = list_find(table->arr[hash], key);
			if (find == NULL)
				printf("ERROR\n");
			else
				printf("%s %s\n", find->elem.key, find->elem.val);
		}
	}
	table = hashtable_delete(table);
	return 0;
}