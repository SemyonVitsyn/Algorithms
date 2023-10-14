//Множество задано строкой, состоящей из букв латинского алфавита и цифр. Каждый символ строки есть элемент множества.
//
//Но это множество — не совсем простое. Элементы в нём могут повторяться.
//
//Два подмножества считаются одинаковыми, если все элементы одного множества совпадают с элементами другого. Например, множества, представленные строками abc и cba совпадают. Совпадают также множества abra и raba.
//
//Ваша задача по заданной строке, представляющей исходное множество, вывести все различные его подмножества, каждое на отдельной строке вывода. Выводить можно в произвольном порядке. Выход не должен содержать совпадающие подмножества.
//
//Пустое множество тоже является подмножеством исходного.
//
//Input format
//Исходное множество в виде строки
//
//Output format
//Все уникальные подмножества исходного множества по одному на строку. Подмножества не требуется как-либо упорядочивать, будет принят любой верный ответ.
//
//Не забудьте, что пустая строка — тоже верное подмножество. В приведённом примере она следует первой, перед строкой a.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* form_string(int *len) //Чуть подправил, просто хотелось написать свою функцию для общего случая.
{
	assert(len);
	int capacity = 2;
	char ch = 0;
	*len = 0;
	char *str = calloc(capacity, sizeof(char));
	while ((ch = getchar()) != '\n')
	{
		if (*len == capacity)
		{
			capacity = capacity * 2;
			char *new = realloc(str, capacity * sizeof(char));
			if (new != NULL)
				str = new;
			else
				return NULL;
		}
		str[*len] = ch;
		(*len)++;
	}
	return str;
}

void sets(char symbol, int *symbol_count, char *curr_str)
{
	if (symbol > 'z')
	{
		printf("%s\n", curr_str);
		return;
	}
	sets(symbol + 1, symbol_count, curr_str);
	for (int i = 0; i < symbol_count[symbol-48]; i++)
	{
		curr_str[strlen(curr_str)] = symbol;
		sets(symbol + 1, symbol_count, curr_str);
	}
	memset(curr_str + strlen(curr_str) - symbol_count[symbol-48], 0, symbol_count[symbol-48]);
}

int main()
{
	int len = 0;
    char *string = form_string(&len);
    assert(string);
    int *symbol_count = calloc(75, sizeof(int));
    for (int i = 0; i < len; i++)
        symbol_count[string[i] - 48]++;
    char *curr_str = calloc(len, sizeof(char));
    sets('0', symbol_count, curr_str);
    free(string);
    free(curr_str);
    free(symbol_count);
    return 0;
}

// Сложность O(2^len)