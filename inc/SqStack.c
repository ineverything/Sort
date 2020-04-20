#include"qgsort.h"
#include"SqStack.h"
#include<stdio.h>
#include<stdlib.h>

//��ʼ��˳��ջ��stackΪ˳��ջ�ĵ�ָ��

void InitSeqStack(SeqStack* stack,int Size)
{
    if(stack == NULL)
    {
        //�Ƿ�����
        return;
    }
 
    stack->size = 0;//��ʼʱʵ�ʳ���Ϊ0                                                                                               
    stack->capacity = Size;
    stack->data = (SeqStackType*)malloc(sizeof(SeqStackType)*(stack->capacity));//Ϊ˳��ջ���붯̬�ڴ�
}

//β����ջ
void SeqStackPush(SeqStack* stack,SeqStackType value)
{
    if(stack == NULL)
    {
        //�Ƿ�����
        return;
    }
    if(stack->size > stack->capacity)
    {
        //��ʼ��˳��ջ����,��ʱ��Ҫ����
        stack->capacity = stack->capacity*2 + 1;
        //�������ݺ�Ķ�̬�ڴ�
        SeqStackType* new_data = (SeqStackType*)malloc(sizeof(SeqStackType)*(stack->capacity));
        //��ԭ�ڴ��е����ݿ��������ڴ���
        int i = 0;
        for(;i < stack->size;i++)
        {
            new_data[i] = stack->data[i];
        }
 
        //�ͷ�ԭ˳��ջ�е��ڴ�
        free(stack->data);
        //�����ݺ���ڴ汣����˳��ջ�Ľṹ��
        stack->data = new_data;
    }                                                                                                                                 
    //β����ջ
    stack->data[stack->size++] = value; 
    return;
}

//βɾ��ջ
void SeqStackPop(SeqStack* stack)
{
    if(stack == NULL)
    {
        //�Ƿ�����
        return;
    }
    if(stack->size == 0)
    {
        //��˳��ջ
        return;
    }
    //��βԪ������Ϊ��ЧԪ�ؼ���
    --stack->size;
}         
//ȡջ��Ԫ��,����ֵ��-1��������أ�0����ɹ�����
int SeqStackTop(SeqStack* stack,SeqStackType* value)
{
    if(stack == NULL || value == NULL) 
    {
        //�Ƿ�����
        return -1;
    }
 
    if(stack->size == 0)
    {
        //��˳��ջ
        return -1;
    }
 
    *value = stack->data[stack->size - 1];
    return 0;
}          

//����˳��ջ
void Destory(SeqStack* stack)
{
    stack->size = 0;
    stack->capacity = 0;
    free(stack->data);
    return;
}
