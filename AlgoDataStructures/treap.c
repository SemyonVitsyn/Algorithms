#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct person
{
	char name[31];
	int val;
} Item;

typedef struct node
{
	Item person;
	int priority;
	int size;
	struct node* left;
	struct node* right;
} Node;

int rand_int() {
	char buff[sizeof(int)];
	for (size_t i = 1 ; i < sizeof(int) ; ++i)
		buff[i] = rand() % 255;
	return *(int*) buff;
}

int get_size(Node* head)
{
	return (head)? head->size : 0;
}

void update_size(Node* head)
{
	if (head == NULL)
		return;
	head->size = 1 + get_size(head->left) + get_size(head->right);
}

Node* treap_new(Item elem)
{
	Node* new = calloc(1, sizeof(Node));
	new->person = elem;
	new->priority = rand_int();
	new->size = 1;
	return new;
}

Node* treap_merge(Node* head1, Node* head2)
{
	if (head1 == NULL)
		return head2;
	if (head2 == NULL)
		return head1;
	if (head1->priority > head2->priority)
	{
		head1->right = treap_merge(head1->right, head2);
		update_size(head1);
		return head1;
	}
	else
	{
		head2->left = treap_merge(head1, head2->left);
		update_size(head2);
		return head2;
	}
}

void treap_split(Node* head, int pos, Node** left, Node** right)
{
	Node* temp = NULL;
	if (head == NULL)
	{
		left = NULL;
		right = NULL;
		return;
	}
	if (get_size(head->left) < pos)
	{
		treap_split(head->right, pos - get_size(head->left) - 1, &temp, right);
		*left = head;
		head->right = temp;
		update_size(head);
	}
	else
	{
		treap_split(head->left, pos, left, &temp);
		*right = head;
		head->left = temp;
		update_size(head);
	}
}

Node* treap_insert(Node* head, int pos, Item elem)
{
	Node* left = NULL;
	Node* right = NULL;
	treap_split(head, pos, &left, &right);
	Node* mid = treap_new(elem);
	return treap_merge(treap_merge(left, mid), right);
}

Node* treap_erase(Node* head, int pos)
{
	Node* left1 = NULL;
	Node* left2 = NULL;
	Node* right1 = NULL;
	Node* right2 = NULL;
	treap_split(head, pos, &left1, &right1);
	treap_split(right1, 1, &left2, &right2);
	head = treap_merge(left1, right2);
	free(left2);
	return head;
	/*Node* left = NULL;
	Node* mid = NULL;
	Node* right = NULL;
	Node* temp = NULL;
	treap_split(head, pos, &left, &right);
	temp = right;
	treap_split(temp, 1, &mid, &right);
	free(mid);
	return treap_merge(left, right);*/
}

Node* treap_find(Node* head, int pos)
{
	if (head == NULL || pos == get_size(head->left))
		return head;
	if (pos < get_size(head->left))
		return treap_find(head->left, pos);
	else
		return treap_find(head->right, pos - get_size(head->left) - 1);
}

Node* treap_delete(Node* head)
{
	if (head == NULL)
		return NULL;
	head->left = treap_delete(head->left);
	head->right = treap_delete(head->right);
	free(head);
	return NULL;
}

void print(Node* head)
{
	if (head == NULL)
		return;
	print(head->left);
	printf("%s %d\n", head->person.name, head->person.val);
	print(head->right);
}

int main()
{
	srand(time(NULL));
	int N = 0, M = 0;
	scanf("%d %d", &N, &M);
	Node *treap = NULL;
	Item person;
	for (int i = 0; i < N; i++)
	{
		scanf("%31s %d", person.name, &person.val);
		treap = treap_insert(treap, i, person);
	}
	int op = 0, idx = 0;
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &op);
		switch (op)
		{
			case 0:
			{
				scanf("%d %31s %d", &idx, person.name, &person.val);
				treap = treap_insert(treap, idx-1, person);
				break;
			}
			case 1:
			{
				scanf("%d", &idx);
				treap = treap_erase(treap, idx-1);
				break;
			}
			case 2:
			{
				scanf("%d", &idx);
				Node* find = treap_find(treap, idx-1);
				printf("%s %d\n", find->person.name, find->person.val);
				break;
			}
			case 3:
			{
				print(treap);
				break;
			}
			default:
				break;
		}
	}
	treap = treap_delete(treap);
	return 0;
}
