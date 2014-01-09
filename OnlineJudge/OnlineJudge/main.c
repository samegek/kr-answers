#include <stdio.h>

int josephus(int n, int m);

/* solution to the BNU OJ 1007 */
int main()
{
	int n, m;
	int last;

	scanf("%d%d", &n, &m);
	last = josephus(n-1, m) + 2;
	printf("%d\n", last);

	return 0;
}

/* josephus: return the last counted number in a Josuphus Ring */
int josephus(int n, int m)
{
	if (n == 2){
		if (m % 2 == 1)	/* if m is odd */
			return 1;
		else
			return 0;
	}
	else if (n > 2){
		int k = m % n - 1;
		return ((josephus(n - 1, m) + k) % n);
	}
	else{
		return -1;
	}	
}

