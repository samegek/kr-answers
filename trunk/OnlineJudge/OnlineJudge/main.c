#include <stdio.h>

int facts[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

/* The solution to PID 4124. 
 * This version base on the fact that if n is such a number, it must
 * consist the number closest to it. 
 * For example, 126 is of this kind, 126 must contain 120, or any number
 * smaller than 120 can't compensate the usage of 120. */
int main()
{
	int n, i;
	while (scanf("%d", &n) && n >= 0){

		if (n == 0){
			printf("NO\n");
			continue;
		}
		for (i = 9; i >= 0; i--){
			if (n >= facts[i])
				n -= facts[i];
		}
		
		if (n == 0)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
