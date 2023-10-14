#include <stdio.h>
#include <stdlib.h>

void RSort_step(unsigned *source, unsigned *dest, unsigned int n, unsigned int *offset, unsigned char sortable_bit)
{
	unsigned char *b = (unsigned char*)&source[n].key + sortable_bit;

	for (unsigned int i = 0; i < n; ++i)
	{
		unsigned const src = source[i];
		unsigned int off = (src >> (sortable_bit * 8)) & 0xFF;
		dest[offset[off]++] = src;
	}
}
//=============================================================
void RSort_Node(TNode *m, unsigned int n)
{
	// Выделяем память под временный массив
	TNode *m_temp = (TNode*)malloc(sizeof(TNode) * n);

	// Заводим массив корзин
	unsigned int s[sizeof(m->key) * 256] = {0};
	// Заполняем массив корзин для всех разрядов
	for (unsigned int i = 0; i < n; ++i)
	{
		unsigned int key = m[i].key;
		for (unsigned int digit=0; digit< sizeof(m->key); digit++)
		{
			s[((key >> (digit * 8)) & 0xFF) +256*digit]++;
		}
	}

	// Пересчитываем смещения для корзин
	for (unsigned int digit=0; digit< sizeof(m->key); digit++)
	{
		unsigned int off = 0;
		for (unsigned int i = 0; i < 256; i++)
		{
			unsigned int value = s[i+256*digit];
			s[i+256*digit] = off;
			off += value;
		}
	}

	// Вызов сортировки по битам от младших к старшим (LSD)
	for (unsigned int digit=0; digit< sizeof(m->key); digit++)
	{
		RSort_step(m, m_temp, n, &s[256*digit] ,digit);
		TNode *temp = m;
		m = m_temp;
		m_temp = temp;
	}

	// Если ключ структуры однобайтовый, копируем отсортированное в исходный массив
	if (sizeof(m->key)==1)
	{
		TNode *temp = m;
		m = m_temp;
		m_temp = temp;
		memcpy(m, m_temp, n * sizeof(TNode));
	}

	free(m_temp);
}

int main()
{
    unsigned array[8] = {3,1,4,1,5,9,303,1};
    fast_sort(array, array+8);
    for (int i = 0; i < 8; i++)
    	printf("%u ", array[i]);
    return 0;
    // Now array = {1,1,2,3,4,5,6,9}
}
