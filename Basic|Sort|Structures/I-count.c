//Комментарием в языке Object Pascal является любой текст, находящийся между последовательностью символов, начинающих комментарий определённого вида и последовательностью символов, заканчивающей комментарий этого вида.
//
//Виды комментариев могут быть следующие:
//
//Начинающиеся с набора символов (* и заканчивающиеся набором символов *).
//Начинающиеся с символа { и заканчивающиеся символом }.
//Начинающиеся с набора символов // и заканчивающиеся символом новой строки
//.
//Еще в языке Object Pascal имеются литеральные строки, начинающиеся символом одиночной кавычки ' (ASCII код 39) и заканчивающиеся этим же символом. В корректной программе строки не могут содержать символа перехода на новую строку.
//
//Input format
//На вход программы подаётся набор строк, содержащих фрагмент корректной программы на языке Object Pascal. Обратите внимание на слово фрагмент и на последнюю строчку примера. Комментарии не вкладываются друг в друга.
//Output format
//Выходом программы должны быть четыре числа — количество комментариев первого, второго и третьего типов, а также количество литеральных строк.

#include <stdio.h>
#include <assert.h>

enum status
{
	STAR_COMM,
	BRACKET_COMM,
	INLINE_COMM,
	STRING,
	NORMAL
};

enum status count(char ch1, char ch2, enum status const st, int *obj_count)
{
	assert(obj_count);
	switch (st)
	{
		case NORMAL:
		{
			if (ch1 == '(' && ch2 == '*')
				return STAR_COMM;
			if (ch1 == '/' && ch2 == '/')
			{
				obj_count[2]++;
				return INLINE_COMM;
			}
			if (ch1 == '{')
				return BRACKET_COMM;
			if (ch1 == '\'')
				return STRING;
			if (ch2 == '{')
				return BRACKET_COMM;
			if (ch2 == '\'')
				return STRING;
			return NORMAL;
		}
		case STAR_COMM:
		{
			if (ch1 == '*' && ch2 == ')')
			{
				obj_count[0]++;
				return NORMAL;
			}
			return STAR_COMM;
		}
		case BRACKET_COMM:
		{
			if (ch1 == '}' || ch2 == '}')
			{
				obj_count[1]++;
				return NORMAL;
			}
			return BRACKET_COMM;
		}
		case INLINE_COMM:
		{
			if (ch1 == '\n' || ch2 == '\n')
				return NORMAL;
			return INLINE_COMM;
		}
		case STRING:
		{
			if (ch1 == '\'' || ch2 == '\'')
			{
				obj_count[3]++;
				return NORMAL;
			}
			return STRING;
		}
		default:
		{
			return NORMAL;
		}
	}
}

int main()
{
	enum status st = NORMAL;
	int obj_count[4] = {0};
	char ch1 = 0, ch2 = 0;
	while ((ch1 = getchar()) != -1)
	{
		if ( (st == NORMAL && (ch1 == '(' || ch1 == '/' || ch1 == '*')) ||
		     (st != NORMAL && ch1 == '*') )
			ch2 = getchar();
		else
			ch2 = ' ';
		st = count(ch1, ch2, st, obj_count);

	}
	for (int i = 0; i < 4; i++)
		printf("%d ", obj_count[i]);
	return 0;
}

// Сложность O(n)