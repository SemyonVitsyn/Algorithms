#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define str_len 21
#define hash_size 1000003

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
	Hashtable **table_arr = calloc(10, sizeof(Hashtable*));
	for (int i = 0; i < 10; i++)
		table_arr[i] = NULL;
	char op[20] = {0};
	while (scanf("%s", op) != EOF)
	{
		if (strcmp(op, "create") == 0)
		{
			size_t num = 0;
			scanf("%zu", &num);
			table_arr[num] = hashtable_create(hash_size);
		}
		else if (strcmp(op, "insert") == 0)
		{
			size_t num = 0;
			char key[str_len] = {0}, value[str_len] = {0};
			scanf("%zu %21s %21s", &num, key, value);
			if (table_arr[num] != NULL)
			{
				int hash = (int) (hash_func(key) % hash_size);
				struct list *find = list_find(table_arr[num]->arr[hash], key);
				if (find == NULL)
					table_arr[num]->arr[hash] = list_insert(table_arr[num]->arr[hash], key, value);
				else
					strcpy(find->elem.val, value);
			}
		}
		else if (strcmp(op, "erase") == 0)
		{
			size_t num = 0;
			char key[str_len] = {0};
			scanf("%zu %21s", &num, key);
			if (table_arr[num] != NULL)
			{
				int hash = (int)(hash_func(key) % hash_size);
				table_arr[num]->arr[hash] = list_erase(table_arr[num]->arr[hash], key);
			}
		}
		else if (strcmp(op, "find") == 0)
		{
			size_t num = 0;
			char key[str_len] = {0};
			scanf("%zu %21s", &num, key);
			if (table_arr[num] == NULL)
				printf("MISSING\n");
			else
			{
				int hash = (int) (hash_func(key) % hash_size);
				struct list *find = list_find(table_arr[num]->arr[hash], key);
				if (find == NULL)
					printf("MISSING\n");
				else
					printf("%s\n", find->elem.val);
			}
		}
		else if (strcmp(op, "destroy") == 0)
		{
			size_t num = 0;
			scanf("%zu", &num);
			table_arr[num] = hashtable_delete(table_arr[num]);
		}
	}
	for (int i = 0; i < 10; i++)
		table_arr[i] = hashtable_delete(table_arr[i]);
	free(table_arr);
	return 0;
}
