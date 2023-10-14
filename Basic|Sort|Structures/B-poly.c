//Быстрое вычисление полинома — важная составляющая многих алгоритмов.
//
//В данной задаче нужно вычислить значение полинома anxn+an-1xn-1+...+a2x2+a1x1+a0
//
//Так как степени и коэффициенты могут быть достаточно большими, чтобы результат был представим в виде элементарного числа, будем вычислять вычислить значение полинома по модулю MOD. Сделать это предлагается для нескольких значений аргумента.
//
//Input format
//Первая строка файла содержит три числа — степень полинома 2⩽N⩽100000, количество вычисляемых значений аргумента 1⩽M⩽10000 и модуль 10⩽MOD⩽109.
//
//Следующие N+1 строк содержат значения коэффициентов полинома 0⩽ai⩽109.
//
//В очередных M строках содержатся значения аргументов 0⩽xi⩽109.
//
//Во втором примере вычисляются последние цифры в десятичном представлении полинома x5 от чисел 1,2,..9. Интересно, что пятые степени всех натуральных чисел заканчиваются на последнюю цифру аргумента.
//
//Output format
//Выходной файл должен состоять из ровно M строк — значений данного полинома при заданных значениях аргументов по модулю MOD

#include <stdio.h>
#include <stdlib.h>

void horner_circuit(unsigned long long const *polynomial, unsigned long long N, unsigned long long MOD, unsigned long long X, unsigned long long *answ)
{
	X = X % MOD;
	*answ = polynomial[0];
	for (int i = 0; i < N; i++)
	{
		*answ *= X;
		*answ = *answ % MOD;
		*answ += polynomial[i+1];
		*answ = *answ % MOD;
	}
}

int main()
{
	unsigned long long N = 0, M = 0, MOD = 0;
	scanf( "%lld %lld %lld", &N, &M, &MOD);
	unsigned long long *polynomial = calloc(N+1, sizeof(unsigned long long));
	unsigned long long *answers = calloc(M, sizeof(unsigned long long));
	for (int i = 0; i <= N; i++)
		scanf("%lld", &polynomial[i]);
	unsigned long long X = 0;
	for (int i = 0; i < M; i++)
	{
		scanf("%lld", &X);
		horner_circuit(polynomial, N, MOD, X, &answers[i]);
	}
	for (int i = 0; i < M; i++)
		printf("%lld\n", answers[i]);
	free(polynomial);
	free(answers);
	return 0;
}