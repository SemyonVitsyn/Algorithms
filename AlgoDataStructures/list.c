//struct list *list_new(int elem);
//Создать новый узел со значением elem и вернуть указатель на него.
//struct list *list_insert(struct list *head, int elem);
//Вставить в конец списка с головой head узел со значением elem. Если голова списка пуста — создать новый список. Вернуть голову нового списка.
//struct list *list_find(struct list *head, int elem);
//Найти узел, начиная с головы списка, в котором значение будет равно elem и вернуть указатель на него. Если таких значений в списке нет, вернуть NULL.
//struct list *list_erase(struct list *head, int elem);
//Найти узел, начиная с головы списка, в котором значение будет равно elem и удалить его из списка. Вернуть указатель на голову вновь получившегося списка.
//struct list *list_insert_after(struct list *head, struct list *where, struct list *what);
//Вставить узел what после узла where в списке, готова которого находится в head. Вернуть указатель на голову нового списка. Вставка в пустой список приводит к созданию непустого. Вставка NULL или после NULL есть пустая операция.
//struct list *list_insert_before(struct list *head, struct list *where, struct list *what);
//Вставить узел what перед узлом where в списке, готова которого находится в head. Вернуть указатель на голову нового списка. Вставка в пустой список приводит к созданию непустого. Вставка NULL или после NULL есть пустая операция.
//struct list *list_delete(struct list *head);
//Удалить весь список, начинающийся с head. Вернуть NULL.
//struct list *list_next(struct list *curr);
//Вернуть указатель на следующий элемент списка. Если curr пустой — вернуть NULL.
//void list_print(struct list const *head);
//Вывести на стандартный вывод содержимое списка в формате по образцу: []\n или [1, 2, 3]\n.

#include <stdio.h>
#include <stdlib.h>

struct list
{
	int val;
	struct list *next;
};

struct list *list_new(int elem)
{
	struct list *head = (struct list*)calloc(1, sizeof(struct list));
	head->next = NULL;
	head->val = elem;
	return head;
}

struct list *list_insert(struct list *head, int elem)
{
	if (head == NULL)
	{
		head = list_new(elem);
		return head;
	}
	else
	{
		struct list *current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = (struct list*)calloc(1, sizeof(struct list));
		current->next->val = elem;
		current->next->next = NULL;
		return head;
	}
}

struct list *list_find_before(struct list *head, int elem)
{
	if (head == NULL || head->val == elem)
		return NULL;
	else
	{
		struct list* current = head;
		while (current->next != NULL && current->next->val != elem)
			current = current->next;
		if (current->next == NULL)
			return NULL;
		else
			return current;
	}
}

struct list *list_find(struct list *head, int elem)
{
	if (head == NULL || head->val == elem)
		return head;
	else
	{
		struct list *find = list_find_before(head, elem);
		if (find == NULL)
			return NULL;
		else
			return find->next;
	}
}

struct list *list_delete(struct list *head)
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

struct list *list_erase(struct list *head, int elem)
{
	if (head == NULL)
		return NULL;
	if (head->val == elem)
	{
		struct list *delete = head;
		head = head->next;
		free(delete);
		return head;
	}
	else
	{
		struct list *prev_found = list_find_before(head, elem);
		if (prev_found == NULL)
			return head;
		else
		{
			struct list *delete = prev_found->next;
			prev_found->next = prev_found->next->next;
			free(delete);
			delete = NULL;
			return head;
		}
	}
}

struct list *list_insert_after(struct list *head, struct list *where, struct list *what)
{
	if (head == NULL)
		return what;
	if (where == NULL || what == NULL)
		return head;
	struct list *current = head;
	while (current != NULL && current != where)
		current = current->next;
	if (current == NULL)
		return head;
	else
	{
		what->next = current->next;
		current->next = what;
		return head;
	}
}

struct list *list_insert_before(struct list *head, struct list *where, struct list *what)
{
	if (head == NULL)
		return what;
	if (where == NULL || what == NULL)
		return head;
	if (head == where)
	{
		what->next = head;
		return what;
	}
	else
	{
		struct list *current = head;
		while (current->next != NULL && current->next != where)
			current = current->next;
		if (current->next == NULL)
			return head;
		else
		{
			what->next = current->next;
			current->next = what;
			return head;
		}
	}
}

struct list *list_next(struct list *curr)
{
	if (curr == NULL)
		return NULL;
	else
		return curr->next;
}

void list_print(struct list const *head)
{
	struct list const *current = head;
	printf("[");
	while (current != NULL)
	{
		printf("%d", current->val);
		if (current->next != NULL)
			printf(", ");
		current = current->next;
	}
	printf("]\n");
}
