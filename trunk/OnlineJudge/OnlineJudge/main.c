#include <stdio.h>

#define YES 1
#define NO	0

int facts[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

int search(int n, int s, int e);
int isfactsum(int n, int e);

/* high precision multiplication: the solution to PID 4121. */
int main()
{
	int n;
	int i, bound;

	scanf("%d", &n);
	while (n >= 0){
		for (i = 1; i <= 10; i++)	/* specify the search region */
		{
			if (facts[i] > n)
				break;
		}
		if (isfactsum(n, i - 1) == YES)
			printf("YES\n");
		else
			printf("NO\n");
		scanf("%d", &n);
	}

	return 0;
}
int isfactsum(int n, int e)
{
	int i;
	for (i = 0; i <= e; i++)
		if (search(n, i, e) == YES)
			return YES;
	return NO;
}

/* isfactsum: check if n is a sum of some factorial */
int search( int n, int s, int e )
{
	int i;

	n -= facts[s];
	if (n == 0)
		return YES;
	else if (n > 0)
	{
		for (i = s + 1; i <= e; i++)
		{
			if (search(n, i, e) == YES)
				return YES;
		}
	}

	return NO;
}
