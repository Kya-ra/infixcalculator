#include "stack.h"
#include "stdio.h"

//create the stack, mallocing doubles for each element
struct double_stack * double_stack_new(int max_size) {
  struct double_stack * stack;
  stack = malloc(sizeof(struct double_stack));
  stack->top = 0;
  stack->max_size = max_size;
  stack->items = malloc(sizeof(double)*max_size);
  return stack;
}

// push a value onto the stack & increment top
void double_stack_push(struct double_stack * this, double value) {
  this->items[this->top] = value;
  this->top++;
}

// pop a value from the stack & decrement top
double double_stack_pop(struct double_stack * this) {
  double temp;
  this->top--;
  temp = this->items[this->top];
  return temp;
}

//create the stack, mallocing chars for each element
struct char_stack * char_stack_new(int max_size) {
  struct char_stack * stack;
  stack = malloc(sizeof(struct char_stack));
  stack->top = 0;
  stack->max_size = max_size;
  stack->items = malloc(sizeof(char)*max_size);
  return stack;
}

// push a value onto the stack
void char_stack_push(struct char_stack * this, char value) {
  fprintf(stderr, "Pushing %c\n", value);
  this->items[this->top] = value;
  this->top++;
}

// pop a value from the stack
char char_stack_pop(struct char_stack * this) {
  if(this->top == 0) { //if statement for debug purposes only
    fprintf(stderr, "Stack Empty: Returning Null \n");
    return '\0';
  }
  char temp;
  this->top--;
  temp = this->items[this->top];
  fprintf(stderr, "Popping %c\n", temp);
  return temp;
}
