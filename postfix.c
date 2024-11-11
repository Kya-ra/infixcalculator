#include "postfix.h"
#include "math.h"
#include "stack.h"
#include <stdio.h>

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {
  //Write your code here
  fprintf(stderr, "Postfix Entered with %i arguments\n", nargs);
  //create a double_stack from before
  struct double_stack * stack = double_stack_new(nargs);
  //traverse every element in the input
  for(int i = 0; i < nargs; i++) {
    double value;
    fprintf(stderr, "%s\n", args[i]);
    if(sscanf(args[i], "%lf", &value) > 0) {   //(args[i][0] >= '0'&& args [i][0] <= '9') || (args[i][0] == '-' && (args[i][1] != '-' args[i][1] != '\0'))){
      //if sscanf is true, this is a number
      double_stack_push(stack, value);
    }
    else{
      //otherwise, this is an operator
      double b = double_stack_pop(stack); //b is actually the second one you put on the stack
      double a = double_stack_pop(stack);
	  //now do the operation in question
      switch(args[i][0]){
        case '+':
          double_stack_push(stack, (a+b));
          break;
        case '-':
          double_stack_push(stack, (a-b));
          break;
        case 'X':
          double_stack_push(stack, (a*b));
          break;
        case '/':
          double_stack_push(stack, (a/b));
          break;
        case '^':
          double_stack_push(stack, pow(a, b));
          break;
        default:
          double_stack_push(stack,a);
      }
  }
  }
  double result = double_stack_pop(stack);
  free(stack);
  return result;
}

