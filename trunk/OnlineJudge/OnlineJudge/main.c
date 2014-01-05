#include <stdio.h>
#include <math.h>

/* solution to the BNU OJ 1040 */
int main()
{
	int t;
	int n;
	double r, s;
	double pi = acos(-1.0);

	scanf("%d", &t);
	while (--t >= 0)
	{
		scanf("%lf%d", &r, &n);
		s = n * 0.5 * r * r * sin(2*pi/n);
		printf("%.3f\n", s);
	}
	return 0;
}