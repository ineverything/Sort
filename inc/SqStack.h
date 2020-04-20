#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef int SeqStackType;
//����˳��ջ�Ľṹ
typedef struct SeqStack
{
    int* data;//��̬����˳��ջ���ڴ�ռ�
    int size;//˳��ջ��ʵ�ʳ���
    int capacity;//˳��ջ����󳤶�
}SeqStack;

void InitSeqStack(SeqStack* stack,int Size);
void SeqStackPush(SeqStack* stack,SeqStackType value);
void SeqStackPop(SeqStack* stack);
int SeqStackTop(SeqStack* stack,SeqStackType* value);
void Destory(SeqStack* stack);






#endif 
