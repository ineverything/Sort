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
	printf("**** 100k*100�������� ****.\n");
	srand((unsigned) time(NULL)); //��ʱ�����֣�ÿ�β����������һ��,��������Ԥ�����������
	write(SIZE);
	a=read(SIZE);
	
	clock_t c1=clock();
	for(i=0;i<100000;i++){

	    insertSort(a,SIZE);
	    *a=a[100*(i+1)];
	}
	clock_t c2=clock();
	printf("���������ʱ��%dms.\n",(int)(c2-c1));
	
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
	printf("�鲢�����ʱ��%dms.\n",(int)(c4-c3));
	
	clock_t c5=clock();
	for(i=0;i<100000;i++){
	    QuickSort_Recursion(a,a[0],a[SIZE-1]);
	    *a=a[100*(i+1)];
	}	
	clock_t c6=clock();
	printf("��������ݹ���ʱ��%d ms.\n",(int)(c6-c5));
	
	clock_t c7=clock();
	for(i=0;i<100000;i++){
	    QuickSort(a,SIZE);
	    *a=a[100*(i+1)];
	} 
	clock_t c8=clock();
	printf("��������ǵݹ���ʱ��%dms.\n",(int)(c8-c7));
	
	clock_t c9=clock();
	for(i=0;i<100000;i++){
	    CountSort(a,SIZE);
	    *a=a[100*(i+1)];
	}
	clock_t c10=clock();
	free(a);
	printf("���������ʱ��%dms.\n",(int)(c10-c9));
	
	clock_t c11=clock();
	for(i=0;i<100000;i++){
	    RadixCountSort(a,SIZE);
	    *a=a[100*(i+1)];
	}
	clock_t c12=clock();
	free(a);
	printf("�������������ʱ��%dms.\n",(int)(c12-c11));
	
	return 0;
}

//��Ҫ�����ɶ�Ӧ��ģ�Ĳ������ݣ������浽�ļ�
void write(int size)
{
	//�ļ�ָ��,���ļ� 
	FILE *fp;
	fp = fopen("number.txt","w");//��ֻд�����������½������������ 
	 
	//�õ���Ӧ��ģ������
	int i,j,a[size];	
	for (i = 0; i < size; i++)
        a[i] = rand()%100;
        
	//��ʽ��д���ļ� 
	for(j=0;j<100000;j++){
		for(i=0;i<size;i++){
			fprintf(fp,"%-6d",a[i]);//�������4�ַ�������ո�ǰ�油��,-���ո���油��
		i = 0;
		fprintf(fp,"\n");
	} 
	}
	//�ر��ļ� 
	fclose(fp);
}

// ��Ҫ���ȡ�ļ��е����ݲ���������������������,����ӡ��Ӧ��ʱ�� 
int *read(int size)
{
	FILE *fp;
	//�ļ��򿪴���
	if((fp=fopen("number.txt","r"))==NULL){
		printf("error open!");
		system("PAUSE");
		exit(0);
	} 
	//�ļ�����ȷ,��ȡ������
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

