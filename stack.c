#include <stdio.h>
#include <stdlib.h>
#include "GRAPH.h"

Stack* createStack(long size) {
   Stack* s = (Stack*) malloc(sizeof(Stack));
   s->size = size;
   s->top = -1;
   s->list = (int*) malloc(size*sizeof(int));
   return s;
}

int stackPeek(Stack* s) {
   return s->list[s->top];
}

int isStack(Stack* s, int data) {
   int t = s->top;
   while ((s->list[t] != data) && (t != -1)) {
      if (s->list[t] == data)
         return 1;
      t = t - 1;
   }
   return 0;
}

int stackEmpty(Stack* s) {
   if(s->top == -1)
      return 1;
   else
      return 0;
}
   
int stackFull(Stack* s) {
   if(s->top == s->size)
      return 1;
   else
      return 0;
}

int stackPop(Stack* s) {
   if(!stackEmpty(s)) {
      return s->list[s->top--];
   } 
   return -1;
}

void stackPush(Stack* s, int data) {
   if(!stackFull(s)) {
      s->top = s->top + 1;   
      s->list[s->top] = data;
   }
}