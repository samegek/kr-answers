#include <stdio.h>
#include <string.h>

#define max(a, b) ((a >= b) ? a : b)
#define MAXN (400+10)

int op1[MAXN];
int op2[MAXN];
int ans[MAXN + MAXN];

void sethp(int *, int);
void hpmul(int *, int *, int *);
void hpprint(int *);

/* high precision multiplication: the solution to PID 4121. */
int main()
{
	int R;
	int n;
	while (scanf("%d%d", &R, &n)== 2){



		memset(ans, 0, sizeof(ans));		/* set the ans into 0*/
		hpmul(op1, op2, ans);dx
		hpprint(ans);
	}

	return 0;
}

void sethp(int *hp, int num)
{

}

/* hpmul: multiple to hp(high precision) represented number */
void hpmul(int *op1, int *op2, int *ans)
{
	int i, j, k;


	/* multiplication */
	for (i = 1; i <= *op1; i++){
		for (j = 1; j <= *op2; j++){
			k = i + j - 1;
			*(ans + k) += *(op1 + i) * *(op2 + j);
			*(ans + k + 1) += *(ans + k) / 10; /* handle the carry */
			*(ans + k) %= 10;
		}
	}

	/* count the length of the answer */
	i = *op1 + *op2;
	while (i > 0 && *(ans + i) == 0)
		i--;
	if (i != 0)
		*ans = i;
	else
		*ans = 1;
}

void hpprint(int *hpv)
{
	int i; 
	for (i = *hpv; i > 0; i--)
		putchar(*(hpv + i) + '0');

	putchar('\n');
}