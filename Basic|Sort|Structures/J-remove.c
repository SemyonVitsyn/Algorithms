//Елпидифор пишет новую программу, которая точно устанавливает факт заимствования чужого кода. Для этого он разбивает процесс анализа программы на этапы. Так как комментарии не влияют на алгоритм программы, обработка начинается с удаления всех комментариев. Помогите ему!
//
//Однострочным комментарием является комментарий, начинающийся с // и заканчивающийся переводом строки или концом файла.
//
//Многострочным комментарием называется комментарий, начинающийся с /* и заканчивающийся */, даже если он помещается на одной строке текста.
//
//Обратите внимание на то, что в C и C++ ещё имеются строки, внутри которых комментариев не бывает!
//
//Input format
//На стандартный ввод поступает текст корректной программы, в которой, возможно, содержатся комментарии. Длина текста программы может быть весьма большой.
//
//...
//
//Output format
//Текст программы, избавленный от комментариев. Каждый комментарий должен быть заменён ровно одним символом: однострочные комментарии — символом '\n', многострочные — одиночным пробелом.

#include <stdio.h>

enum status
{
	SHORT_COMM,
	LONG_COMM,
	STRING,
	CHAR,
	NORMAL
};

void rmv()
{
	char c = 0, ch = 0;
	enum status st = NORMAL;
	while ((c = getchar()) != -1)
	{
		switch(st)
		{
			case NORMAL:
			{
				if (c == '"')
				{
					printf("%c", c);
					st = STRING;
				}
				else if (c == '\'')
				{
					printf("%c", c);
					st = CHAR;
				}
				else if (c == '/')
				{
					ch = getchar();
					if (ch == '/')
						st = SHORT_COMM;
					else if (ch == '*')
						st = LONG_COMM;
					else
						printf("%c%c", c, ch);
				}
				else
					printf("%c", c);
				break;
			}
			case STRING:
			{
				if (c == '"')
					st = NORMAL;
				printf("%c", c);
				break;
			}
			case CHAR:
			{
				if (c == '\'')
					st = NORMAL;
				printf("%c", c);
				break;
			}
			case SHORT_COMM:
			{
				if (c == '\n')
				{
					printf("%c", c);
					st = NORMAL;
				}
				break;
			}
			case LONG_COMM:
			{
				if (c == '*')
				{
					ch = getchar();
					if (ch == '/')
					{
						st = NORMAL;
						printf(" ");
					}
				}
				break;
			}
		}
	}
}

int main()
{
	rmv();
	return 0;
}