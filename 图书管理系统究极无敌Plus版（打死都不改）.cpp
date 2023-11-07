#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//创建结构体 
struct bookinfo{
	char name[20];
	double price;
	int sum;
};
//创建链表 
struct node{
	struct bookinfo data;
	struct node* next;
};
//创建表头表头不存任何数据 
struct node* createhead(){
	struct node* headnode=(struct node*)malloc(sizeof(struct node));
	headnode->next=NULL;
	return headnode;
}
//创建节点，将信息输入到节点中 
struct node* createnode(struct bookinfo data){
	struct node* newnode=(struct node*)malloc(sizeof(struct node));
	newnode->data=data;
	newnode->next=NULL;
	return newnode;
}
//为listbook赋一个全局变量 
struct node* listbook=NULL;
//表头法插入新节点 
void insertnodebyhead(struct node* headnode,struct bookinfo data){
	struct node* newnode=createnode(data);
	newnode->next=headnode->next;
	headnode->next=newnode;
}
//打印链表 
void printflist(struct node* headnode){
	struct node* print=headnode->next;
	printf("书名\t价格\t数量\n");
	while(print!=NULL){
		printf("%s\t%.1f\t%d\n",print->data.name,print->data.price,print->data.sum);
		print=print->next;
	}
}
//查找数据
struct node* searchbookbyname(struct node* headnode,char* bookname){
	struct node* posnode=headnode->next;
	while(posnode!=NULL&&strcmp(posnode->data.name,bookname)){
		posnode=posnode->next;
	}
	return posnode;
} 
//删除数据
void deletebookbyname(struct node* headnode,char* bookname){
	struct node* posnode=headnode->next;
	struct node* posleftnode=headnode;
	while(posnode!=NULL&&strcmp(posnode->data.name,bookname)){
		posleftnode=posnode;
		posnode=posleftnode->next;
	}
	if(posnode==NULL){
		printf("您想删除的书籍在图书馆不存在！");
	} else{
		printf("删除成功");
		posleftnode->next=posnode->next;
	    free(posnode);
	    posnode=NULL;
	}
} 
//排序
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
//做初始界面 
void makemenu(){
	printf("------------------------------------------------------------------------------------------------------------------------");
	printf("欢迎打开图书管理系统\n");
	printf("0.退出系统\n");
	printf("1.登记书籍\n"); 
	printf("2.浏览书籍\n"); 
	printf("3.借阅书籍\n"); 
	printf("4.归还书籍\n"); 
	printf("5.排序书籍\n"); 
	printf("6.删除书籍\n"); 
	printf("7.查找书籍\n"); 
	printf("-----------------------------------------------------------------------------------------------------------------------");
	printf("请输入您想进行的操作：");
}
//保存文件 
void saveinfotofile(const char* filename,struct node* headnode){
	FILE* fp=fopen(filename,"w");
	struct node* fprint=headnode->next;
	while(fprint!=NULL){
		fprintf(fp,"%s\t%.1f\t%d\n",fprint->data.name,fprint->data.price,fprint->data.sum);
		fprint=fprint->next;
	}
	fclose(fp);
}
//读写文件 
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
//交互面板 
void keydown(){
	struct bookinfo tempbook;
	struct node* result;
	int userkey=0;
	scanf("%d",&userkey);
	switch(userkey){
		case 0:printf("【退出】\n");
		        printf("退出成功！\n");
		        system("pause");
		        exit(0);
				break;
		case 1:printf("【登记】\n");
		        printf("请输入您想要登记的书籍信息（书名、价格、数量）:");
		        scanf("%s %lf %d",tempbook.name,&tempbook.price,&tempbook.sum);
		        insertnodebyhead(listbook,tempbook);
		        saveinfotofile("bookinfoplus.txt",listbook);
				break;
		case 2:printf("【浏览】\n");
		        printflist(listbook);
				break;
		case 3:printf("【借阅】\n");
		        printf("请输入您想要借阅的书籍：");
		        scanf("%s",tempbook.name);
		        result=searchbookbyname(listbook,tempbook.name);
		        if(result==NULL){
		        	printf("图书馆不存在该书籍！");
				}else{
					if(result->data.sum>0){
						printf("借阅成功！\n");
						result->data.sum--;
						printf("%s还剩余%d本",result->data.name,result->data.sum);
					}
				}
				saveinfotofile("bookinfoplus.txt",listbook);
				break;
		case 4:printf("【归还】\n");
		        printf("请输入您想要归还的书籍:");
		        scanf("%s",tempbook.name);
		        result=searchbookbyname(listbook,tempbook.name);
		        if(result==NULL){
		        	printf("该书不属于图书馆！");
				}else{
					printf("归还成功!\n");
					result->data.sum++;
					printf("%s还剩余%d本",result->data.name,result->data.sum);
				}
				saveinfotofile("bookinfoplus.txt",listbook);
				break;
		case 5:printf("【排序】\n");
		        sortbookbyprice(listbook);
				break;
		case 6:printf("【删除】\n");
		        printf("请输入您想删除的书籍：");
		        scanf("%s",tempbook.name);
		        deletebookbyname(listbook,tempbook.name);
		        saveinfotofile("bookinfoplus.txt",listbook);
				break;
		case 7:printf("【查找】\n");
		        printf("请输入您想要查找的书籍：");
		        scanf("%s",tempbook.name);
		        result=searchbookbyname(listbook,tempbook.name);
		        if(result==NULL){
		        	printf("您所查找的书籍不属于图书馆！");
				}else{
					printf("书名\t价格\t数量\n");
					printf("%s\t%.1f\t%d\n",result->data.name,result->data.price,result->data.sum);
				}
				break;
	}
}
//主题函数 
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
