#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct coord
{
	__int128_t x;
	__int128_t y;
	__int128_t z;
} Coord;

typedef struct list
{
	Coord elem;
	struct list* next;
} List;

typedef struct hash_table
{
	struct list** arr;
	size_t size;
} Hashtable;

void copy_coord(Coord* destination, Coord source)
{
	destination->x = source.x;
	destination->y = source.y;
	destination->z = source.z;
}

int coord_equ(Coord elem1, Coord elem2)
{
	if (elem1.x == elem2.x)
		if (elem1.y == elem2.y)
			if (elem1.z == elem2.z)
				return 1;
	return 0;
}

List* list_new(Coord elem)
{
	struct list* head = (struct list*)calloc(1, sizeof(struct list));
	head->next = NULL;
	copy_coord(&head->elem, elem);
	return head;
}

List *list_insert(List* head, Coord elem)
{
	if (head == NULL)
	{
		head = list_new(elem);
		return head;
	}
	else
	{
		List* current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = list_new(elem);
		return head;
	}
}

List* list_find_before(List* head, Coord elem)
{
	if (head == NULL || coord_equ(head->elem, elem))
		return NULL;
	else
	{
		struct list* current = head;
		while (current->next != NULL && !coord_equ(current->next->elem, elem))
			current = current->next;
		if (current->next == NULL)
			return NULL;
		else
			return current;
	}
}

struct list* list_find(struct list* head, Coord elem)
{
	if (head == NULL || coord_equ(head->elem, elem))
		return head;
	else
	{
		struct list* find = list_find_before(head, elem);
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

unsigned hash_func(Coord elem)
{
	return elem.x * 73856093 + elem.y * 19349669 + elem.z * 83492791;
}

Hashtable* hashtable_create(size_t size)
{
	Hashtable* new = calloc(1, sizeof(Hashtable));
	new->arr = calloc(size, sizeof(struct list*));
	new->size = size;
	return new;
}

Hashtable* hashtable_insert(Hashtable* table, Coord elem, int hash_size)
{
	unsigned hash = hash_func(elem) % hash_size;
	table->arr[hash] = list_insert(table->arr[hash], elem);
	return table;
}

int hashtable_find(Hashtable* table, Coord elem, int hash_size)
{
	unsigned hash = hash_func(elem) % hash_size;
	List* find = list_find(table->arr[hash], elem);
	if (find == NULL)
		return 0;
	return 1;
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

int check_centre(Coord centre, Hashtable* table, Coord* point, int N, int hash_size)
{
	Coord elem;
	for (int i = 0; i < N; i++)
	{
		copy_coord(&elem, point[i]);
		elem.x += ((centre.x - point[i].x) << 1);
		elem.y += ((centre.y - point[i].y) << 1);
		elem.z += ((centre.z - point[i].z) << 1);
		if (!hashtable_find(table, elem, hash_size))
			return 0;
	}
	return 1;
}

int main()
{
	int N = 0;
	scanf("%d", &N);
	int hash_size = N * 10;
	Coord* point = calloc(N, sizeof(Coord));
	Hashtable* table = hashtable_create(hash_size);
	long long tmp_x = 0, tmp_y = 0, tmp_z = 0;
	__int128_t X = 0, Y = 0, Z = 0;
	for (int i = 0; i < N; i++)
	{
		scanf("%lld %lld %lld", &tmp_x, &tmp_y, &tmp_z);
		point[i].x = tmp_x, point[i].y = tmp_y, point[i].z = tmp_z;
		table = hashtable_insert(table, point[i], hash_size);
		X += tmp_x;
		Y += tmp_y;
		Z += tmp_z;
	}
	if (X % N == 0 && Y % N == 0 && Z % N == 0)
	{
		Coord centre;
		centre.x = X / N, centre.y = Y / N, centre.z = Z / N;
		if (check_centre(centre, table, point, N, hash_size))
			printf("Yes\n");
		else
			printf("No\n");
	}
	else
		printf("No\n");
	free(point);
	table = hashtable_delete(table);
	return 0;
}