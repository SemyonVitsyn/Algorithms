#include <stdio.h>
#include <stdlib.h>

struct letter
{
	int num;
	int count;
};

int compare(const void *x1, const void *x2)
{
	struct letter elem1 = *(struct letter*)x1;
	struct letter elem2 = *(struct letter*)x2;
	if (elem1.count == elem2.count)
		return elem1.num - elem2.num;
	else
		return elem2.count - elem1.count;
}

struct letter *find_count()
{
	char ch = 0;
	struct letter *arr = calloc(26, sizeof(struct letter));
	for (int i = 0; i < 26; i++)
		arr[i].num = i;
	while ((ch = getchar()) != '\n')
		arr[ch - 65].count++;
	qsort(arr, 26, sizeof(struct letter), compare);
	return arr;
}

int main()
{
	struct letter *arr = find_count();
	for (int i = 0; i < 26; i++)
	{
		if (arr[i].count > 0)
			printf("%c %d\n", 65 + arr[i].num, arr[i].count);
	}
	free(arr);
	return 0;
}
