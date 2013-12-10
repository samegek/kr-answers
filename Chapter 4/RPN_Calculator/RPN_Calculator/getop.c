#include <stdio.h>
#include <ctype.h>
#include "Calc.h"

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	if (isupper(c))
		return VARS;

	i = 0;
	if (!isdigit(c) && c != '.' && c != '-' )	
		switch (c){
			case 's':		/* maybe a lib function from math.h */
			case 'e':
			case 'p':
				while (isalpha(s[++i] = c = getch()))
					;
				s[i] = '\0';
				if (c != EOF)
					ungetch(c);
				return LIBFUN;
			default:
				return c;	/* not a number or lib functions */
				break;
		}

	if (c == '-')
		if (!isdigit(s[++i] = c = getch()) && c != '.'){
			ungetch(c);
			s[1] = '\0';
			return '-';	/* '-' is minus sign rather than a unary negative */
		}

	if (isdigit(c))	/* collect the integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')	/* collect the fractional part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	
	if (c != EOF)
		ungetch(c);
	
	return NUMBER;
}
