#include"qgsort.h"
#include"SqStack.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define SIZE 100
void write(int size);
int *read(int size);

int main(int argc, char *argv[])
{
	int i;
	int *a = NULL;
	printf("**** 100k*100数组排序 ****.\n");
	srand((unsigned) time(NULL)); //用时间做种，每次产生随机数不一样,产生不可预见的随机序列
	write(SIZE);
	a=read(SIZE);
	
	clock_t c1=clock();
	for(i=0;i<100000;i++){

	    insertSort(a,SIZE);
	    *a=a[100*(i+1)];
	}
	clock_t c2=clock();
	printf("插入排序耗时是%dms.\n",(int)(c2-c1));
	
	clock_t c3=clock();
	for(i=0;i<100000;i++){
	int *temp=(int *)malloc(SIZE*sizeof(int));
	if(temp != NULL){
       MergeSort(a,a[0],a[SIZE-1],temp);
       *a=a[100*(i+1)];
       free(temp);
    }
    else
        printf("no space!\n");
	}
	clock_t c4=clock();
	printf("归并排序耗时是%dms.\n",(int)(c4-c3));
	
	clock_t c5=clock();
	for(i=0;i<100000;i++){
	    QuickSort_Recursion(a,a[0],a[SIZE-1]);
	    *a=a[100*(i+1)];
	}	
	clock_t c6=clock();
	printf("快速排序递归版耗时是%d ms.\n",(int)(c6-c5));
	
	clock_t c7=clock();
	for(i=0;i<100000;i++){
	    QuickSort(a,SIZE);
	    *a=a[100*(i+1)];
	} 
	clock_t c8=clock();
	printf("快速排序非递归版耗时是%dms.\n",(int)(c8-c7));
	
	clock_t c9=clock();
	for(i=0;i<100000;i++){
	    CountSort(a,SIZE);
	    *a=a[100*(i+1)];
	}
	clock_t c10=clock();
	free(a);
	printf("计数排序耗时是%dms.\n",(int)(c10-c9));
	
	clock_t c11=clock();
	for(i=0;i<100000;i++){
	    RadixCountSort(a,SIZE);
	    *a=a[100*(i+1)];
	}
	clock_t c12=clock();
	free(a);
	printf("基数计数排序耗时是%dms.\n",(int)(c12-c11));
	
	return 0;
}

//按要求生成对应规模的测试数据，并保存到文件
void write(int size)
{
	//文件指针,打开文件 
	FILE *fp;
	fp = fopen("number.txt","w");//打开只写，不存在则新建，存在则清空 
	 
	//得到对应规模的数组
	int i,j,a[size];	
	for (i = 0; i < size; i++)
        a[i] = rand()%100;
        
	//格式化写入文件 
	for(j=0;j<100000;j++){
		for(i=0;i<size;i++){
			fprintf(fp,"%-6d",a[i]);//最少输出4字符，不足空格前面补充,-：空格后面补充
		i = 0;
		fprintf(fp,"\n");
	} 
	}
	//关闭文件 
	fclose(fp);
}

// 按要求读取文件中的数据并让上述排序函数进行排序,并打印对应的时间 
int *read(int size)
{
	FILE *fp;
	//文件打开错误
	if((fp=fopen("number.txt","r"))==NULL){
		printf("error open!");
		system("PAUSE");
		exit(0);
	} 
	//文件打开正确,读取到数组
	int i;
	int *a;
	a = (int*)malloc(100000*SIZE*sizeof(int));
	for(i=0;i<size;i++){
		fscanf(fp,"%d",&a[i]);
		fscanf(fp,"\n");
	} 
	fclose(fp);
	return a;
}

