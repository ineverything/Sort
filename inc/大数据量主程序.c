#include"qgsort.h"
#include"SqStack.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void write(int size);
void read(int size);

int main(int argc, char *argv[])
{
	printf("**** 10000规模数组 ****\n");
	write(10000);
	read(10000);
	
	printf("**** 50000规模数组 ****\n");
	write(50000);
	read(50000);
	
	printf("**** 200000规模数组 ****\n");
	write(200000);
	read(200000);
	
	return 0;
}

//按要求生成对应规模的测试数据，并保存到文件
void write(int size)
{
	//文件指针,打开文件 
	FILE *fp;
	fp = fopen("number.txt","w");//打开只写，不存在则新建，存在则清空 
	 
	//得到对应规模的数组
	int i,a[size];
	srand((unsigned) time(NULL)); //用时间做种，每次产生随机数不一样,产生不可预见的随机序列
	for (i = 0; i < size; i++)
        a[i] = rand()%1000; 
        
	//格式化写入文件 
	for(i=0;i<size;i++){
		fprintf(fp,"%-6d",a[i]);//最少输出4字符，不足空格前面补充,-：空格后面补充
		fprintf(fp,"\n");
	} 
	
	//关闭文件 
	fclose(fp);
}

// 按要求读取文件中的数据并让上述排序函数进行排序,并打印对应的时间 
void read(int size)
{
	FILE *fp;
	//文件打开错误
	if((fp=fopen("number.txt","r"))==NULL){
		printf("error open!");
		system("PAUSE");
		exit(0);
	} 
	//文件打开正确,读取到数组
	int i,a[size];
	for(i=0;i<size;i++){
		fscanf(fp,"%d",&a[i]);
		fscanf(fp,"\n");
	} 
	fclose(fp);
	
	//得到数组，开始排序操作并得到时间 
	clock_t c1=clock();
	insertSort(a,size);
	clock_t c2=clock();
	printf("插入排序耗时是%dms.\n",(int)(c2-c1));
	
	int *temp=(int *)malloc(size*sizeof(int));
	clock_t c3=clock();
	if(temp != NULL){
       MergeSort(a,a[0],a[size-1],temp);
       free(temp);
    }
    else
        printf("no space!\n");
	clock_t c4=clock();
	printf("归并排序耗时是%dms.\n",(int)(c4-c3));
	
	clock_t c5=clock();
	QuickSort_Recursion(a, a[0],a[size-1]);
	clock_t c6=clock();
	printf("快速排序递归版耗时是%dms.\n",(int)(c6-c5));
	
	clock_t c7=clock();
	QuickSort(a,size); 
	clock_t c8=clock();
	printf("快速排序非递归版耗时是%dms.\n",(int)(c8-c7));
	
	clock_t c9=clock();
	CountSort(a,size);
	clock_t c10=clock();
	printf("计数排序耗时是%dms.\n",(int)(c10-c9));
	
	clock_t c11=clock();
	RadixCountSort(a,size);
	clock_t c12=clock();
	printf("基数计数排序耗时是%dms.\n",(int)(c12-c11));
	
}

