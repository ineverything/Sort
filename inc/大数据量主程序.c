#include"qgsort.h"
#include"SqStack.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void write(int size);
void read(int size);

int main(int argc, char *argv[])
{
	printf("**** 10000��ģ���� ****\n");
	write(10000);
	read(10000);
	
	printf("**** 50000��ģ���� ****\n");
	write(50000);
	read(50000);
	
	printf("**** 200000��ģ���� ****\n");
	write(200000);
	read(200000);
	
	return 0;
}

//��Ҫ�����ɶ�Ӧ��ģ�Ĳ������ݣ������浽�ļ�
void write(int size)
{
	//�ļ�ָ��,���ļ� 
	FILE *fp;
	fp = fopen("number.txt","w");//��ֻд�����������½������������ 
	 
	//�õ���Ӧ��ģ������
	int i,a[size];
	srand((unsigned) time(NULL)); //��ʱ�����֣�ÿ�β����������һ��,��������Ԥ�����������
	for (i = 0; i < size; i++)
        a[i] = rand()%1000; 
        
	//��ʽ��д���ļ� 
	for(i=0;i<size;i++){
		fprintf(fp,"%-6d",a[i]);//�������4�ַ�������ո�ǰ�油��,-���ո���油��
		fprintf(fp,"\n");
	} 
	
	//�ر��ļ� 
	fclose(fp);
}

// ��Ҫ���ȡ�ļ��е����ݲ���������������������,����ӡ��Ӧ��ʱ�� 
void read(int size)
{
	FILE *fp;
	//�ļ��򿪴���
	if((fp=fopen("number.txt","r"))==NULL){
		printf("error open!");
		system("PAUSE");
		exit(0);
	} 
	//�ļ�����ȷ,��ȡ������
	int i,a[size];
	for(i=0;i<size;i++){
		fscanf(fp,"%d",&a[i]);
		fscanf(fp,"\n");
	} 
	fclose(fp);
	
	//�õ����飬��ʼ����������õ�ʱ�� 
	clock_t c1=clock();
	insertSort(a,size);
	clock_t c2=clock();
	printf("���������ʱ��%dms.\n",(int)(c2-c1));
	
	int *temp=(int *)malloc(size*sizeof(int));
	clock_t c3=clock();
	if(temp != NULL){
       MergeSort(a,a[0],a[size-1],temp);
       free(temp);
    }
    else
        printf("no space!\n");
	clock_t c4=clock();
	printf("�鲢�����ʱ��%dms.\n",(int)(c4-c3));
	
	clock_t c5=clock();
	QuickSort_Recursion(a, a[0],a[size-1]);
	clock_t c6=clock();
	printf("��������ݹ���ʱ��%dms.\n",(int)(c6-c5));
	
	clock_t c7=clock();
	QuickSort(a,size); 
	clock_t c8=clock();
	printf("��������ǵݹ���ʱ��%dms.\n",(int)(c8-c7));
	
	clock_t c9=clock();
	CountSort(a,size);
	clock_t c10=clock();
	printf("���������ʱ��%dms.\n",(int)(c10-c9));
	
	clock_t c11=clock();
	RadixCountSort(a,size);
	clock_t c12=clock();
	printf("�������������ʱ��%dms.\n",(int)(c12-c11));
	
}

