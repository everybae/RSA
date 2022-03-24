#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define MAX 30

char m[MAX];

int sosucheck = 1;

int sosu(int);
int get_e(int);
int get_d(int, int);
int encryption(int, int, int);
char decryption(int, int, int);

int main()
{
	int i;
	int data;
	int p = 0, q = 0;
	int n = 0;
	int e;
	int d;
	int c[MAX];
	char dec_M[MAX];
	int lenth;

	srand(time(0));

	do {
		do {
			sosucheck = 1;
			while (sosucheck) 
			{
				p = (rand() % (200-100)) + 100;  //난수생성
				sosucheck = sosu(p);
				//생성된 난수가 소수인지 판별한다
			}
			sosucheck = 1;
			while (sosucheck) 
			{
				q = (rand() % (200-100)) + 100; //난수생성
				sosucheck = sosu(q);
				//생성된 난수가 소수인지 판별한다
			}
		} 
		while (p == q);

		printf("\nInput M => ");
		gets(m);
		printf("\n평문 M = ");
		puts(m);

		printf("(p= %d , q= %d)\n", p, q);
		n = p * q;

		e = get_e((p - 1) * (q - 1));

		printf("공개키 : (e=%d),(N=%d)\n", e, n);

		d = get_d(e, (p - 1) * (q - 1));

		printf("개인키 : (d=%d)\n", d);
		lenth = strlen(m);
		printf("암호문 : ");
		for (i = 0; i < lenth; i++)
		{
			data = m[i];
			c[i] = encryption(data, e, n);
			printf("%d ", c[i]);
		}

		printf("\n복호화된 평문 : ");
		for (i = 0; i < lenth; i++)
		{
			dec_M[i] = decryption(c[i], d, n);
			printf("%c", dec_M[i]);
		}

	} while (strcmp(m, "quit") != 0);
	getchar();
}




int encryption(int m, int e, int n)
{
	int i;
	double s = 1;

	for (i = 1; i <= e; i++)
	{
		if (s != 0)
		{
			s = s * m;	
			s = (int)s % n;
		}
		else
			s = s * m;
		s = (int)s % n;
	}
	return (int)s;
}

char decryption(int c, int d, int n)
{
	int i;
	double s = 1;

	for (i = 1; i <= d; i++)
	{
		if (s != 0)
		{
			s = s * c;
			s = (int)s % n;
		}
		else
			s = s * c;
		s = (int)s % n;
	}
	return (char)s;

}
int get_d(int e, int d_num)
{
	int i = 1, d = 1;
	while (i)
	{
		for (d = 1; d < 999999; d++)
		{
			if (((e * d) - 1) % (d_num * i) == 0)
			{
				return d;
			}
		}
	}
	return -1;
}

int get_e(int e_num)
{
	int e, j;
	int small;
	int big;
	int count = 0;
	for (e = 3; e < 999999; e += 2)      
	{
		if (e < e_num)
		{
			small = e_num; big = e_num;
		}
		else
		{
			small = e_num; big = e;
		}

		for (j = 1; j <= small; j++)
		{
			if (small % j == 0 && big % j == 0)

				count++;
		}
		if (count == 1)
		{
			return e;
		}
		else
		{
			count = 0;
		}
	}
	return -1;
}

int sosu(int n)
{
	int i;
	if (n == 1)
		return 1;
	if (n == 2)
		return 1;

	for (i = 2; i < n; i++)
	{
		if (n % i == 0)
			return 1;
	}
	return 0;
}

