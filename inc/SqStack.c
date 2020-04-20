#include"qgsort.h"
#include"SqStack.h"
#include<stdio.h>
#include<stdlib.h>

//初始化顺序栈，stack为顺序栈的的指针

void InitSeqStack(SeqStack* stack,int Size)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
 
    stack->size = 0;//初始时实际长度为0                                                                                               
    stack->capacity = Size;
    stack->data = (SeqStackType*)malloc(sizeof(SeqStackType)*(stack->capacity));//为顺序栈申请动态内存
}

//尾插入栈
void SeqStackPush(SeqStack* stack,SeqStackType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size > stack->capacity)
    {
        //初始的顺序栈已满,此时需要扩容
        stack->capacity = stack->capacity*2 + 1;
        //申请扩容后的动态内存
        SeqStackType* new_data = (SeqStackType*)malloc(sizeof(SeqStackType)*(stack->capacity));
        //将原内存中的内容拷贝到新内存中
        int i = 0;
        for(;i < stack->size;i++)
        {
            new_data[i] = stack->data[i];
        }
 
        //释放原顺序栈中的内存
        free(stack->data);
        //将扩容后的内存保存在顺序栈的结构中
        stack->data = new_data;
    }                                                                                                                                 
    //尾插入栈
    stack->data[stack->size++] = value; 
    return;
}

//尾删出栈
void SeqStackPop(SeqStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size == 0)
    {
        //空顺序栈
        return;
    }
    //将尾元素设置为无效元素即可
    --stack->size;
}         
//取栈顶元素,返回值：-1代表出错返回，0代表成功返回
int SeqStackTop(SeqStack* stack,SeqStackType* value)
{
    if(stack == NULL || value == NULL) 
    {
        //非法输入
        return -1;
    }
 
    if(stack->size == 0)
    {
        //空顺序栈
        return -1;
    }
 
    *value = stack->data[stack->size - 1];
    return 0;
}          

//销毁顺序栈
void Destory(SeqStack* stack)
{
    stack->size = 0;
    stack->capacity = 0;
    free(stack->data);
    return;
}
