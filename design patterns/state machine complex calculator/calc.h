/******************************************************************************/
/*    @File:       calc.h                                                     */
/*    @Created:    23.07.19                                                   */
/*    @Version:    1.0	                                                      */
/*    @Author:                                                                */
/******************************************************************************/

#ifndef __CALC_H__
#define __CALC_H__

typedef enum calc_status
{
	CALC_SUCCESS,
	CALC_FAIL
}calc_status_t;

/*TODO optional only*/
/*
typedef  int(*calc_parser_t)(state_t state, event_t event);
typedef int (*calc_compare_t)(char stack_op, char next_op);

typedef enum state
{
	CALC_WAIT_FOR_NUM,
	CALC_WAIT_FOR_OP,
    CALC_ERROR,
    CALC_EXIT
}state_t;

typedef enum event
{
    SPACE
    NUM,
	PLUS_MIN,
    MULTIPLY_DIVIDE,
    POWER,
    PARENTHESIS
}event_t;

struct calc
{
    stack_t *nums;
    stack_t *ops;
    state_t state;
    calc_parser_t parser;


}calc_t;

void*(handlers)(state_t state, event_t event);

return:
             1  - if stack_op > next_op
             0  - if stack_op = next_op
            -1  - if stack_op < next_op
             */

/*NOTE: Our calculator does not soppurt devision by 0 */
/******************************************************************************/

calc_status_t Calculate(char *polynom, double *res);
#endif /* __CALC_H__*/
