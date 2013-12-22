#include <stdio.h>
#include <math.h>
#include <string.h>

#define max(a, b) ((a >= b) ? a : b)
#define MAXN (400+10)

int op1[MAXN];
int op2[MAXN];
int ans[MAXN + MAXN];

void sethp(int *, int);
void hpmul(int *, int *, int *);
void hpprint(int *, int);

/* high precision multiplication: the solution to PID 4121. */
int main()
{
	double R;
	int n, scale;
	while (scanf("%6lf%d", &R, &n)== 2){
		R *= 100000.0;
		R = floor(R + 0.5);
		scale = 5 * n;

		sethp(op1, 1);
		sethp(op2, R);
		while(n--){
			memset(ans, 0, sizeof(ans));		/* set the ans into 0*/
			hpmul(op1, op2, ans);
			memcpy(op1, ans, (*ans + 1)*sizeof(int));

		}
		hpprint(op1, scale);
	}

	return 0;
}

/* sethp: convert num into high precision representation */
void sethp(int *hp, int num)
{
	int count = 0;
	do{
		*(hp + ++count) = num % 10;
	} while (num /= 10);

	*hp = count;
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
/* hpprint: print high precision values, point specifies the 
 * position that divide the fraction part and the integer part */
void hpprint(int *hpv, int point)
{
	int i, j; 
	if (point <= *hpv){
		for (i = *hpv; i > point; i--)
			putchar(*(hpv + i) + '0');
		j = 1;
		while (j <= point && *(hpv + j) == 0)
			j++;	
		if (i >= j)
			putchar('.');
		for(; i >= j; i--)
			putchar(*(hpv + i) + '0');
	}
	else{
		putchar('.');
		j = 1;
		while (*(hpv + j) == 0)
			j++;
		i = point - *hpv;
		while(i--)
			putchar('0');
		for (i = *hpv; i >= j; i--)
			putchar(*(hpv + i) + '0');
	}

	putchar('\n');
}