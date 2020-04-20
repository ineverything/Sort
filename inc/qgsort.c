#include"qgsort.h"
#include"SqStack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>

/**
 *  @name        : void insertSort(int *a,int n);
 *  @description : ��������,��һ����ʱ�����洢��ǰֵ��ǰ���Ԫ�رȺ����ʱ���ȰѺ����Ԫ�ش�����ʱ������ǰ
 					��Ԫ�ص�ֵ�ŵ�����Ԫ��λ�ã��ٵ�������ֵ���뵽���ʵ�����λ�á�
 *  @param       : ����ָ�� a, ���鳤�� n
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
 *  @description : �鲢���򣨺ϲ����飩 
 *  @param       : ����ָ��a���������begin�������е�mid�������յ�end����������ָ��temp
 */
void MergeArray(int *a,int begin,int mid,int end,int *temp)
{
	int i = begin,j = mid + 1;
    int m = mid,n = end;
    int k = 0;
 
    //��ʼ�ϲ��������飻
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
 
    //��temp�����еĽ��װ��a����
    for(i = 0;i < k;i++){
        a[begin + i] = temp[i];
    }
}

/**
 *  @name        : void MergeSort(int *a,int begin,int end,int *temp);
 *  @description : �鲢����
 *  @param       : ����ָ��a���������begin�������յ�end����������ָ��temp
 */
void MergeSort(int *a,int begin,int end,int *temp)
{
	if(begin < end){
    	int mid = (begin + end) / 2;
        //  �ֱ�ݹ��������Ҳ��Ϊ2-·�鲢��
        MergeSort(a,begin,mid,temp);   //�������
        MergeSort(a,mid + 1,end,temp);   //�ұ�����
        MergeArray(a,begin,mid,end,temp); //�������������������ϲ�
    }
}


/**
 *  @name        : void QuickSort(int *a, int begin, int end);
 *  @description : �������򣨵ݹ�棩
 *  @param       : ����ָ��a���������begin�������յ�end
 */
void QuickSort_Recursion(int *a, int begin, int end)
{
	int pivot;
    if (begin<end){
        pivot = Partition(a, begin, end);
        QuickSort_Recursion(a, begin, pivot-1);    //�Ե��ӱ���еݹ�����
        QuickSort_Recursion(a, pivot + 1, end);    //�Ը��ӱ���еݹ�����
    }
}

/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : �������򣨷ǵݹ�棩
 �ݹ���㷨��Ҫ���ڻ��������䣬���Ҫ�ǵݹ�ʵ�ֿ��ţ�ֻҪʹ��һ��ջ����������Ϳ����ˡ�
һ�㽫�ݹ����ĳɷǵݹ������뵽�ľ���ʹ��ջ����Ϊ�ݹ鱾�����һ��ѹջ�Ĺ��̡�
 *  @param       : ����ָ��a�����鳤��size
 */
void QuickSort(int *a,int size)
{
	if(a == NULL || size <= 1)                                                                           
        return;
    SeqStack stack;//����ջ
    InitSeqStack(&stack,size);//��ʼ��ջ
    //��ջ�������������е���λ����
    SeqStackPush(&stack,0);
 
    int left;
    int right;
    while(1)
    {
        //ȡջ��Ԫ����Ϊ���������е�β����
        int ret = SeqStackTop(&stack,&right);
        if(ret == -1)//ջ��Ϊ�գ����������д�����
        {
            return;
        }
        //��ջ����ȡջ��Ԫ��
        SeqStackPop(&stack);
        //��ʱ��ջ��Ԫ�ر�Ϊ���������е�������
        SeqStackTop(&stack,&left);
        //��ջջ��Ԫ��
        SeqStackPop(&stack);
        //�������������Ԫ�ظ���С�ڵ���1��������б�Ȼ�Ѿ��ź���
        //�Ҳ����ڷ�Ϊ��С�����У�Ҳ�Ͳ���Ҫ�ٽ��������ٽ�����ջ��
        if(right - left <= 1)
        {
            continue;
        }
        //�Դ��������н���������
        int mid = Partition(a,left,right);
        //�����������з�Ϊ�����ֱַ���ջ�����д���
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
 *  @description : �������������ţ�
 *  @param       : ����ָ��a���������begin�������յ�end
 */
int Partition(int *a, int begin, int end)
{
	int pivotkey;
    int m = begin + (end - begin) / 2;
    //����ȡ�е��ж�
    if (a[begin] > a[end])
        swap(a, begin, end);
    if (a[m] > a[end])
        swap(a, m, end);
    if (a[m] < a[begin])
        swap(a, m, begin);
    //��ʱbegin�����������м�ֵ

    pivotkey = a[begin];    //���ӱ��һ����¼�������¼
    while (begin<end)    //�ӱ�����˽������м�ɨ��
    {
        while (begin<end&&a[end] >= pivotkey)
            end--;
        swap(a, end, begin);    //���������¼С�ļ�¼�������Ͷ�
        while (begin < end&&a[begin] <= pivotkey)
            begin++;
        swap(a, begin, end);    //���������¼��ļ�¼�������߶�
    }
    return begin;    //������������λ��
}

void swap(int a[], int begin, int end)
{
    int temp = a[begin];
    a[begin] = a[end];
    a[end] = temp;
}


/**
 *  @name        : void CountSort(int *a, int size )
 *  @description : ��������
 *  @param       : ����ָ��a�����鳤��size
 */
void CountSort(int *a, int size)
{
	int i = 0;
	int max = 0;
	int *count = 0;
	int *res = 0;

	/*�ҵ������*/
	for (i = 0 ; i< size; i++){
		if (a[i] > max){
			max = a[i];
		}
	}

	count = (int *)malloc(sizeof(int)*(max + 1));
	assert(count != NULL);

	memset(count,0,sizeof(int)*(max + 1));

	/*����*/
	for (i = 0; i < size;i++){
		count[a[i]]++;
	}
	
	/*�����ۼ�*/
	for(i = 1 ;i <= max; i ++){
		count[i] += count[i-1];
	}

	res = (int *)malloc(sizeof(int)*(size));
	assert(res != NULL);
    /*���Ĵ��룬count[a[i] - 1]��������õ��±�*/
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
 *  @description : ������������
 *  @param       : ����ָ��a�����鳤��size
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
	int *radixArrays[10];    //�ֱ�Ϊ0~9�����пռ�
	int i,j,k,pos;
	for (i = 0; i < 10; i++)
	{
		radixArrays[i] = (int *)malloc(sizeof(int) * (size + 1));
		radixArrays[i][0] = 0;    //indexΪ0����¼�������ݵĸ���
	}
	
	for (pos = 1; pos <= 10; pos++)   
	{
		for (i = 0; i < size; i++)    //�������
		{
			int num = GetNumInPos(a[i], pos);
			int index = ++radixArrays[num][0];
			radixArrays[num][index] = a[i];
		}
        
		for (i = 0,j =0; i < 10; i++)    //�ռ�
		{
			for (k = 1; k <= radixArrays[i][0]; k++)
				a[j++] = radixArrays[i][k];
			radixArrays[i][0] = 0;    //��λ
		}
	}
}

/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : ��ɫ����,һ���� zero_position����֮ǰһ������ǰ�ߵ�λ��ȫ���� 0��
 				����һ��ָ�룬two_position������ߵ�λ��ȫ���� 2��
 *  @param       : ����ָ��a��ֻ��0��1��2Ԫ�أ������鳤��size
 */
void ColorSort(int *a,int size)
{
	int zero_position = 0;
    int two_position = size - 1;
    int i;
    for (i = 0; i <= two_position; i++) {
        if (a[i] == 0) {
            //����ǰλ�õ����ֱ���
            int temp = a[zero_position];
            //�� 0 �����
            a[zero_position] = 0;
            //��֮ǰ����������
            a[i] = temp;
            //��ǰָ�����
            zero_position++;
        } else if (a[i] == 2) {
            //����ǰλ�õ����ֱ���
            int temp = a[two_position];
            //�� 2 �����
            a[two_position] = 2;
            //��֮ǰ����������
            a[i] = temp;
            //��ǰָ��ǰ��
            two_position--;
            //����һ��Ҫע�⣬��Ϊ���ǰѺ�ߵ����ֻ����˵� i ��λ�ã�
            //����������ǻ�û���ж����Ƕ��٣����� for ѭ����ʹ�� i++ �����������Ԫ��
            //����Ҫ i--
            //�������ϱ� zero_position �ĸ��²���Ҫ���ǣ���Ϊ���Ǵ�ǰ�߻�����������
            //��֮ǰ�Ѿ����жϹ���
            i--;
        }
    }	
}


/**
 *  @name        : ����
 *  @description : ��һ�������������ҵ���K��/С����
 *  @param       : ����ָ��a�����鳤��size
 */
void findk(int k,int *a,int begin,int end)  
{  
    int temp;  
    temp=Partition(a,begin,end);  
    if(temp==k-1){  
        printf("��%d���Ԫ����%d",temp+1,a[temp]);
    } else if(temp>k-1) {
    	findk(k,a,begin,temp-1); 
	} else {
		findk(k,a,temp+1,end);  
	}    
}  
