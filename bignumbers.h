#pragma once
#include "structures.h"

stack* create();
void read(stack **head, char c, char sign);
stack* copy(stack *head);
void deletef(stack **head);
void push_head(stack *head, char dig);
void push_tail(stack *head, char dig);
void delete_head(stack *head);
void delete_tail(stack *head);
