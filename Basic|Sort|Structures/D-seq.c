//Имеется последовательность строк:
//
//1. a
//
//2. baa
//
//3. cbaabaa
//
//4. dcbaabaacbaabaa
//
//5. ...
//
//Каждая последующая строка формируется из повторения предыдущей строки и дописывания в начала очередной буквы по алфавиту.
//
//Input format
//N K L
//
//1⩽N⩽26
//
//Нужно вывести подстроку строки N, от символа номер K до символа номер L.
//
//1⩽K⩽L⩽length(string). Нумерация символов строки с единицы.
//
//Output format
//Искомая подстрока
//
//Учтите, что память жёстко ограничена и у вас не получится сформировать целую строку и вырезать из неё нужный кусок

#include <stdio.h>
#include <stdlib.h>

char find_elem(int idx, int row_num, int *size)
{
	if (idx == 0)
		return (char)(97 + row_num);
	if (idx == size[row_num] - 1)
		return (char)(97);
	if (idx <= size[row_num] / 2)
			return find_elem(idx - 1, row_num - 1, size);
	else
		return find_elem(idx - size[row_num]/2 - 1, row_num - 1, size);
}

int main()
{
	int N = 0, K  = 0, L = 0;
	scanf("%d %d %d", &N, &K, &L);
	int *size = calloc(N, sizeof(int));
	size[0] = 1;
	for (int i = 1; i < N; i++)
		size[i] = size[i-1] * 2 + 1;
	for (int i = K-1; i < L; i++)
		printf("%c", find_elem(i, N-1 , size));
	free(size);
	return 0;
}

//Сложность O(N logN)
