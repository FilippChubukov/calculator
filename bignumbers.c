#include <stdio.h>
#include <stdlib.h>

#include "bignumbers.h"
#include "structures.h"

stack* create() {
 stack *tmp = malloc(sizeof(stack));
 tmp->number = NULL;
 tmp->tail = NULL;
 tmp->next = NULL;
 tmp->sign = 0;
 tmp->len = 0;
 return tmp;
}

void read(stack **head, char c, char sign) {// Считывание числа.
 stack *tmp = create();
 push_head(tmp, c - '0');
 while ((c = getchar())!= '\n') {
  push_head(tmp, c - '0');
 }
 tmp->sign = sign - '0';
 tmp->next = *head;
 *head = tmp;
}
 
stack* copy(stack *head) {
 stack *tmp = create();
 tmp->sign = head->sign;
 bnumber *num = head->number;
 while (num) {
  push_tail(tmp, num->value);
  num = num->next;
 }
 return tmp;
}

void deletef(stack **head) {// Удаление числа из стека.
 if (!(*head)) {
  printf("nothing to delete.\n");
  return;
 }
 while ((*head)->number) {
  delete_head(*head);
 }
 stack *op = (*head);
 *head = (*head)->next;
 free(op);
 op = NULL;
}

void push_head(stack *head, char ch) {
 bnumber *tmp = malloc(sizeof(bnumber));
 tmp->value = ch;
 tmp->prev = NULL;
 tmp->next = head->number;
 if (head->number) {
  head->number->prev = tmp;
 }
 else{
  head->tail = tmp;
 }
 head->number = tmp;
 head->len++;
}

void push_tail(stack *head, char ch){
 bnumber *tmp = malloc(sizeof(bnumber));
 tmp->value = ch;
 tmp->next = NULL;
 tmp->prev = head->tail;
 if (head->tail){
  head->tail->next = tmp;
 }
 else{
  head->number = tmp;
 }
 head->tail = tmp;
 head->len++;
}

void delete_head(stack *head){
 bnumber *tmp = head->number;
 head->number = head->number->next;
 if (head->number){
  head->number->prev = NULL;
 }

 else{
  head->tail = NULL;
 }
 free(tmp);
 tmp = NULL;
 head->len--;
}

void delete_tail(stack *head){
 bnumber *tmp = head->tail;
 head->tail = head->tail->prev;
 if (head->tail){
  head->tail->next = NULL;
 }
 else{
  head->number = NULL;
 }
 free(tmp);
 tmp = NULL;
 head->len--;
}












