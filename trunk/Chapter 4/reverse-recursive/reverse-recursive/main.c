#include <stdio.h>
#include <string.h>

void reverse(char[], int, int);

/* This is the solution to the K&R C 4-13 */
main()
{
	char s[] = "I am the object to reverse.";
	
	reverse(s, 0, strlen(s) - 1);
	printf("%s\n", s);

	reverse(s, 0, strlen(s) - 1);
	printf("%s\n", s);

	return 0;
}

void reverse(char s[], int left, int right)
{
	int temp;
	
	if (left >= right)
	{
		return;
	}
	else
	{
		temp = s[left];
		s[left] = s[right];
		s[right] = temp;

		reverse(s, left + 1, right - 1);

	}
}