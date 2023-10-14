#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct person
{
	char* name;
	int val;
	int time;
} Person;

typedef struct data
{
	char* name;
	int idx;
} Item;

typedef struct node
{
	Item elem;
	unsigned char height;
	struct node* left;
	struct node* right;
	struct node* parent;
} Node;

int compare(const void* x1, const void* x2)
{
	Person p1 = *(Person*)x1, p2 = *(Person*)x2;
	if (p1.val != p2.val)
		return p2.val - p1.val;
	else
		return p1.time - p2.time;
}

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

Node* tree_insert(Node* head, Item elem, int name_len)
{
	if (head == NULL)
	{
		head = calloc(1, sizeof(Node));
		head->elem.name = calloc(name_len + 1, sizeof(char));
		strcpy(head->elem.name, elem.name);
		head->elem.idx = elem.idx;
		head->height = 1;
		return head;
	}
	if (strcmp(elem.name, head->elem.name) < 0)
		head->left = tree_insert(head->left, elem, name_len);
	else if (strcmp(elem.name, head->elem.name) > 0)
		head->right = tree_insert(head->right, elem, name_len);
	return balance(head);
}

Node* tree_find(Node* head, char* name)
{
	if (head == NULL)
		return NULL;
	if (strcmp(name, head->elem.name) == 0)
		return head;
	else if (strcmp(name, head->elem.name) < 0)
		return tree_find(head->left, name);
	else
		return tree_find(head->right, name);
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

Node* tree_delete(Node* head)
{
	if (head == NULL)
		return NULL;
	head->left = tree_delete(head->left);
	head->right = tree_delete(head->right);
	free(head->elem.name);
	free(head);
	return NULL;
}

int main()
{
	Item elem;
	elem.name = calloc(41, sizeof(char));
	int M = 0, N = 0, size = 0, val = 0;
	char buf[41] = {0};
	Node *tree = NULL;
	scanf("%d %d", &M, &N);
	Person* players = calloc(M, sizeof(Person));
	for (int i = 0; i < N; i++)
	{
		scanf("%41s %d", buf, &val);
		Node *find = tree_find(tree, buf);
		if (find == NULL)
		{
			players[size].name = calloc(strlen(buf) + 1, sizeof(char));
			strcpy(players[size].name, buf);
			players[size].val = val;
			players[size].time = i;
			elem.idx = size++;
			strcpy(elem.name, buf);
			tree = tree_insert(tree, elem, strlen(buf));
		}
		else if (val > players[find->elem.idx].val)
		{
			players[find->elem.idx].val = val;
			players[find->elem.idx].time = i;
		}
	}
	qsort(players, size, sizeof(Person), compare);
	for (int i = 0; i < size; i++)
		printf("%s\n", players[i].name);
	tree = tree_delete(tree);
	for (int i = 0; i < size; i++)
		free(players[i].name);
	free(players);
	free(elem.name);
	return 0;
}