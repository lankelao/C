#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct NODE
{
	int id;
	char *name;
	char *tel;
	struct NODE *pNext;//有链表主函数就要有头尾指针
}Node;

typedef struct PAGE
{
	int TotalInfo; //总条数
	int TotalPage;  //总页数
	int CurrentPage;  //当前页
	int OnePageInfo; //每页显示多少条
}Page;

Node* GetNode();//1.测试用   获得节点，参数id内部生成，名字随机，电话随机，所以不用参数
void AddNode(Node **ppHead,Node **ppEnd,Node *pNode);//2.添加链表  (头   尾    添加的谁)
int GetId();//3.自动生成编号
char* GetName();//4.姓名电话原本放在字符常量区，将来可能要改所以要放在堆区
char* GetTel();//5.电话
void InitInfo(Node **ppHead,Node **ppEnd,int n);//6.初始化数据 去掉测试数据
Page* GetPage(Node *pHead,int n);//7.
void ShowInfo(Node *pHead,Page *pPage);//8.显示分页信息
void ShowMenu(Page *pPage);//9.显示菜单


int main()
{
	Node *pHead = NULL;
	Node *pEnd = NULL;
	Page *pPage = NULL;

	InitInfo(&pHead,&pEnd,101);

	pPage = GetPage(pHead,10);
	
	pPage->CurrentPage = 2;//查看第2页

	ShowInfo(pHead,pPage);
	ShowMenu(pPage);
	//while(pHead != NULL)
	//{
	//	printf("%d\t%s\t%s\n",pHead->id,pHead->name,pHead->tel);
	//	pHead = pHead->pNext;
	//}

	return 0;
}
Node* GetNode()
{
	Node *pNode = (Node*)malloc(sizeof(Node));//主动申请空间，主函数可以调用
	//pNode->id = 1; //先给1，后面再改
	pNode->id = GetId();
	//pNode->name = "aaaa";
	pNode->name = GetName();
	//pNode->tel = "11111111111";
	pNode->tel = GetTel();
	pNode->pNext = NULL;

	return pNode;
}
void AddNode(Node **ppHead,Node **ppEnd,Node *pNode)
{
	if(*ppHead == NULL)
	{
		*ppHead = pNode;
	}
	else
	{
		(*ppEnd)->pNext = pNode;
	}
	*ppEnd = pNode;

	return;
}
int GetId()
{
	static int id = 1;//需要静态，局部不行,局部每次都开辟再释放
	return id++;//id++第一次返回1，id值变2，没有问题
}
char* GetName()
{
	char *pName = (char*)malloc(sizeof(char)*6);//名字开辟6个字符的空间
	 int i;
	 for(i=0;i<5;i++)
	 {
		 pName[i] = rand()%26 + 'a';//rand随机数，取a--z字符当名字
	 }
	 pName[i] = '\0';

	 return pName;
}
char* GetTel()
{
	char *pTel = (char*)malloc(sizeof(char)*12);//11位号码
	int i;
	switch (rand()%4)//取四个随机号段
	{
	case 0:
		pTel[0] = '1';
		pTel[1] = '3';
		pTel[2] = '3';
		break;
	case 1:
		strcpy_s(pTel,12,"155");
		break;
	case 2:
		strcpy_s(pTel,12,"177");
		break;
	case 3:
		strcpy_s(pTel,12,"188");
		break;
	}
	for(i=3;i<11;i++)
	{
		pTel[i] = rand()%10 + '0';
	}
	pTel[i] = '\0';

	return pTel;
}
void InitInfo(Node **ppHead,Node **ppEnd,int n)//ppHead存的就是pHead的地址,初始化n条
{
	int i;
	srand((unsigned int)time(NULL));//用随机数先埋种子，随机种子只能埋一次，
	for(i=0;i<n;i++)//测试用
	{
		AddNode(ppHead,ppEnd,GetNode());
	}
}
Page* GetPage(Node *pHead,int n)
{
	//1.给结构体申请空间
	Page *pPage = (Page*)malloc(sizeof(Page));
	pPage->CurrentPage = 1;
	pPage->OnePageInfo = n;
	pPage->TotalInfo = 0;
	//2.通过链表把结构体里的值都赋上
	while(pHead != NULL)//只是遍历，用值传递，参数只需要Node*pHead
	{
		pPage->TotalInfo++;
		pHead = pHead->pNext;
	}
	//if(pPage->TotalInfo%pPage->OnePageInfo == 0)
	//{
	//	pPage->TotalPage = pPage->TotalInfo / pPage->OnePageInfo;
	//}
	//else
	//{
	//	pPage->TotalPage = pPage->TotalInfo / pPage->OnePageInfo +1;
	//}
	pPage->TotalPage = pPage->TotalInfo%pPage->OnePageInfo == 0 ? pPage->TotalInfo / pPage->OnePageInfo : pPage->TotalInfo / pPage->OnePageInfo +1;
	return pPage;
}
void ShowInfo(Node *pHead,Page *pPage)
{
	int begin = (pPage->CurrentPage-1) * pPage->OnePageInfo + 1;
	int end = pPage->CurrentPage * pPage->OnePageInfo;
	int count = 0;

	while(pHead != NULL)
	{
		count++;
		if(begin<=count && count<=end)
		{
			printf("%d\t%s\t%s\n",pHead->id,pHead->name,pHead->tel);
		}
		pHead = pHead->pNext;
	}
	return;
}
void ShowMenu(Page *pPage)
{
	printf("当前第%d页  共%d页  共%d条  w上一页  s下一页  b返回\n",pPage->CurrentPage,pPage->TotalPage,pPage->TotalInfo);
	return;
}