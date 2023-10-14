#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define mod 1000000000

typedef int Type;

typedef struct node
{
	Type val;
	long long sum;
 	struct node* left;
	struct node* right;
	struct node* parent;
} Node;

struct queue
{
	void *data;
	size_t start;
	size_t end;
	size_t elem_size;
	size_t size;
	size_t capacity;
};

void fix_sum(Node* head)
{
	head->sum = head->val;
	if (head->left != NULL)
		head->sum += head->left->sum;
	if (head->right != NULL)
		head->sum += head->right->sum;
}

void rotate_right(Node* head)
{
	assert(head);
	Node* temp = head->left;
	head->left = temp->right;
	if (temp->right != NULL)
		temp->right->parent = head;
	temp->parent = head->parent;
	if (head->parent != NULL)
	{
		if (head == head->parent->right)
			head->parent->right = temp;
		else
			head->parent->left = temp;
	}
	temp->right = head;
	head->parent = temp;
	fix_sum(head);
	fix_sum(temp);
}

void rotate_left(Node* head)
{
	assert(head);
	Node* temp = head->right;
	head->right = temp->left;
	if (temp->left != NULL)
		temp->left->parent = head;
	temp->parent = head->parent;
	if (head->parent != NULL)
	{
		if (head == head->parent->left)
			head->parent->left = temp;
		else
			head->parent->right = temp;
	}
	temp->left = head;
	head->parent = temp;
	fix_sum(head);
	fix_sum(temp);
}

struct queue *queue_new(size_t elem_size)
{
	assert(elem_size);
	struct queue *new = calloc(1, sizeof(struct queue));
	new->data = calloc(8, elem_size);
	new->elem_size = elem_size;
	new->start = new->end = new->size = 0;
	new->capacity = 8;
	return new;
}

int queue_push(struct queue *q, const void *elem)
{
	assert(q);
	assert(elem);
	if (q->size + 1 == q->capacity)
	{
		size_t count_real_num = q->capacity - q->start;
		q->capacity *= 2;
		struct queue *new = realloc(q->data, q->capacity * q->elem_size);
		if (new != NULL)
			q->data = new;
		else
			return 1;
		if (q->start > q->end)
		{
			memcpy(q->data + (q->capacity - count_real_num) * q->elem_size, q->data + q->start * q->elem_size,
			       count_real_num * q->elem_size);
			q->start = q->capacity - count_real_num;
		}
	}
	memcpy(q->data + q->end * q->elem_size, elem, q->elem_size);
	q->end = (q->end + 1) % q->capacity;
	q->size++;
	return 0;
}

int queue_pop(struct queue *q, void *elem)
{
	assert(q);
	assert(elem);
	if (q->size == 0)
		return 1;
	else
	{
		memcpy(elem, q->data + q->start * q->elem_size, q->elem_size);
		q->start = (q->start + 1) % q->capacity;
		q->size--;
		return 0;
	}
}

int queue_empty(struct queue const *q)
{
	assert(q);
	return (q->size == 0);
}

struct queue *queue_delete(struct queue *q)
{
	assert(q);
	free(q->data);
	free(q);
	return NULL;
}

Node* splay_new(Type x)
{
	Node* new = calloc(1, sizeof(Node));
	new->val = x;
	new->sum = x;
	return new;
}

Node* splay(Node* head)
{
	while (head->parent != NULL)
	{
		if (head->parent->parent == NULL)
		{
			if (head == head->parent->left)
				rotate_right(head->parent);
			else
				rotate_left(head->parent);
		}
		else
		{
			if (head == head->parent->left && head->parent == head->parent->parent->left)
			{
				rotate_right(head->parent->parent);
				rotate_right(head->parent);
			}
			else if (head == head->parent->right && head->parent == head->parent->parent->right)
			{
				rotate_left(head->parent->parent);
				rotate_left(head->parent);
			}
			else if (head == head->parent->right && head->parent == head->parent->parent->left)
			{
				rotate_left(head->parent);
				rotate_right(head->parent);
			}
			else
			{
				rotate_right(head->parent);
				rotate_left(head->parent);
			}
		}
	}
	return head;
}

Node* splay_insert(Node* head, Type x)
{
	if (head == NULL)
		return splay_new(x);
	Node* current = head;
	Node* prev = NULL;
	while (current != NULL)
	{
		prev = current;
		if (x < current->val)
			current = current->left;
		else if (x > current->val)
			current = current->right;
		else return head;
	}
	Node* new = splay_new(x);
	new->parent = prev;
	if (x < prev->val)
		prev->left = new;
	else
		prev->right = new;
	return splay(new);
}

Node* find(Node* head, Type x)
{
	if (head == NULL)
		NULL;
	if (x == head->val)
		return splay(head);
	else if (x < head->val && head->left != NULL)
		return find(head->left, x);
	else if (x > head->val && head->right != NULL)
		return find(head->right, x);
	return splay(head);
}

Node* splay_sum(Node* head, int min, int max, long long* sum)
{
	if (head == NULL)
		return 0;

	*sum = head->sum;
	head = find(head, min);
	if (head->val == min || head->val > min)
		*sum -= (head->left)? head->left->sum : 0;
	else
	{
		*sum -= head->val;
		*sum -= (head->left)? head->left->sum : 0;
	}

	head = find(head, max);
	if (head->val == max || head->val < max)
		*sum -= (head->right)? head->right->sum : 0;
	else
	{
		*sum -= head->val;
		*sum -= (head->right)? head->right->sum : 0;
	}

	return head;
}

Node* splay_delete(Node* head)
{
	if (head == NULL)
		return NULL;
	struct queue* q = queue_new(sizeof(Node*));
	queue_push(q, &head);
	Node* curr;
	while (!queue_empty(q))
	{
		queue_pop(q, &curr);
		if (curr->left != NULL)
			queue_push(q, &curr->left);
		if (curr->right != NULL)
			queue_push(q, &curr->right);
		free(curr);
	}
	q = queue_delete(q);
	return NULL;
}

void print(Node* head)
{
	if (head == NULL)
		return;
	print(head->left);
	printf("%d %lld\n", head->val, head->sum);
	print(head->right);
}

int main()
{
	int N = 0, min = 0, max = 0, x = 0;
	long long sum = 0;
	char op = 0, flag = 0;
	Node *tree = NULL;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%c", &op);
		switch(op)
		{
			case '+':
			{
				scanf("%d", &x);
				if (flag == 0)
					tree = splay_insert(tree, x);
				else
				{
					sum += x;
					tree = splay_insert(tree, (int)(sum % mod));
				}
				flag = 0;
				break;
			}
			case '?':
			{
				scanf("%d %d", &min, &max);
				tree = splay_sum(tree, min, max, &sum);
				printf("%lld\n", sum);
				flag = 1;
				break;
			}
			case 'p':
			{
				print(tree);
				break;
			}
			default:
				i--;
				break;
		}
	}
	tree = splay_delete(tree);
	return 0;
}
