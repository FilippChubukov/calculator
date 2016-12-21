#include <stdio.h>
#include <stdlib.h>
#include "bignumbers.h"
#include "arifmetika.h"
#include "structures.h"

int znak(stack *head) {//Определение знака для результата умножения/деления.
 if (head->sign  && head->next->sign ) {
   return 0;//result->sign = 0
 }
 if (!head->sign  && head->next->sign) {
  return 1;//result->sign = 1
 }
 if (head->sign && !head->next->sign) {
  return 1;//result->sign = 1
 }
 if (!head->sign && !head->next->sign) {
  return 0;//result->sign = 0
 }
}

int sravn(stack *head) {// Сравнение по модулю двух чисел.
 if (!head || !head->next) {
  printf("empty stack.\n");
  return -1;
 }
 if (head->len > head->next->len) {
  return 0; //a > b
 }
 if (head->len < head->next->len) {
  return 1; //a < b
 }
 bnumber *a = head->tail;
 bnumber *b = head->next->tail;
 while ((a->value == b->value) && a->prev) { //if len(a) = len(b)
  a = a->prev;
  b = b->prev;
 }
 if (a->value > b->value) {
  return 0;//a > b
 }
 if (a->value < b->value) {
  return 1;//a < b
 }
 return 2;//a = b 
 }

void sum(stack **head) {
 stack *result = create();
 result->sign = (*head)->next->sign;
 stack *first = (*head);
 stack *second = (*head)->next;
 char des = 0;// Десятки, которые перейдут в следующий разряд.
 while (first->number && second->number) { // Пока длина одного числа равна длине другого.
  push_tail(result, (( (first->number->value) + (second->number->value) + des ) % 10));
  des = ( (first->number->value) + (second->number->value) + des ) / 10;
  delete_head(first);
  delete_head(second);
 }
 while (first->number) {
  push_tail(result, (( (first->number->value) + des ) % 10));
  des = ( (first->number->value) + des ) / 10;
  delete_head(first);
 }
 while (second->number) {
  push_tail(result, (( (second->number->value) + des ) % 10));
  des = ( (second->number->value) + des ) / 10;
  delete_head(second);
 }
 if (des) {
  push_tail(result, des);
 }
 deletef(head);
 deletef(head);
 result->next = *head;
 *head = result;
}

void razn(stack **head) {
 if (sravn(*head) == 2){ // Числа равны => их разность равна нулю.
  deletef(head); 
  deletef(head); 
  stack *nul = create();
  push_head(nul, 0);
  nul->next = *head;
  *head = nul;
  return;
 }
 bnumber *min = NULL;
 bnumber *max = NULL;
 stack *result = create();
 if (sravn(*head)) { // Согласно тому какое из чисел больше определяем знак разности.
  min = (*head)->number;
  max = (*head)->next->number;
  result->sign = (*head)->next->sign;
 }
 else {
  min = (*head)->next->number;
  max = (*head)->number;
  if ( ((*head)->sign) != ((*head)->next->sign) ) {
   result->sign = (*head)->sign;
  }
  else {
   if((*head)->sign == 1) {
    result->sign = 0;
   }
   else {
    result->sign = 1;
   }
  }
 }
 char minus = 0;
 while (max && min) {  //Вычитание.
  minus = (max->value) - (min->value);
  if (minus < 0) {
   minus = minus + 10;
   max->next->value--;
  }
  push_tail(result, minus);
  max = max->next;
  min = min->next;
 }
 while (max) {
  while (max->value < 0) {
   max->value = max->value + 10;
   max->next->value--;
  }
  push_tail(result, max->value);
  max = max->next;
 }
 while (!result->tail->value && result->tail->prev) {
  delete_tail(result);
 }
 deletef(head);
 deletef(head); 
 result->next = *head;
 *head = result;
}

void proizv(stack **head) {
 if (!(*head) || !(*head)->next) {
  printf("empty stack.\n");
  return;
 }
 stack *result = create();
 result->sign = znak(*head);
 if (!(*head)->tail->value || !(*head)->next->tail->value) { // Если хотя бы одно из чисел рано нулю то произведение равно нулю.
  push_head(result, 0);
  result->sign = 0;
  deletef(head);
  deletef(head);
  result->next = *head;
  *head = result;
  return;
 }
 if (((*head)->tail->value == 1) && ((*head)->len == 1)) {// Если одно из чисел по модулю равно 1, то произведение равно второму числу(с учетом знаков).
  (*head)->next->sign = znak(*head);
  deletef(head);
  return;
 }
 if (((*head)->next->tail->value == 1) && ((*head)->next->len == 1)) {
  (*head)->sign = znak(*head);
  deletef(&(*head)->next);
  return;
 }
 bnumber *first = (*head)->number;
 bnumber *second = (*head)->next->number;
 long length = (*head)->len + (*head)->next->len;// len(a*b) <= len(a) + len(b)
 while (length--) {
  push_head(result, 0); 
 }
 char ed = 0;// Единицы при умножении поразрядно.
 char des = 0;// Десятки, переходящие в следующий разряд.
 bnumber *summ = result->number;
 bnumber *umnoj = result->number;
 while (first) {
  while (second) {
   ed = umnoj->value;
   umnoj->value = ( (first->value) * (second->value) + des + ed ) % 10;
   des = ( (first->value) * (second->value) + des + ed ) / 10;
   second = second->next;
   umnoj = umnoj->next;
  }
  while(des) {
   ed = umnoj->value;
   umnoj->value = (des + ed) % 10;
   des = (des + ed) / 10;
   umnoj = umnoj->next;
  }
  second = (*head)->next->number;
  summ = summ->next;
  umnoj = summ;
  first = first->next;
  delete_head(*head);
 }
 while (!result->tail->value && result->tail->prev) {
  delete_tail(result);
 }
 deletef(head);
 deletef(head);
 result->next = *head;
 *head = result;
 return;
}

void delenie(stack **head) {
 if (!(*head) || !(*head)->next) {
  printf("empty stack.\n");
  return;
 }
 if (!(*head)->tail->value) {// Запрет деления на ноль.
  printf("error.\n");
  return;
 }

 if (((*head)->tail->value == 1) && ((*head)->len == 1)) {//Если делитель равен 1, то частное равно делимому.
  (*head)->next->sign = znak(*head);
  deletef(head);
  return;
 }
 stack *result = create();
 result->sign = znak(*head);
 if (sravn(*head) == 2) {// При равенстве чисел частное равно 1(с учетом знаков)
  deletef(head);
  deletef(head);
  push_head(result, 1);
  result->next = (*head);
  (*head) = result;
  return;
 }
 if (!sravn(*head)) {// Если делить больше делимого то целочисленное деление дает 0.
  deletef(head);
  deletef(head);
  push_head(result, 0);
  result->next = *head;
  *head = result;
  return;
 }
 int del = 0;
 (*head)->sign = 0;
 (*head)->next->sign = 0;
 stack *first = copy(*head);
 stack *second = create();
 first->next = second;
 while ((*head)->next->tail) {
  do {
   if (second->tail && !second->tail->value) {
    delete_tail(second);
   }
   push_head(second, (*head)->next->tail->value);
   delete_tail((*head)->next);
   if (!sravn(first) && (*head)->next->tail) {
    push_head(result, 0);
   }
  } while (!sravn(first) && (*head)->next->tail);
  while (sravn(first)) {
   razn(&first);
   del++;
   second = first;
   first = copy(*head);
   first->next = second;
  }
  push_head(result, del);
  del = 0;
 }
 while (!result->tail->value && result->tail->prev) {
  delete_tail(result);
 }
 deletef(&first);
 deletef(&second);
 deletef(head);
 deletef(head);
 result->next = (*head);
 *head = result;
 return;
}






