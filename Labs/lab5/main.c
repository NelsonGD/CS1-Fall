/* Nelson Diaz
COP3502C - Sep 30th, 2024
Lab 5 - Parenthesis Checker and infix-Postfix */

#include <stdio.h>
#include <string.h> // For strlen
#include <ctype.h>  // For isdigit, isalpha

// The array will store the items in the stack, first in
// index 0, then 1, etc. top will represent the index
// to the top element in the stack. If the stack is
// empty top will be -1.
#define SIZE 100
#define EMPTY -1

struct stack
{
    char items[SIZE];
    int top;
};

void initialize(struct stack *stackPtr);
int full(struct stack *stackPtr);
int push(struct stack *stackPtr, char value);
int empty(struct stack *stackPtr);
char pop(struct stack *stackPtr);
char peek(struct stack *stackPtr);
void display(struct stack *stackPtr);

// Function to check if the equation is valid or invalid
int checkBalance(char exp[]);
// Function to determine operator precedence
int priority(char ch);
// Function to check if a character is an operator
int isOperator(char ch);
// Function that converts infix to postfix
char *infixToPostfix(char infix[]);

int main()
{
    // Reading the input expression
    char expression[SIZE];
    printf("Enter expression: ");
    fgets(expression, SIZE, stdin);

    size_t len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n')
    {
        expression[len - 1] = '\0';
    }

    // Print the input expression
    printf("Your input expression: %s\n", expression);

    // Print message that balance is being checked
    printf("Checking balance...\n");

    // Check if the balance is correct
    if (checkBalance(expression))
    {
        printf("VALID\n");
        char *postfix = infixToPostfix(expression);
        printf("The postfix is: %s\n", postfix);
    }
    // Else case: Do nothing, as checkBalance function already prints the invalid message

    return 0;
}

char *infixToPostfix(char infix[])
{
    struct stack stack;
    initialize(&stack);

    static char postfix[SIZE]; // Output array for postfix expression
    int j = 0;                 // Index for postfix array

    int i = 0;
    int len = strlen(infix);
    while (i < len)
    {
        char current = infix[i];

        // If the current character is a digit, collect all consecutive digits (multi-digit numbers)
        if (isdigit(current))
        {
            // Add space if needed
            if (j > 0 && postfix[j - 1] != ' ')
                postfix[j++] = ' ';

            // Collect all consecutive digits
            while (i < len && isdigit(infix[i]))
            {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' '; // Add space after the number
            continue;
        }
        // If the current character is a letter (variable), add it to postfix output
        else if (isalpha(current))
        {
            // Add space if needed
            if (j > 0 && postfix[j - 1] != ' ')
                postfix[j++] = ' ';

            postfix[j++] = current;
            postfix[j++] = ' ';
        }
        // If it's an opening parenthesis, push it onto the stack
        else if (current == '(')
        {
            push(&stack, current);
        }
        // If it's a closing parenthesis, pop from the stack to output until '(' is found
        else if (current == ')')
        {
            while (!empty(&stack) && peek(&stack) != '(')
            {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            if (!empty(&stack) && peek(&stack) == '(')
                pop(&stack); // Pop the opening parenthesis '('
            else
            {
                // Mismatched parenthesis (should not happen if checkBalance passed)
            }
        }
        // If the character is an operator
        else if (isOperator(current))
        {
            // Add space if needed
            if (j > 0 && postfix[j - 1] != ' ')
                postfix[j++] = ' ';

            // Pop operators from the stack to the output based on precedence
            while (!empty(&stack) && priority(peek(&stack)) >= priority(current))
            {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            push(&stack, current); // Push the current operator onto the stack
        }
        // Skip spaces
        else if (current == ' ')
        {
            // Do nothing
        }
        // Other characters, ignore?
        i++; // Move to next character
    }

    // Pop any remaining operators in the stack to the output
    while (!empty(&stack))
    {
        postfix[j++] = pop(&stack);
        postfix[j++] = ' ';
    }

    if (j > 0 && postfix[j - 1] == ' ')
        j--; // Remove trailing space

    postfix[j] = '\0'; // Null terminate the postfix expression

    return postfix; // Return the resulting postfix expression
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to determine operator precedence
int priority(char ch)
{
    switch (ch)
    {
    // Check according to order of precedence
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0; // Non-operator characters
    }
}

// Modify checkBalance to handle specific unmatched parentheses
int checkBalance(char exp[])
{
    // Declare and initialize stack
    struct stack stack;
    initialize(&stack);

    // Iterate through the expression
    for (int i = 0; i < strlen(exp); i++)
    {
        char current = exp[i];

        // Push opening parentheses onto the stack
        if (current == '(' || current == '{' || current == '[')
        {
            push(&stack, current);
        }

        // Pop and check for matching parentheses
        else if (current == ')' || current == '}' || current == ']')
        {
            if (empty(&stack))
            {
                printf("INVALID for %c!!!\n", current); // Unmatched closing parenthesis
                return 0;
            }
            char top = pop(&stack);
            if ((current == ')' && top != '(') || (current == '}' && top != '{') || (current == ']' && top != '['))
            {
                printf("INVALID for %c!!!\n", current); // Mismatched parentheses
                return 0;
            }
        }
    }

    // If the stack is not empty, there is an unmatched opening parenthesis
    if (!empty(&stack))
    {
        printf("INVALID for unmatched opening parenthesis!!!\n");
        return 0;
    }

    return 1; // Parentheses are balanced
}

void initialize(struct stack *stackPtr)
{
    stackPtr->top = -1;
}

// Push function
int push(struct stack *stackPtr, char value)
{
    if (full(stackPtr))
    {
        printf("Stack overflow!\n");
        return 0;
    }
    stackPtr->items[++stackPtr->top] = value;
    return 1;
}

// Check if stack is full
int full(struct stack *stackPtr)
{
    return (stackPtr->top == SIZE - 1);
}

// Check if stack is empty
int empty(struct stack *stackPtr)
{
    return (stackPtr->top == -1);
}

// Pop function
char pop(struct stack *stackPtr)
{
    if (empty(stackPtr))
    {
        printf("Stack underflow!\n");
        return '\0'; // Return null character for underflow
    }
    return stackPtr->items[stackPtr->top--];
}

// Peek function
char peek(struct stack *stackPtr)
{
    if (empty(stackPtr))
        return '\0'; // Return null character for an empty stack
    return stackPtr->items[stackPtr->top];
}

void display(struct stack *stackPtr)
{
    printf("\nPrinting the current stack...");
    for (int i = 0; i <= stackPtr->top; i++)
        printf("%c ", stackPtr->items[i]);
}
