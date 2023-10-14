#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
	unsigned long long val;
	unsigned long long sum;
	int priority;
	unsigned long long size;
	struct node* left;
	struct node* right;
} Node;

int rand_int()
{
	char buff[sizeof(int)];
	for (size_t i = 1 ; i < sizeof(int) ; ++i)
		buff[i] = rand() % 255;
	return *(int*) buff;
}

unsigned long long get_size(Node* head)
{
	return (head)? head->size : 0;
}

unsigned long long get_sum(Node* head)
{
	return (head)? head->sum : 0;
}

void update(Node* head)
{
	if (head == NULL)
		return;
	head->size = 1 + get_size(head->left) + get_size(head->right);
	head->sum = head->val * head->val + get_sum(head->left) + get_sum(head->right);
}

Node* treap_new(unsigned long long val)
{
	Node* new = calloc(1, sizeof(Node));
	new->val = val;
	new->sum = val * val;
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
		update(head1);
		return head1;
	}
	else
	{
		head2->left = treap_merge(head1, head2->left);
		update(head2);
		return head2;
	}
}

void treap_split(Node* head, unsigned long long pos, Node** left, Node** right)
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
		update(head);
	}
	else
	{
		treap_split(head->left, pos, left, &temp);
		*right = head;
		head->left = temp;
		update(head);
	}
}

Node* treap_insert(Node* head, unsigned long long pos, unsigned long long val)
{
	Node* left = NULL;
	Node* right = NULL;
	treap_split(head, pos, &left, &right);
	Node* mid = treap_new(val);
	return treap_merge(treap_merge(left, mid), right);
}

Node* treap_erase(Node* head, unsigned long long pos)
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
}

Node* treap_find(Node* head, unsigned long long pos)
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

Node* bankruptcy(Node* head, unsigned long long pos)
{
	unsigned long long val1 = 0, val2 = 0;
	Node* find = treap_find(head, pos);
	if (pos == 0)
	{
		val1 = find->val;
		head = treap_erase(head, 0);
		find  = treap_find(head, 0);
		val1 += find->val;
		head = treap_erase(head, 0);
		head = treap_insert(head, 0, val1);
	}
	else if (pos == head->size - 1)
	{
		val1 = find->val;
		head = treap_erase(head, pos);
		find  = treap_find(head, pos - 1);
		val1 += find->val;
		head = treap_erase(head, pos - 1);
		head = treap_insert(head, pos - 1, val1);
	}
	else
	{
		val1 = find->val / 2;
		val2 = find->val - val1;
		head = treap_erase(head, pos);
		find = treap_find(head, pos - 1);
		val1 += find->val;
		head = treap_erase(head, pos - 1);
		head = treap_insert(head, pos - 1, val1);
		find = treap_find(head, pos);
		val2 += find->val;
		head = treap_erase(head, pos);
		head = treap_insert(head, pos, val2);
	}
	return head;
}

Node* separation(Node* head, unsigned long long pos)
{
	unsigned long long val1 = 0, val2 = 0;
	Node* find = treap_find(head, pos);
	val1 = find->val / 2;
	val2 = find->val - val1;
	head = treap_erase(head, pos);
	head = treap_insert(head, pos, val1);
	head = treap_insert(head, pos + 1, val2);
	return head;
}

int main()
{
	srand(time(NULL));
	int N = 0, P = 0;
	scanf("%d %d", &N, &P);
	Node *treap = NULL;
	int val = 0;
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &val);
		treap = treap_insert(treap, i, val);
	}
	int op = 0, K = 0;
	unsigned long long idx = 0;
	scanf("%d", &K);
	printf("%lld\n", treap->sum);
	for (int i = 0; i < K; i++)
	{
		scanf("%d", &op);
		switch (op)
		{
			case 1:
			{
				scanf("%lld", &idx);
				treap = bankruptcy(treap, idx - 1);
				printf("%lld\n", treap->sum);
				break;
			}
			case 2:
			{
				scanf("%lld", &idx);
				treap = separation(treap, idx - 1);
				printf("%lld\n", treap->sum);
				break;
			}
			default:
				break;
		}
	}
	treap = treap_delete(treap);
	return 0;
}