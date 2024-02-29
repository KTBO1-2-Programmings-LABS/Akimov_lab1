#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <ctype.h>

int const MAX = 100;
int stack[MAX];
int tos = 0;


int prior(char str)
{
	switch (str)
	{
	case '!':
		return 4;
	case '*':
	case '/':
	case '&':
		return 3;
	case '-':
	case '+':
	case '|':
		return 2;
	case '(':
		return 1;
	}
}

void push(int i) {
	if (tos >= MAX) {
		printf("Стек полон\n"); return;
	}
	stack[tos] = i;
	tos++;
}

int pop() {
	tos--;
	if (tos < 0) {
		printf("Стек пуст\n"); return 0;
	}
	return stack[tos];
}


int main() {

	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");

	char str[100], element;

	while (fgets(str, 100, in) != NULL) {

		while (tos > 0) {
			pop();
		}

		for (int i = 0; i < strlen(str); i++) {

			if (str[i] >= '0' && str[i] <= '9') {
				fputc(str[i], out);
			}

			else if ((str[i] == 'A') || (str[i] == 'B') || (str[i] == 'C') || (str[i] == 'D')) {
				fputc(str[i], out);
			}

			else if (str[i] == '(') {
				push(str[i]);
			}

			else if (str[i] == ')') {
				while ((element = pop()) != '(') {
					fputc(element, out);
				}
			}

			else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
				while (tos > 0 && prior(stack[tos - 1]) >= prior(str[i])) {
					element = pop();
					fputc(element, out);
				}
				push(str[i]);
			}

			else if (str[i] == '&' || str[i] == '|' || str[i] == '!') {
				while (tos > 0 && prior(stack[tos - 1]) >= prior(str[i])) {
					element = pop();
					fputc(element, out);
				}
				push(str[i]);
			}
		}

		while (tos > 0) {
			element = pop();
			fputc(element, out);
		}
		fputc('\n', out);

	}
	printf("the result is written to a file");
	fclose(in);
	fclose(out);
}
