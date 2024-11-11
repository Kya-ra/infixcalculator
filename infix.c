#include "infix.h"
#include "postfix.h"
#include "stack.h"
#include <string.h>
#include <stdio.h>

#define MAX_TOKENS 128
#define MAX_TOKEN_SIZE 16

//implement BIDMAS in a function
int establish_precedence(char operator) {
  switch(operator) {
    case '+':
    case '-':
      return 1;
    case 'X':
    case '/':
      return 2;
    case '^':
      return 3;
    default:
      return 0;
  }
}

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** args, int nargs) {
  // Write your code here
  //rpn_output stores the output in the format required for postfix, rpn_nargs stores the number of arguments for postfix
  char* rpn_output[MAX_TOKENS];
  struct char_stack * cstack = char_stack_new(nargs);
  int rpn_nargs = nargs;
  int token_count = 0;
  fprintf(stderr, "Nargs: %i\n", nargs);
  //traverse every element in the input
  for(int i = 0; i < nargs; i++) {
    double value;
    fprintf(stderr, "INPUT: %s\n", args[i]);
	//check if the input element is convertible to a float, using the true/false output of sscanf
    if(sscanf(args[i], "%lf", &value) == 1) {
	//malloc a char for the number, possibly multiple if its not a single digit or is negative
	rpn_output[token_count] = (char*)malloc(sizeof(char) * strlen(args[i]));
	strcpy(rpn_output[token_count], args[i]);
	token_count++;
    }
	//handle the bracket case: skip closing bracket
    else if(args[i][0] != ')') {
		//handle the bracket case: immediately push open bracket
      if(args[i][0] == '(') {
        char_stack_push(cstack, '(');
      }
	  else {
		  //pop the top of the stack so it can be compared for precedence
      char top_of_stack = char_stack_pop(cstack);
      fprintf(stderr, "%c\n", top_of_stack);
	  //if its null the stack is empty and this code is useless
      if (top_of_stack != '\0') {
        fprintf(stderr, "Args: %i, Top: %i\n", establish_precedence(args[i][0]), establish_precedence(top_of_stack));
        while (establish_precedence(args[i][0]) < establish_precedence(top_of_stack)) {
			//while the top of the stack is more important (e.g. bracket or index) then write it to the token array, otherwise push it to the stack
	        fprintf(stderr, "%c is higher precedence than %c\n", top_of_stack, args[i][0]);
	        rpn_output[token_count] = (char*)malloc(sizeof(char));
	        rpn_output[token_count][0] = top_of_stack;
	        token_count++;
          top_of_stack = char_stack_pop(cstack);
        }
        char_stack_push(cstack, top_of_stack);
      }
	  //push the operator to the stack
      char_stack_push(cstack, args[i][0]);
	}
    }
	//if its a close bracket, pop everything until you find the open bracket, mallocing for operators throughout
    else if(args[i][0] == ')') {
      char top_of_stack = char_stack_pop(cstack);
      while (top_of_stack != '(') {
	rpn_output[token_count] = (char*)malloc(sizeof(char));
	rpn_output[token_count][0] = top_of_stack;
	      token_count++;
        top_of_stack = char_stack_pop(cstack);
      }
      //we do not need the bracket thanks to RPN
      rpn_nargs -= 2;
	  fprintf(stderr, "Brackets Removed from Count Successfully, Nargs: %i\n", rpn_nargs);
    }
  }

  fprintf(stderr, "END FOR LOOP \n");
  char top_of_stack = char_stack_pop(cstack);
  //empty out the stack after the input has handled
  while (top_of_stack != '\0') {
    if (top_of_stack == '(') {
      top_of_stack = char_stack_pop(cstack);
    }
    fprintf(stderr, "Top of Stack: %c\n", top_of_stack);
    rpn_output[token_count] = (char*)malloc(sizeof(char));
    rpn_output[token_count][0] = top_of_stack;
    token_count++;
    top_of_stack = char_stack_pop(cstack);
  }
  fprintf(stderr, "END WHILE LOOP\n");
  //call postfix
  double result = evaluate_postfix_expression((char **)rpn_output, rpn_nargs);
  //theres no free because rpn_output is already getting freed somehow
  return result;
}
