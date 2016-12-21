#include <stdio.h>
#include <stdlib.h>
#include "bignumbers.h"
#include "arifmetika.h"
#include "structures.h"

int main() {
 stack *sthead = NULL;
 for(;;) {
  char c = getchar();
  switch (c) {

   case '+':
    if (sthead && sthead->next) {
     if (sthead->sign == sthead->next->sign) {
      sum(&sthead); // Оба числа одного знака => мы их складываем.
     } 
     else {
      razn(&sthead); // Числа разных знаков => из одного вычитаем другое. 
     }
    }
    else {
     printf("empty stack.\n");
    }
    break;

   case '*':
    proizv(&sthead);
   break;

   case '/':
    delenie(&sthead);
   break;

   case '-':
    if ((c = getchar()) != '\n') {// Если за '-' следуют еще символы, то считываем отрицательное число.
     read(&sthead, c, '1');
     break;
    }
    if (sthead && sthead->next) {
     if (sthead->sign != sthead->next->sign) {
      sum(&sthead); // Числа разных знаков => либо это сумма положительных либо разность отрицательных(также сумма).
     } 
     else {
      razn(&sthead);// Числа одного знака => это разность либо первого и второго, либо второго и первого.
     }
    }
    else {
     printf("empty stack.\n");
    }
    break;
   
   case '=':
    printf("real-time result:\n");
     if(sthead && sthead->tail) {
      bnumber *tmp = sthead->tail;
      if (sthead->sign) {
      printf("%c", '-');
     }
     while (tmp) {
      printf("%d", tmp->value);
      tmp = tmp->prev;
     }
     printf("\n");
    }
    else {
     printf("empty stack.\n");
    }

    break;

   default: 
    if (c != '\n') {
     read(&sthead, c, '0');
     break;
    }

  }
 }
}
