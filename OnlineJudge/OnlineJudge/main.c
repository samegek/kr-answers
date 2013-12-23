#include <stdio.h>

#define YES 1
#define NO	0

int facts[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
int accessed[11] = {1};
int cursum;

int isfactsum(int n, int s, int e);

/* high precision multiplication: the solution to PID 4121. */
int main()
{
	int i, n;
	scanf("%d", &n);
	while (n >= 0){
		for (i = 1; i <= 10; i++)
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

	for (i = s; i <= e; i++)
	{
		if ((cursum + facts[i]) == n)
		{
			return 1;
		}
		else{

		}

	}
}
