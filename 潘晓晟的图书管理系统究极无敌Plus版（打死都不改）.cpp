#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//�����ṹ�� 
struct bookinfo{
	char name[20];
	double price;
	int sum;
};
//�������� 
struct node{
	struct bookinfo data;
	struct node* next;
};
//������ͷ��ͷ�����κ����� 
struct node* createhead(){
	struct node* headnode=(struct node*)malloc(sizeof(struct node));
	headnode->next=NULL;
	return headnode;
}
//�����ڵ㣬����Ϣ���뵽�ڵ��� 
struct node* createnode(struct bookinfo data){
	struct node* newnode=(struct node*)malloc(sizeof(struct node));
	newnode->data=data;
	newnode->next=NULL;
	return newnode;
}
//Ϊlistbook��һ��ȫ�ֱ��� 
struct node* listbook=NULL;
//��ͷ�������½ڵ� 
void insertnodebyhead(struct node* headnode,struct bookinfo data){
	struct node* newnode=createnode(data);
	newnode->next=headnode->next;
	headnode->next=newnode;
}
//��ӡ���� 
void printflist(struct node* headnode){
	struct node* print=headnode->next;
	printf("����\t�۸�\t����\n");
	while(print!=NULL){
		printf("%s\t%.1f\t%d\n",print->data.name,print->data.price,print->data.sum);
		print=print->next;
	}
}
//��������
struct node* searchbookbyname(struct node* headnode,char* bookname){
	struct node* posnode=headnode->next;
	while(posnode!=NULL&&strcmp(posnode->data.name,bookname)){
		posnode=posnode->next;
	}
	return posnode;
} 
//ɾ������
void deletebookbyname(struct node* headnode,char* bookname){
	struct node* posnode=headnode->next;
	struct node* posleftnode=headnode;
	while(posnode!=NULL&&strcmp(posnode->data.name,bookname)){
		posleftnode=posnode;
		posnode=posleftnode->next;
	}
	if(posnode==NULL){
		printf("����ɾ�����鼮��ͼ��ݲ����ڣ�");
	} else{
		printf("ɾ���ɹ�");
		posleftnode->next=posnode->next;
	    free(posnode);
	    posnode=NULL;
	}
} 
//����
void sortbookbyprice(struct node* headnode){
	for(struct node* p=headnode->next;p->next!=NULL;p=p->next){
		if(p->data.price<p->next->data.price){
			struct bookinfo tempdata=p->data;
			p->data=p->next->data;
			p->next->data=tempdata;
		}
	}
	printflist(headnode); 
} 
//����ʼ���� 
void makemenu(){
	printf("------------------------------------------------------------------------------------------------------------------------");
	printf("��ӭ��ͼ�����ϵͳ\n");
	printf("0.�˳�ϵͳ\n");
	printf("1.�Ǽ��鼮\n"); 
	printf("2.����鼮\n"); 
	printf("3.�����鼮\n"); 
	printf("4.�黹�鼮\n"); 
	printf("5.�����鼮\n"); 
	printf("6.ɾ���鼮\n"); 
	printf("7.�����鼮\n"); 
	printf("-----------------------------------------------------------------------------------------------------------------------");
	printf("������������еĲ�����");
}
//�����ļ� 
void saveinfotofile(const char* filename,struct node* headnode){
	FILE* fp=fopen(filename,"w");
	struct node* fprint=headnode->next;
	while(fprint!=NULL){
		fprintf(fp,"%s\t%.1f\t%d\n",fprint->data.name,fprint->data.price,fprint->data.sum);
		fprint=fprint->next;
	}
	fclose(fp);
}
//��д�ļ� 
void readinfotofile(const char* filename,struct node* headnode){
	FILE* fp=fopen(filename,"r");
	if(fp==NULL){
		fp=fopen(filename,"w+");
	}
	struct bookinfo tempdata;
	while(fscanf(fp,"%s\t%lf\t%d\n",tempdata.name,&tempdata.price,&tempdata.sum)!=EOF){
		insertnodebyhead(listbook,tempdata);
	}
	fclose(fp);
}
//������� 
void keydown(){
	struct bookinfo tempbook;
	struct node* result;
	int userkey=0;
	scanf("%d",&userkey);
	switch(userkey){
		case 0:printf("���˳���\n");
		        printf("�˳��ɹ���\n");
		        system("pause");
		        exit(0);
				break;
		case 1:printf("���Ǽǡ�\n");
		        printf("����������Ҫ�Ǽǵ��鼮��Ϣ���������۸�������:");
		        scanf("%s %lf %d",tempbook.name,&tempbook.price,&tempbook.sum);
		        insertnodebyhead(listbook,tempbook);
		        saveinfotofile("bookinfoplus.txt",listbook);
				break;
		case 2:printf("�������\n");
		        printflist(listbook);
				break;
		case 3:printf("�����ġ�\n");
		        printf("����������Ҫ���ĵ��鼮��");
		        scanf("%s",tempbook.name);
		        result=searchbookbyname(listbook,tempbook.name);
		        if(result==NULL){
		        	printf("ͼ��ݲ����ڸ��鼮��");
				}else{
					if(result->data.sum>0){
						printf("���ĳɹ���\n");
						result->data.sum--;
						printf("%s��ʣ��%d��",result->data.name,result->data.sum);
					}
				}
				saveinfotofile("bookinfoplus.txt",listbook);
				break;
		case 4:printf("���黹��\n");
		        printf("����������Ҫ�黹���鼮:");
		        scanf("%s",tempbook.name);
		        result=searchbookbyname(listbook,tempbook.name);
		        if(result==NULL){
		        	printf("���鲻����ͼ��ݣ�");
				}else{
					printf("�黹�ɹ�!\n");
					result->data.sum++;
					printf("%s��ʣ��%d��",result->data.name,result->data.sum);
				}
				saveinfotofile("bookinfoplus.txt",listbook);
				break;
		case 5:printf("������\n");
		        sortbookbyprice(listbook);
				break;
		case 6:printf("��ɾ����\n");
		        printf("����������ɾ�����鼮��");
		        scanf("%s",tempbook.name);
		        deletebookbyname(listbook,tempbook.name);
		        saveinfotofile("bookinfoplus.txt",listbook);
				break;
		case 7:printf("�����ҡ�\n");
		        printf("����������Ҫ���ҵ��鼮��");
		        scanf("%s",tempbook.name);
		        result=searchbookbyname(listbook,tempbook.name);
		        if(result==NULL){
		        	printf("�������ҵ��鼮������ͼ��ݣ�");
				}else{
					printf("����\t�۸�\t����\n");
					printf("%s\t%.1f\t%d\n",result->data.name,result->data.price,result->data.sum);
				}
				break;
	}
}
//���⺯�� 
int main(){
	listbook=createhead();
	readinfotofile("bookinfoplus.txt",listbook);
	while(1){
		makemenu();
		keydown(); 
		printf("\n");
		system("pause");
		system("cls");
	}
	system("pause");
	return 0;
} 
