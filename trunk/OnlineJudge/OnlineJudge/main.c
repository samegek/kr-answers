#include <stdio.h>

#define YES 1
#define NO	0

int facts[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
int accessed[11];
int n;

int isfactsum(int n, int s, int e);

/* high precision multiplication: the solution to PID 4121. */
int main()
{
	int i;
	scanf("%d", &n);
	while (n >= 0){
		for (i = 1; i <= 10; i++)	/* specify the search region */
		{
			if (facts[i] >= n)
				break;
		}

		if (isfactsum(n, 1, i))
		{
			printf("YES\n");
		} 
		else
		{
			printf("NO\n");
		}
		scanf("%d", &n);
	}

	return 0;
}
/* isfactsum: check if n is a sum of some factorial */
int isfactsum( int n, int s, int e )
{
	int i;

	n -= s;
	if (n == 0)
		return YES;
	else if (n > 0)
	{
		for (i = s + 1; i <= e; i++)
		{
			if (isfactsum(n, i, e) == YES)
				return YES;
		}
	}

	return NO;
}
