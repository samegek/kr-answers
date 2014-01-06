#include <stdio.h>
#include <stdlib.h>


#define MAXARMY 1000000
#define MAXDOCT 1000
#define max(a,b) ((a>=b)?(a):(b))

int army[MAXARMY];
int doctors[MAXDOCT];

int cmp(const void *, const void *);

/* solution to the BNU OJ 1020 
 * ATTENTION: the current solution may be over the time limit */
int main()
{
	int K; /* num of data groups */
	int N, M, P;
	int i, j;
	int minDoct, maxDoct;

	scanf("%d", &K);
	while (--K >= 0){
		scanf("%d%d%d", &N, &M, &P);
		for (i = 0; i < N; i++){
			scanf("%d", &army[i]);
		}
		qsort(army, N, sizeof(int), cmp);
		for (i = N-1; i >= 0; i--){
			/* get number of the accessible doctor 
			 * be careful with the seatch algorithm! */
			minDoct = 0;
			for (j = 1; j < M; j++){
				if (doctors[j] < doctors[minDoct]){
					minDoct = j;
				}
			}
			doctors[minDoct] += army[i];
		}

		maxDoct = 0;
		for (j = 1; j < M; j++){
			if (doctors[j] > doctors[maxDoct]){
				maxDoct = j;
			}
		}

	printf("%.3f", doctors[maxDoct] / (double)P);
	}
	return 0;
}

/* cmp: cmpare function used by qsort */
int cmp(const void *n1, const void *n2)
{
	return *(int*)n1 - *(int*)n2;
}