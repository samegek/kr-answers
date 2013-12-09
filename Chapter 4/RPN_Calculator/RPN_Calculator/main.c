#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXOP 100		/* max size of a operand */
#define NUMBER '0'		/* signal that a number was found */
#define LIBFUN '1'
#define VARS '2'

int getop(char []);
void push(double);
double pop(void);
double top(void);
void duptop(void);
void swtop(void);
void clearstack(void);

int getch(void);
void ungetch(int);

void calcLibFun(char s[]);

/* RPN(Reverse Polish Calculator)
 * These files are the solutions to K&R C 4-3~4-9*/
main()
{
	int type, i;
	double op2, vars[26], ans;
	char s[MAXOP];
	
	ans = 0;
	for (i = 0; i < 26; ++i)
		vars[i] = 0;

	printf("Welcome to RPN Calculator!\nEnter RPN expression and hit enter.\n");

	while ((type = getop(s)) != EOF)
	{
		switch (type)
		{
		case NUMBER:
			push(atof(s));
			break;
		case LIBFUN:
			calcLibFun(s);
			break;
		case VARS:
			push(vars[s[0] - 'A']);
			break;
		case 'v':
			push(ans);
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else{
				printf("error: zero divisor!\n");
			}
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push(fmod(pop(), op2));
			else
				printf("error: zero divisor");
			break;
		case '?':	/* print the top of the stack */
			printf("\t%.8g\n", top());
			while (getch() != '\n')
				;
			break;
		case '#':	/* duplicate the top element of the stack */
			duptop();
			while (getch() != '\n')
				;
			break;
		case '$':
			swtop();
			while (getch() != '\n')
				;
			break;
		case '!':
			clearstack();
			while (getch() != '\n')
				;
			break;
		case '=':
			if(getop(s) != NUMBER){
				printf("error: assignment without a variable.\n");
				break;
			}
			push(vars[s[0] - 'A'] = pop());
			break;
		case '\n':
			printf("\t%.8g\n", ans = pop());
			break;
		case 'q':
			printf("Bye!");
			return 0;
		default:
			while (getch() != '\n')
				;
			printf("error: unknown command %s\n", s);
			break;
		}
	}

	return 0;
}

void calcLibFun(char s[])
{
	double op2;

	if (strcmp(s, "sin") == 0)
		push(sin(pop()));
	else if (strcmp(s, "exp") == 0)
		push(exp(pop()));
	else if (strcmp(s, "pow") == 0){
		op2 = pop();
		push(pow(pop(), op2));
	}
	else
		printf("error: unknown command %s\n", s);

}

#define MAXVAL 100 /*maximum depth of val stack */

int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n");
}

/* pop: pop and return the top value of the stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else{
		printf("error: stack empty, can't pop\n");
		return 0.0;
	}
}
/* top: return the top element of the stack */
double top(void)
{	
	if (sp > 0)
		return val[sp - 1];
	else{
		printf("error: stack empty, no top element!\n");
		return 0.0;
	}
}
/* duptop: dup the top element of the stack */
void duptop(void)
{
	if (sp == 0){
		printf("error: stack empty, can't duplicate!\n");
		return;
	}
	if (sp == MAXVAL){
		printf("error: stack full, can't duplicate %g\n", top());
		return;
	}

	push(top());
}

/* swtop: swap the top 2 elements of the stack */
void swtop(void)
{
	double temp;
	if (sp > 1){
		temp = val[sp - 1];
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = temp;
	}
	else
		printf("error: no enough elements to perform swap.\n");
}

void clearstack(void)
{
	sp = 0;
}

#include <ctype.h>

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



#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;
/* getch: get one char from the buffer, if not use getchar[] */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
	//return (bufp > 0) ? buf[0] : getchar();	/* solution to the 4-8 */
}
/*ungetch: return one char into the buffer */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
		//buf[0] = c;							/* solutions to the 4-8 */
}
/* ungets: return the s strings into the buffer */
void ungets(char s[])
{
	int i;
	for (i = 0; s[i] != '\0'; ++i)
	{
		ungetch(s[i]);
	}
}