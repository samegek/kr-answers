#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXARMY 1000010
#define MAXDOCT 1010

int army[MAXARMY];
int doctors[MAXDOCT];

int cmp(const void *, const void *);

void MinHeapFixdown(int heap[], int i, int n);

/* solution to the BNU OJ 1020 
 * ATTENTION: the current solution may be over the time limit */
int main()
{
	int K; /* number of data groups */
	int N, M, P;
	int i;
	int minDoct, maxDoct;
	double result;
	scanf("%d", &K);
	while (--K >= 0){
		scanf("%d%d%d", &N, &M, &P);
		for (i = 0; i < N; i++){
			scanf("%d", &army[i]);
		}
		memset(doctors, 0, sizeof(int) * MAXDOCT);

		qsort(army, N, sizeof(int), cmp);
		for (i = N-1; i >= 0; i--){
			doctors[0] += army[i];
			MinHeapFixdown(doctors, 0, M);
		}

		/* find the doctor who works the longest time*/
		maxDoct = M - 1;
		for (i = M - 1; i >= 0; i--){
			if (doctors[i] > doctors[maxDoct]){
				maxDoct = i;
			}
		}
		result = doctors[maxDoct] / (double)P;
		printf("%.3f\n", result);
	}

	return 0;
}

/* cmp: compare function used by qsort */
int cmp(const void *n1, const void *n2)
{
	return *(int*)n1 - *(int*)n2;
}

/* MinHeapFixdown: fix the heap from top */
void MinHeapFixdown(int heap[], int i, int n)
{
	int temp = heap[i];
	int minchild = 2 * i + 1;

	while (minchild < n)
	{
		if (minchild + 1 < n && heap[minchild + 1] < heap[minchild])
			minchild += 1;

		if (temp <= heap[minchild])
			break;

		heap[i] = heap[minchild];

		i = minchild;
		minchild = 2 * i + 1;
	}

	heap[i] = temp;
}