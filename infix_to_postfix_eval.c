#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<stdbool.h>

#define MAX_SIZE 100

int stack[MAX_SIZE];

int top;


void Stack_Init(void);
int isEmpty(void);
int isFull(void);
int size(void);
int peek(void);
void push(int item);
int pop(void);
void display(void);
int precedence(char ch);
int operation(char operator, int op1, int op2);
bool isOpeartor(char ch);



int main() {	
	
	char exp[MAX_SIZE];
	char post_fix[MAX_SIZE];

	Stack_Init();

	printf("Enter an expression: ");

	fgets(exp, MAX_SIZE, stdin);
	
	int popped_item;

	size_t k = 0;

	for (int i = 0; exp[i] != '\n'; i++) {
		
		if (exp[i] == ' ' || exp[i] == '\t') {
			continue;
		}

		switch (exp[i]) {
			
			case '(': 
				push(exp[i]);
				break;
			
			case ')': {
				
				while (((popped_item = pop()) != -1) && (popped_item != '(')) {
					post_fix[k++] = popped_item;
				}

				if (popped_item == -1) {
					printf("Invalid Expression...\n");
					exit(1);
				}

				break;
			}

			case '^':
			case '*':
			case '/':
			case '%':
			case '+':
			case '-':
				while (peek() != -1 && (precedence(peek()) <= precedence(exp[i]))) {
					post_fix[k++] = pop();
				}
				push(exp[i]);
				break;
			default:
				post_fix[k++] = exp[i];	
		}


	}

	while ((popped_item = pop()) != -1) {
		if (popped_item == '(') {
			printf("Invalid Expression...\n");
			exit(1);
		}
		post_fix[k++] = popped_item; 
	}

	popped_item = '\0';
		
	printf("Postfix = %s\n", post_fix);

	Stack_Init();

	for (int i = 0; post_fix[i] != '\0'; i++) {
	
		if (isOpeartor(post_fix[i])) {

			if (size() < 2) {
				printf("IInvalid postfix expression...\n");
				exit(1);
			}
			
			int op2 = pop();
			int op1 = pop();

			push(operation(post_fix[i], op1, op2));
		} else {
			push(post_fix[i] - '0');
		}

	}

	int result = pop();

	if (result == -1) {
		printf("Invalid postfix expression...\n");
		exit(1);
	}

	
	printf("Value = %d\n", result);

	return 0;
}





bool isOpeartor(char ch)
{
	switch (ch) {
		case '^':
		case '*':
		case '/':
		case '%':
		case '+':
		case '-':
			return true;
		default:
			return false;
	}
}



int precedence(char ch)
{
	switch (ch) {
		case '^': 
			return 1;
		case '*': 
		case '/': 
		case '%': 
			return 2;
		case '+': 
		case '-': 
			return 3;
		case '(':
			return 4;
		default:
			return 5;

	}
}


int operation(char operator, int op1, int op2)
	
{
	switch (operator) {
		case '^':
			return pow(op1, op2);
		case '*':
			return op1 * op2;
		case '/':
			return op1 / op2;
		case '%':
			return op1 % op2;
		case '+':
			return op1 + op2;
		case '-':
			return op1 - op2;
		default:
			printf("Invalid postfix expression...");
			exit(1);
	}

}




void Stack_Init(void)
{
	top = -1;
}





int isEmpty(void)
{
	return top == -1;
}




int isFull(void)
{
	return (top == MAX_SIZE - 1);
}




int size(void)
{
	return top + 1;
}




int peek(void)
{
	if (isEmpty()) {
		printf("Empty Stack\n");
		return -1;
	} else{
		return stack[top];
	}

}




void push(int item)
{
	if (isFull()) {
		printf("Stack is Full\n");
		return;
	} 

	stack[++top] = item;

}




int pop(void)
{
	if (isEmpty()) {
		printf("Stack is Empty\n");
		return -1;
	} 
	
	return stack[top--];

}




void display(void)
{
	if (isEmpty()) {
		printf("Stack is Empty\n");
		return;
	} 


	for (int i = 0; i <= top; i++) {
		printf("%d --> ", stack[i]);
	}

	printf("\n");

}






