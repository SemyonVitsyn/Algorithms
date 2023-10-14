#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct data
{
	char key[21];
	char val[21];
} Item;

typedef struct node
{
	Item elem;
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

Node* tree_insert(Node* head, Item elem)
{
	if (head == NULL)
	{
		head = calloc(1, sizeof(Node));
		head->elem = elem;
		head->height = 1;
		return head;
	}
	if (strcmp(elem.key, head->elem.key) < 0)
		head->left = tree_insert(head->left, elem);
	else if (strcmp(elem.key, head->elem.key) > 0)
		head->right = tree_insert(head->right, elem);
	else
		strcpy(head->elem.val, elem.val);
	return balance(head);
}

Node* tree_find(Node* head, char key[21])
{
	if (head == NULL)
		return NULL;
	if (strcmp(key, head->elem.key) == 0)
		return head;
	else if (strcmp(key, head->elem.key) < 0)
		return tree_find(head->left, key);
	else
		return tree_find(head->right, key);
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

Node* tree_erase(Node* head, char key[21])
{
	if (head == NULL)
		return NULL;
	if (strcmp(key, head->elem.key) < 0)
		head->left = tree_erase(head->left, key);
	else if (strcmp(key, head->elem.key) > 0)
		head->right = tree_erase(head->right, key);
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
	char op[21] = {0}, key[21] = {0}, val[21] = {0};
	Node *tree = NULL;
	while (scanf("%21s", op) != EOF)
	{
		if (strcmp(op, "insert") == 0)
		{
			scanf("%21s %21s", key, val);
			Item elem;
			strcpy(elem.key, key);
			strcpy(elem.val, val);
			tree = tree_insert(tree, elem);
		}
		else if (strcmp(op, "erase") == 0)
		{
			scanf("%21s", key);
			tree = tree_erase(tree, key);
		}
		else if (strcmp(op, "find") == 0)
		{
			scanf("%20s", key);
			Node* find = tree_find(tree, key);
			if (find == NULL)
				printf("MISSING\n");
			else
				printf("%s\n", find->elem.val);
		}
	}
	tree = tree_delete(tree);
	return 0;
}
