#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct node
{
	long long elem;
	unsigned char height;
	struct node* left;
	struct node* right;
} Node;

unsigned char height(Node* head)
{
	if (head != NULL)
		return head->height;
	else
		return 0;
}

int balance_factor(Node* head)
{
	assert(head);
	return height(head->right) - height(head->left);
}

void fix_height(Node* head)
{
	assert(head);
	unsigned char left_height = height(head->left);
	unsigned char right_height = height(head->right);
	head->height = (left_height > right_height ? left_height : right_height) + 1;
}

Node* rotate_right(Node* head)
{
	assert(head);
	Node* temp = head->left;
	head->left = temp->right;
	temp->right = head;
	fix_height(head);
	fix_height(temp);
	return temp;
}

Node* rotate_left(Node* head)
{
	assert(head);
	Node* temp = head->right;
	head->right = temp->left;
	temp->left = head;
	fix_height(head);
	fix_height(temp);
	return temp;
}

Node* balance(Node* head)
{
	fix_height(head);
	if (balance_factor(head) == 2)
	{
		if (balance_factor(head->right) < 0)
			head->right = rotate_right(head->right);
		return rotate_left(head);
	}
	if (balance_factor(head) == -2)
	{
		if (balance_factor(head->left) > 0)
			head->left = rotate_left(head->left);
		return rotate_right(head);
	}
	return head;
}

Node* tree_insert(Node* head, long long elem)
{
	if (head == NULL)
	{
		head = calloc(1, sizeof(Node));
		head->elem = elem;
		head->height = 1;
		return head;
	}
	if (elem < head->elem)
		head->left = tree_insert(head->left, elem);
	else if (elem > head->elem)
		head->right = tree_insert(head->right, elem);
	else
		return head;
	return balance(head);
}

Node* tree_find(Node* head, long long elem)
{
	if (head == NULL)
		return NULL;
	if (elem == head->elem)
		return head;
	else if (elem < head->elem)
		return tree_find(head->left, elem);
	else
		return tree_find(head->right, elem);
}

Node* find_min(Node* head)
{
	assert(head);
	if (head->left == NULL)
		return head;
	else
		return find_min(head->left);
}

Node* remove_min(Node* head)
{
	assert(head);
	if (head->left == NULL)
		return head->right;
	head->left = remove_min(head->left);
	return balance(head);
}

Node* tree_erase(Node* head, long long elem)
{
	if (head == NULL)
		return NULL;
	if (elem < head->elem)
		head->left = tree_erase(head->left, elem);
	else if (elem > head->elem)
		head->right = tree_erase(head->right, elem);
	else
	{
		if (head->right == NULL)
		{
			Node* temp = head->left;
			free(head);
			return temp;
		}
		Node* left = head->left;
		Node* right = head->right;
		free(head);
		Node* min = find_min(right);
		min->right = remove_min(right);
		min->left = left;
		return balance(min);
	}
	return balance(head);
}

void tree_print(Node* head)
{
	if (head == NULL)
		return;
	tree_print(head->left);
	printf("%lld ", head->elem);
	tree_print(head->right);
}

Node* tree_delete(Node* head)
{
	if (head == NULL)
		return NULL;
	head->left = tree_delete(head->left);
	head->right = tree_delete(head->right);
	free(head);
	return NULL;
}

int main()
{
	char op[3] = {0}, zero_flag = 1;
	int N = 0, M = 0, idx = 0;
	long long elem = 0;
	scanf("%d %d", &N, &M);
	Node **tree_arr = calloc(N + 1, sizeof(Node *));
	for (int i = 0; i < M; i++)
	{
		scanf("%3s", op);
		if (strcmp(op, "+") == 0)
		{
			scanf("%lld %d", &elem, &idx);
			tree_arr[idx] = tree_insert(tree_arr[idx], elem);
		}
		else if (strcmp(op, "-") == 0)
		{
			scanf("%lld %d", &elem, &idx);
			tree_arr[idx] = tree_erase(tree_arr[idx], elem);
		}
		else if (strcmp(op, "=") == 0)
		{
			scanf("%d", &idx);
			tree_arr[idx] = tree_delete(tree_arr[idx]);
		}
		else if (strcmp(op, "?") == 0)
		{
			scanf("%d", &idx);
			if (tree_arr[idx] == NULL)
				printf("-1");
			else
				tree_print(tree_arr[idx]);
			printf("\n");
		}
		else if (strcmp(op, "??") == 0)
		{
			zero_flag = 1;
			scanf("%lld", &elem);
			for (int j = 0; j < N + 1; j++)
			{
				Node* find = tree_find(tree_arr[j], elem);
				if (find != NULL)
				{
					printf("%d ", j);
					zero_flag = 0;
				}
			}
			if (zero_flag == 1)
				printf("-1");
			printf("\n");
		}
	}
	for (int i = 0; i < N + 1; i++)
		tree_arr[i] = tree_delete(tree_arr[i]);
	free(tree_arr);
	return 0;
}