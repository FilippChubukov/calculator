#pragma once

typedef struct bnumber{
 char value;
 struct bnumber *next;
 struct bnumber *prev;
} bnumber;

typedef struct stack{
 char sign;
 long len;
 struct bnumber *number;
 struct bnumber *tail;
 struct stack *next;
} stack;
