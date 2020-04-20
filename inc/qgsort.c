#include"qgsort.h"
#include"SqStack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>

/**
 *  @name        : void insertSort(int *a,int n);
 *  @description : 插入排序,用一个临时变量存储当前值。前面的元素比后面大时，先把后面的元素存入临时变量，前
 					面元素的值放到后面元素位置，再到最后把其值插入到合适的数组位置。
 *  @param       : 数组指针 a, 数组长度 n
 */
void insertSort(int *a,int n)
{
	int i, j, temp, m, low, high;
    for (i = 1; i < n; i++){
        temp = a[i];
        low = 0;
		high = i-1;
        while (low <= high){
            m = (low +high) / 2;
            if(a[m] > temp)
                high = m-1;
            else
                low = m+1;
        }
        for (j = i-1; j>=high+1; j--)
            a[j+1] = a[j];
       }
    a[j+1] = temp;        	
}

/**
 *  @name        : void MergeArray(int *a,int begin,int mid,int end,int *temp);
 *  @description : 归并排序（合并数组） 
 *  @param       : 数组指针a，数组起点begin，数组中点mid，数组终点end，承载数组指针temp
 */
void MergeArray(int *a,int begin,int mid,int end,int *temp)
{
	int i = begin,j = mid + 1;
    int m = mid,n = end;
    int k = 0;
 
    //开始合并两个数组；
    while(i <= m && j <= n){
        if(a[i] <= a[j]){
            temp[k++] = a[i++];
        }else{
            temp[k++] = a[j++];
        }
    }
 
    while(i <= m){
        temp[k++] = a[i++];
    }
 
    while(j <= n){
        temp[k++] = a[j++];
    }
 
    //把temp数组中的结果装回a数组
    for(i = 0;i < k;i++){
        a[begin + i] = temp[i];
    }
}

/**
 *  @name        : void MergeSort(int *a,int begin,int end,int *temp);
 *  @description : 归并排序
 *  @param       : 数组指针a，数组起点begin，数组终点end，承载数组指针temp
 */
void MergeSort(int *a,int begin,int end,int *temp)
{
	if(begin < end){
    	int mid = (begin + end) / 2;
        //  分别递归进行排序，也称为2-路归并；
        MergeSort(a,begin,mid,temp);   //左边有序
        MergeSort(a,mid + 1,end,temp);   //右边有序
        MergeArray(a,begin,mid,end,temp); //将左右两边有序的数组合并
    }
}


/**
 *  @name        : void QuickSort(int *a, int begin, int end);
 *  @description : 快速排序（递归版）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
void QuickSort_Recursion(int *a, int begin, int end)
{
	int pivot;
    if (begin<end){
        pivot = Partition(a, begin, end);
        QuickSort_Recursion(a, begin, pivot-1);    //对低子表进行递归排序
        QuickSort_Recursion(a, pivot + 1, end);    //对高子表进行递归排序
    }
}

/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : 快速排序（非递归版）
 递归的算法主要是在划分子区间，如果要非递归实现快排，只要使用一个栈来保存区间就可以了。
一般将递归程序改成非递归首先想到的就是使用栈，因为递归本身就是一个压栈的过程。
 *  @param       : 数组指针a，数组长度size
 */
void QuickSort(int *a,int size)
{
	if(a == NULL || size <= 1)                                                                           
        return;
    SeqStack stack;//定义栈
    InitSeqStack(&stack,size);//初始化栈
    //入栈整个待排序序列的首位坐标
    SeqStackPush(&stack,0);
 
    int left;
    int right;
    while(1)
    {
        //取栈顶元素作为带排序序列的尾坐标
        int ret = SeqStackTop(&stack,&right);
        if(ret == -1)//栈定为空，带排序序列处理完
        {
            return;
        }
        //出栈后再取栈顶元素
        SeqStackPop(&stack);
        //此时的栈定元素必为带排序序列的首坐标
        SeqStackTop(&stack,&left);
        //出栈栈顶元素
        SeqStackPop(&stack);
        //如果带排序序列元素个数小于等于1，则该序列必然已经排好序
        //且不能在分为更小的序列，也就不需要再进行排序再进行入栈了
        if(right - left <= 1)
        {
            continue;
        }
        //对带排序序列进行排序处理
        int mid = Partition(a,left,right);
        //将带排序序列分为两部分分别入栈，进行处理
        SeqStackPush(&stack,left);
        SeqStackPush(&stack,mid);
        SeqStackPush(&stack,mid + 1);
        SeqStackPush(&stack,right);                                                                             
    }
    Destory(&stack);
    return;
 } 
/**
 *  @name        : void QuickSort(int *a, int begin, int end)
 *  @description : 快速排序（枢轴存放）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
int Partition(int *a, int begin, int end)
{
	int pivotkey;
    int m = begin + (end - begin) / 2;
    //三数取中的判断
    if (a[begin] > a[end])
        swap(a, begin, end);
    if (a[m] > a[end])
        swap(a, m, end);
    if (a[m] < a[begin])
        swap(a, m, begin);
    //此时begin处是三个数中间值

    pivotkey = a[begin];    //用子表第一个记录左枢轴记录
    while (begin<end)    //从表的两端交替向中间扫描
    {
        while (begin<end&&a[end] >= pivotkey)
            end--;
        swap(a, end, begin);    //将比枢轴记录小的记录交换到低端
        while (begin < end&&a[begin] <= pivotkey)
            begin++;
        swap(a, begin, end);    //将比枢轴记录大的记录交换到高端
    }
    return begin;    //返回枢轴所在位置
}

void swap(int a[], int begin, int end)
{
    int temp = a[begin];
    a[begin] = a[end];
    a[end] = temp;
}


/**
 *  @name        : void CountSort(int *a, int size )
 *  @description : 计数排序
 *  @param       : 数组指针a，数组长度size
 */
void CountSort(int *a, int size)
{
	int i = 0;
	int max = 0;
	int *count = 0;
	int *res = 0;

	/*找到最大数*/
	for (i = 0 ; i< size; i++){
		if (a[i] > max){
			max = a[i];
		}
	}

	count = (int *)malloc(sizeof(int)*(max + 1));
	assert(count != NULL);

	memset(count,0,sizeof(int)*(max + 1));

	/*计数*/
	for (i = 0; i < size;i++){
		count[a[i]]++;
	}
	
	/*依次累加*/
	for(i = 1 ;i <= max; i ++){
		count[i] += count[i-1];
	}

	res = (int *)malloc(sizeof(int)*(size));
	assert(res != NULL);
    /*核心代码，count[a[i] - 1]就是排序好的下标*/
	for (i = size-1;i >= 0; i--){
		res[count[a[i]] -1] = a[i];
		count[a[i]]--;
	}
    
	memcpy(a,res,size*(sizeof(int)));

	free(res);
	free(count);
	return;
}


/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : 基数计数排序
 *  @param       : 数组指针a，数组长度size
 */
int GetNumInPos(int num,int pos)
{
	int temp = 1;
	int i;
	for (i = 0; i < pos - 1; i++)
		temp *= 10;
    
	return (num / temp) % 10;
}

void RadixCountSort(int* a, int size)
{
	int *radixArrays[10];    //分别为0~9的序列空间
	int i,j,k,pos;
	for (i = 0; i < 10; i++)
	{
		radixArrays[i] = (int *)malloc(sizeof(int) * (size + 1));
		radixArrays[i][0] = 0;    //index为0处记录这组数据的个数
	}
	
	for (pos = 1; pos <= 10; pos++)   
	{
		for (i = 0; i < size; i++)    //分配过程
		{
			int num = GetNumInPos(a[i], pos);
			int index = ++radixArrays[num][0];
			radixArrays[num][index] = a[i];
		}
        
		for (i = 0,j =0; i < 10; i++)    //收集
		{
			for (k = 1; k <= radixArrays[i][0]; k++)
				a[j++] = radixArrays[i][k];
			radixArrays[i][0] = 0;    //复位
		}
	}
}

/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : 颜色排序,一个是 zero_position，和之前一样，它前边的位置全部存 0。
 				再来一个指针，two_position，它后边的位置全部存 2。
 *  @param       : 数组指针a（只含0，1，2元素），数组长度size
 */
void ColorSort(int *a,int size)
{
	int zero_position = 0;
    int two_position = size - 1;
    int i;
    for (i = 0; i <= two_position; i++) {
        if (a[i] == 0) {
            //将当前位置的数字保存
            int temp = a[zero_position];
            //把 0 存过来
            a[zero_position] = 0;
            //把之前的数换过来
            a[i] = temp;
            //当前指针后移
            zero_position++;
        } else if (a[i] == 2) {
            //将当前位置的数字保存
            int temp = a[two_position];
            //把 2 存过来
            a[two_position] = 2;
            //把之前的数换过来
            a[i] = temp;
            //当前指针前移
            two_position--;
            //这里一定要注意，因为我们把后边的数字换到了第 i 个位置，
            //这个数字我们还没有判断它是多少，外层的 for 循环会使得 i++ 导致跳过这个元素
            //所以要 i--
            //而对于上边 zero_position 的更新不需要考虑，因为它是从前边换过来的数字
            //在之前已经都判断过了
            i--;
        }
    }	
}


/**
 *  @name        : 自拟
 *  @description : 在一个无序序列中找到第K大/小的数
 *  @param       : 数组指针a，数组长度size
 */
void findk(int k,int *a,int begin,int end)  
{  
    int temp;  
    temp=Partition(a,begin,end);  
    if(temp==k-1){  
        printf("第%d大的元素是%d",temp+1,a[temp]);
    } else if(temp>k-1) {
    	findk(k,a,begin,temp-1); 
	} else {
		findk(k,a,temp+1,end);  
	}    
}  
