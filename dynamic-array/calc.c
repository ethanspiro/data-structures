/* CS261- Assignment 2 - calc.c*/
/* Name: Ethan Spiro
 * Date: 4/12/14
 * Solution description: Implementation of RPN calculator using dynamicArray.c
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.h"
#include "assert.h"
#include "math.h"

#define pi 3.14159
#define e 2.71828

/* General algorithm:
	(1) Check if the string s is in the list of operators.
	(1a) If it is, perform corresponding operations.
	(1b) Otherwise, check if s is a number.
	(1b - I) If s is not a number, produce an error.
	(1b - II) If s is a number, push it onto the stack
*/

/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	//pi case
	else if((strcmp(s, "pi") == 0) || (strcmp(s, "Pi") == 0) || (strcmp(s, "PI") == 0)) {
		*num = pi;
		return 1;
	}
	//e case
	else if(strcmp(s, "e") == 0) {
		*num = e;
		return 1;
	}
	else 
	{
		returnNum = strtod(s, &end);
		/* If there's anythin in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack)
{
	//declare necessary doubles for operator use on stack
	double operand_1, operand_2, add_result;

	//make sure the stack is not empty
	//assert(!isEmptyDynArr(stack));

	//store and pop first number off
	operand_1 = topDynArr(stack);
	popDynArr(stack);

	//make sure stack is not empty
	//assert(!isEmptyDynArr(stack));

	//store and pop second number off
	operand_2 = topDynArr(stack);
	popDynArr(stack);

	//store in result
	add_result = operand_2 + operand_1;

	//push back onto stack
	pushDynArr(stack, add_result);

}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
	//declare necessary doubles for operator use on stack
	double operand_1, operand_2, sub_result;

	//make sure the stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop first number off
	operand_1 = topDynArr(stack);
	popDynArr(stack);

	//make sure stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop second number off
	operand_2 = topDynArr(stack);
	popDynArr(stack);

	//store in result
	sub_result = operand_2 - operand_1;

	//push back onto stack
	pushDynArr(stack, sub_result);

}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
	//declare necessary doubles for operator use on stack
	double operand_1, operand_2, div_result;

	//make sure the stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop first number off
	operand_1 = topDynArr(stack);
	popDynArr(stack);

	//make sure stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop second number off
	operand_2 = topDynArr(stack);
	popDynArr(stack);

	//store in result
	div_result = operand_2 / operand_1;

	//push back onto stack
	pushDynArr(stack, div_result);

}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their product is pushed back onto the stack.
*/
void multiply(struct DynArr *stack)
{
	//declare necessary doubles for operator use on stack
	double operand_1, operand_2, mul_result;

	//make sure the stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop first number off
	operand_1 = topDynArr(stack);
	popDynArr(stack);

	//make sure stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop second number off
	operand_2 = topDynArr(stack);
	popDynArr(stack);

	//store in result
	mul_result = operand_2 * operand_1;

	//push back onto stack
	pushDynArr(stack, mul_result);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	the second is raised to the power of the first 
	and is pushed back onto the stack.
*/
void power(struct DynArr *stack)
{
	//declare necessary doubles for operator use on stack
	double operand_1, operand_2, pow_result;

	//make sure the stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop first number off
	operand_1 = topDynArr(stack);
	popDynArr(stack);

	//make sure stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop second number off
	operand_2 = topDynArr(stack);
	popDynArr(stack);

	//store in result
	pow_result = pow(operand_2, operand_1);

	//push back onto stack
	pushDynArr(stack, pow_result);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped, squared,
	and is pushed back onto the stack.
*/
void square(struct DynArr *stack)
{
	//declare necessary doubles for operator use on stack
	double operand_1, square_result;

	//make sure the stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop first number off
	operand_1 = topDynArr(stack);
	popDynArr(stack);

	//store in result
	square_result = operand_1 * operand_1;

	//push back onto stack
	pushDynArr(stack, square_result);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped, cubed,
	and is pushed back onto the stack.
*/
void cube(struct DynArr *stack)
{
	//declare necessary doubles for operator use on stack
	double operand_1, cube_result;

	//make sure the stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop first number off
	operand_1 = topDynArr(stack);
	popDynArr(stack);

	//store in result
	cube_result = operand_1 * operand_1 * operand_1;

	//push back onto stack
	pushDynArr(stack, cube_result);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped, 'absolute valued',
	and is pushed back onto the stack.
*/
void absoluteValue(struct DynArr *stack)
{
	//declare necessary doubles for operator use on stack
	double operand_1, abs_result;

	//make sure the stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop first number off
	operand_1 = topDynArr(stack);
	popDynArr(stack);

	//store in result
	abs_result = abs(operand_1);

	//push back onto stack
	pushDynArr(stack, abs_result);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped, sqrt'd,
	and is pushed back onto the stack.
*/
void squareRoot(struct DynArr *stack)
{
	//declare necessary doubles for operator use on stack
	double operand_1, sqrt_result;

	//make sure the stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop first number off
	operand_1 = topDynArr(stack);
	popDynArr(stack);

	//store in result
	sqrt_result = sqrt(operand_1);

	//push back onto stack
	pushDynArr(stack, sqrt_result);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped, exp'd,
	and is pushed back onto the stack.
*/
void exponential(struct DynArr *stack)
{
	//declare necessary doubles for operator use on stack
	double operand_1, exp_result;

	//make sure the stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop first number off
	operand_1 = topDynArr(stack);
	popDynArr(stack);

	//store in result
	exp_result = exp(operand_1);

	//push back onto stack
	pushDynArr(stack, exp_result);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped, ln'd,
	and is pushed back onto the stack.
*/
void naturalLog(struct DynArr *stack)
{
	//declare necessary doubles for operator use on stack
	double operand_1, ln_result;

	//make sure the stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop first number off
	operand_1 = topDynArr(stack);
	popDynArr(stack);

	//store in result
	ln_result = log(operand_1);

	//push back onto stack
	pushDynArr(stack, ln_result);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped, log10'd,
	and is pushed back onto the stack.
*/
void logTen(struct DynArr *stack)
{
	//declare necessary doubles for operator use on stack
	double operand_1, logTen_result;

	//make sure the stack is not empty
	assert(!isEmptyDynArr(stack));

	//store and pop first number off
	operand_1 = topDynArr(stack);
	popDynArr(stack);

	//store in result
	logTen_result = log10(operand_1);

	//push back onto stack
	pushDynArr(stack, logTen_result);
}


double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	struct DynArr *stack;

	//for keeping track of # of operands and operators
	int numOfOperands = 0;
	int numOfOperators = 0;
	int check = 0;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++) 
	{
		s = inputString[i];

		if(strcmp(s, "+") == 0) {
			numOfOperators++;		//increase for binary operators
			add(stack);
		}
		else if(strcmp(s,"-") == 0) {
			numOfOperators++;
			subtract(stack);
		}
		else if(strcmp(s, "/") == 0) {
			numOfOperators++;
			divide(stack);
		}
		else if(strcmp(s, "x") == 0) {
			numOfOperators++;
			multiply(stack);
		}
		else if(strcmp(s, "^") == 0) {
			numOfOperators = numOfOperators;	//for unary operators don't increase
			power(stack);
		}
		else if(strcmp(s, "^2") == 0) {
			numOfOperators = numOfOperators;
			square(stack);
		}
		else if(strcmp(s, "^3") == 0) {
			numOfOperators = numOfOperators;
			cube(stack);
		}
		else if(strcmp(s, "abs") == 0) {
			numOfOperators = numOfOperators;
			absoluteValue(stack);
		}
		else if(strcmp(s, "sqrt") == 0) {
			numOfOperators = numOfOperators;
			squareRoot(stack);
		}
		else if(strcmp(s, "exp") == 0) {
			numOfOperators = numOfOperators;
			exponential(stack);
		}
		else if(strcmp(s, "ln") == 0) {
			numOfOperators = numOfOperators;
			naturalLog(stack);
		}
		else if(strcmp(s, "log") == 0) {
			numOfOperators = numOfOperators;
			logTen(stack);
		}
		else 
		{
			//check if its a number (or pi or e)
			if(isNumber(s, &result)) {
				numOfOperands++;			//increase count of operands
				pushDynArr(stack, result); //if it is push onto stack
			}
			else {
			printf("You entered bad characters, exiting!\n"); //else print error message
			exit(0);
			}
			
		}
	}	//end for 

	//check for correct balance of operands and operators
	//must be one more operand than operators in sequence
	check = numOfOperands - numOfOperators; //this must be equal to 1 for valid input
	if (check > 1) {
		printf("Illegal Input, too many operands or too few operators, exiting\n");
		exit(0);
	}
	else if (check < 1) {
		printf("Illegal Input, too few operands or too many operators, exiting\n");
		exit(0);
	}

	//if passed check store final result and return
	result = topDynArr(stack);
	return result;
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

	//declare a double to store final answer of RPN calculation
	double finalResult = 0;

	//call calculate and store return result in finalResult
	finalResult = calculate(argc, argv);

	//print final result
	printf("Answer is:%f\n", finalResult);

	return 0;
}