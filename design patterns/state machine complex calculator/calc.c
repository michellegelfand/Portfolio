/**********************************************************************;
* Project           : Data Structures
*
* Program name      : calc.c
*
* Author            : Michelle Gelfand
*
* Date created      : 23.07.19
*
* Purpose           : This program provides the user
					  with a state machine based calculator
*
* Version           : 1.0
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 24/07/2019       	  Michelle Gelfand           Olga K. *														  
*******************************************************************/
#include <stdlib.h>/*malloc, strtod*/
#include <string.h>/*strlen*/

#include "stack.h"
#include "calc.h"

#define NUM_OPS_LUT 4
#define NUM_OF_STATES 4

#define NEW_OP_MORE_IMPORTANT 1

double plus_func(double num1, double num2);

typedef enum event
{
	PLUS,
	MINUS,
    MULTIPLY,
	DIVIDE,
    SPACE,
    NUM,
    POWER,
    PARENTHESIS
}event_t;

typedef enum state
{
	CALC_WAIT_FOR_NUM,
	CALC_WAIT_FOR_OP,
    CALC_ERROR,
    CALC_EXIT
}state_t;


typedef state_t (*event_handler_t)(char **event, stack_t *nums, stack_t *ops, double *res);

/*returns next state num*/
typedef state_t (*calc_parser_t)(char **character, state_t state, stack_t *nums, stack_t *ops, double *res);

typedef struct calc
{
    stack_t *nums_stack;
    stack_t *ops_stack;
    state_t state;
    calc_parser_t parser;
}calc_t;

typedef enum associo
{
	LEFT_TO_RIGHT = 0,
	RIGHT_TO_LEFT = 1
}associo_t; 

typedef double (*op_func_t)(double num1, double num2); 

typedef struct operator
{
	int precedence;
	associo_t associo;
	op_func_t op_func;

}operator_t;


typedef int (*calc_compare_t)(char stack_top_op, char new_op);

/******************************************************************************* */

static operator_t* _InitOps(op_func_t func, int precedence, associo_t associo)
{
	operator_t *op = (operator_t*)malloc(sizeof(operator_t));
	
	if(op)
	{
		op->precedence = precedence;
		op->associo = associo;
		op->op_func = func;
	}

	return op;
}

operator_t *ops[NUM_OPS_LUT] = {0};



static operator_t *_CharToStructPointer(char op)
{
	event_t event = 0;

	switch (op)
	{
	case '+':
		event = PLUS;
		break;
	case '-':
		event = MINUS;
		break;
	
	case '*':
		event = MULTIPLY;
		break;
	case '/':
		event = DIVIDE;
		break;
	}


	return ops[event];
}

int Compare(char stack_top_op, char new_op)
{
	int stack_op_prec = _CharToStructPointer((char)stack_top_op)->precedence;
	int new_op_prec   = _CharToStructPointer((char)new_op)->precedence;
	
	return (!!stack_op_prec < new_op_prec );
}

/***************** H  A  N  D  L  E  R  S ***********************************/

state_t WaitingNum_Op(char **event, stack_t *nums, stack_t *ops, double *res)
{
	(void)res;
	(void)event;
	(void)nums;
	(void)ops;
	return CALC_ERROR; 
}

state_t WaitingOp_Num(char **event, stack_t *nums, stack_t *ops ,double *res)
{
	(void)res;
	(void)event;
	(void)nums;
	(void)ops;
	return CALC_ERROR; 
}

state_t WaitingNum_Num(char **num, stack_t *nums, stack_t *ops, double *res)
{	
	double num_to_push = strtod(*num, num);
	StackPush(nums, (void*)&num_to_push);
	(void)ops;
	(void)res;

	return CALC_WAIT_FOR_OP;
}

/******************************************************************************* */

state_t WaitingOp_Op(char **event, stack_t *nums, stack_t *ops, double *res)
{
	double num_stack_top = 0;
	double num_stack_next_top = 0;	
	double prev_op_result = 0;
	operator_t *op_stack_top = StackPeek(ops);
	if(num_stack_top)
	{
		int precedence = Compare(*(char*)op_stack_top, **event);

		if( NEW_OP_MORE_IMPORTANT == precedence )
		{	
			StackPush(ops ,event);
		}
		else 
		{							
			num_stack_top = *(double*)StackPeek(nums);
			StackPop(nums); 
			num_stack_next_top = *(double*)StackPeek(nums);
			StackPop(nums); 

			op_stack_top = _CharToStructPointer(*(int*)StackPeek(ops));

			StackPop(ops);

			prev_op_result = (double)op_stack_top->op_func(num_stack_top, num_stack_next_top);
			
			StackPush(nums, (void*)&prev_op_result);
			StackPush(ops, event); 
		}
	}
	else
	{
		StackPush(ops, *event); 
	}
	
	++*event;

	(void)res;
	return CALC_WAIT_FOR_NUM;
}


state_t EOS(char **event, stack_t *nums, stack_t *ops, double *res)
{
	double num_stack_top = 0;
	double num_stack_next_top = 0;	
	double prev_op_result = 0;
	operator_t *op_stack_top = StackPeek(ops);
	
	while( 1 != StackSize(nums))
	{							
		num_stack_top = *(double*)StackPeek(nums);
		StackPop(nums); 
		num_stack_next_top = *(double*)StackPeek(nums);
		StackPop(nums); 

		op_stack_top = _CharToStructPointer(*(int*)StackPeek(ops));

		StackPop(ops);

		prev_op_result = (double)op_stack_top->op_func(num_stack_top, num_stack_next_top);
		
		StackPush(nums, (void*)&prev_op_result);
	}	
	*res = *(double*)StackPeek(nums);
	(void)event;

	return CALC_EXIT;
}

event_handler_t event_handler_matrix[256][NUM_OF_STATES];

/***************** P  A  R  S  E  R ***************************************/

static state_t Parser (char **character, state_t state,
								stack_t *ops, stack_t *nums, double *res)
{
	event_handler_t handler = event_handler_matrix[(int)**character][state];
	state = handler(character, nums, ops, res);

	return state;
}

/**************************** c  r  e  a  t  e *******************************/
static calc_t* _CalcCreate(size_t stack_size)
{
	calc_t *calc = NULL;
	stack_t *nums = StackCreate(sizeof(double), stack_size);

	if (nums)
	{
		stack_t *ops = StackCreate(sizeof(char), stack_size);
		if(ops)
		{
			calc = (calc_t*)malloc(sizeof(calc_t)); 
			
			if(calc)
			{
				calc->nums_stack = nums; 
				calc->ops_stack = ops;
				calc->state =  CALC_WAIT_FOR_NUM; 
				calc->parser = Parser;
			}
			else
			{
				free(nums);
				free(ops);
			}
		}
		else
		{
			free(nums);
		}
	}

	return calc;
}
static void _CalcDestroy(calc_t *calc)
{
	free(calc->nums_stack);
	free(calc->ops_stack);
	calc->nums_stack = NULL;
	calc->ops_stack = NULL;
	
	free(calc);
	calc = NULL;
}
/************************** o  p  s *******************************************/

double plus_func(double num1, double num2)
{
	return (num1 + num2);
}

double minus_func(double num1, double num2)
{
	return (num2 - num1);
}

double Mult_func(double num1, double num2)
{
	return (num1 * num2);
}

double div_func(double num1, double num2)
{
	return (num1 / num2);
}

/*****************************************************************************/
calc_status_t Calculate(char *polynom, double *res)
{
	calc_status_t calc_status = CALC_FAIL;
	calc_t *calc = _CalcCreate(strlen(polynom));
	int i = '0';
	operator_t *plus_op = _InitOps(plus_func, 1, LEFT_TO_RIGHT);
	operator_t *minus_op = _InitOps(minus_func, 1, LEFT_TO_RIGHT);
	operator_t *mult_op = _InitOps(Mult_func, 2, LEFT_TO_RIGHT);
	operator_t *div_op = _InitOps(div_func, 2, LEFT_TO_RIGHT);

	ops[PLUS] = plus_op;
	ops[MINUS] = minus_op;
	ops[MULTIPLY] = mult_op;
	ops[DIVIDE] = div_op;

	for(i = '0'; i <= '9'; ++i)
	{
		event_handler_matrix [i][CALC_WAIT_FOR_NUM] = WaitingNum_Num;
		event_handler_matrix [i][CALC_WAIT_FOR_OP] = WaitingOp_Num;
	}

	event_handler_matrix['+'][CALC_WAIT_FOR_NUM] = WaitingNum_Op;
	event_handler_matrix['+'][CALC_WAIT_FOR_OP]  = WaitingOp_Op;

	event_handler_matrix['-'][CALC_WAIT_FOR_NUM] = WaitingNum_Op;
	event_handler_matrix['-'][CALC_WAIT_FOR_OP]  = WaitingOp_Op;

	event_handler_matrix['\0'][CALC_WAIT_FOR_NUM] = EOS;
	event_handler_matrix['\0'][CALC_WAIT_FOR_OP]  = EOS;


	if(calc)
	{
		calc_status = CALC_SUCCESS;

		/*inited to WAIT_FOR_NUM*/
		while ( CALC_EXIT != calc->state && CALC_ERROR != calc->state)
		{
			calc->state = Parser(&polynom, calc->state, calc->ops_stack, calc->nums_stack, res);
			/* ++polynom;*/
		}

		_CalcDestroy(calc);
	}
		
	return calc_status;
}




