#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef int SeqStackType;
//定义顺序栈的结构
typedef struct SeqStack
{
    int* data;//动态申请顺序栈的内存空间
    int size;//顺序栈的实际长度
    int capacity;//顺序栈的最大长度
}SeqStack;

void InitSeqStack(SeqStack* stack,int Size);
void SeqStackPush(SeqStack* stack,SeqStackType value);
void SeqStackPop(SeqStack* stack);
int SeqStackTop(SeqStack* stack,SeqStackType* value);
void Destory(SeqStack* stack);






#endif 
