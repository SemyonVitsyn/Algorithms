#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	struct node* one;
	struct node* zero;
} Node;

Node* new_node()
{
	Node* new = calloc(1, sizeof(Node));
	return new;
}

void insert(Node* head, unsigned val)
{
	Node *temp = head;
	unsigned bit = 0;
	for (int i = 31; i >= 0; i--)
	{
		bit = (val >> i) & 1;
		if (bit == 0)
		{
			if (temp->zero == NULL)
				temp->zero = new_node();
			temp = temp->zero;
		}
		else
		{
			if (temp->one == NULL)
				temp->one = new_node();
			temp = temp->one;
		}
	}
}

void erase(Node* head, unsigned val, int i, char* out_flag)
{
	if (head == NULL && i != -1)
		return;
	if (i == -1)
	{
		*out_flag = 1;
		return;
	}
	unsigned bit = (val >> i) & 1;
	if (bit == 0)
		erase(head->zero, val, i - 1, out_flag);
	else
		erase(head->one, val, i - 1, out_flag);
	if (*out_flag == 1)
	{
		if (bit == 0)
		{
			free(head->zero);
			head->zero = NULL;
			if (head->one != NULL)
				*out_flag = 0;
		}
		else
		{
			free(head->one);
			head->one = NULL;
			if (head->zero != NULL)
				*out_flag = 0;
		}
	}
}

unsigned max_xor(Node* head, unsigned val)
{
	Node* temp = head;
	unsigned elem = 0;
	unsigned bit = 0;
	for (int i = 31; i >= 0; i--)
	{
		bit = (val >> i) & 1;
		if (bit == 0)
		{
			if (temp->one != NULL)
			{
				elem += (1 << i);
				temp = temp->one;
			}
			else
				temp = temp->zero;
		}
		else
		{
			if (temp->zero != NULL)
				temp = temp->zero;
			else
			{
				elem += (1 << i);
				temp = temp->one;
			}
		}
	}
	return elem;
}

void delete(Node* head)
{
	if (head == NULL)
		return;
	delete(head->one);
	delete(head->zero);
	free(head);
}

int main()
{
	Node* trie = calloc(1, sizeof(Node));
	int N = 0, op = 0;
	unsigned val = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &op);
		switch (op)
		{
			case 1:
			{
				scanf("%u", &val);
				insert(trie, val);
				break;
			}
			case 2:
			{
				scanf("%u", &val);
				char out_flag = 0;
				erase(trie, val, 31, &out_flag);
				break;
			}
			case 3:
			{
				scanf("%u", &val);
				printf("%u\n", max_xor(trie, val));
				break;
			}
			default:
				break;
		}
	}
	delete(trie);
	return 0;
}