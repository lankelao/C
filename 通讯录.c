#include<stdio.h>//可以把头文件和声明都存到自己头文件里，用#include "MyHead.h"调用
#include<stdlib.h>// " "优先调用自己的头文件，< >优先调用系统头文件
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

int g_menu_type;//为了重新查询按钮
char g_Key; //按b返回不了，本来应该用传参来按的是啥，降低难度用全局变量

Node* GetNode();//1.测试用   获得节点，参数id内部生成，名字随机，电话随机，所以不用参数
void AddNode(Node **ppHead,Node **ppEnd,Node *pNode);//2.添加链表  (头   尾    添加的谁)
int GetId();//3.自动生成编号
char* GetName();//4.姓名电话原本放在字符常量区，将来可能要改所以要放在堆区
char* GetTel();//5.电话
void InitInfo(Node **ppHead,Node **ppEnd,int n);//6.初始化数据 去掉测试数据
Page* GetPage(Node *pHead,int n);//7.
void ShowInfo(Node *pHead,Page *pPage);//8.显示分页信息
void ShowMenu(Page *pPage);//9.显示菜单
void TurnPage(Page *pPage,Node *pHead);//10.翻页
char GetKey();//11.去掉回车'\n'带来的错误
void Browse(Node *pHead);//12.把查看功能封装起来
Node* GetNodeIn(); //13.添加通讯录
char *GetString();//14.添加名字和电话
void Query(Node *pHead);//15.查询通讯录
void DeleteNode(Node **ppHead,Node **ppEnd,int id);//删除联系人
void DeleteInfo(Node **ppHead,Node **ppEnd);
void UpDataInfo(Node *pHead);//修改通讯录

int main()
{
	Node *pHead = NULL;
	Node *pEnd = NULL;
	char c;

	InitInfo(&pHead,&pEnd,101);


	while(1)
	{
		printf("1.查看通讯录\n");
		printf("2.添加信息\n");
		printf("3.查询信息\n");
		printf("4.删除信息\n");
		printf("5.修改信息\n");
		printf("q.退出\n");

		c = GetKey();

		switch (c)
		{
		case '1':
			g_menu_type = 1;
			Browse(pHead);
			break;
		case '2':
			AddNode(&pHead,&pEnd,GetNodeIn());
			break;
		case '3':
			g_menu_type = 3;
			Query(pHead);
			break;
		case '4':
			g_menu_type = 4;
			DeleteInfo(&pHead,&pEnd);
			break;
		case '5':
			g_menu_type = 5;
			UpDataInfo(pHead);
			break;
		case 'q':
			return;
			break;
		}
	}
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
	pPage->CurrentPage = 0;
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
	switch(g_menu_type)
	{
	case 1:
		printf("当前第%d页  共%d页  共%d条  w上一页  s下一页  b返回\n",pPage->CurrentPage,pPage->TotalPage,pPage->TotalInfo);
		break;
	case 3:
		printf("当前第%d页  共%d页  共%d条  w上一页  s下一页  c重新查询  b返回\n",pPage->CurrentPage,pPage->TotalPage,pPage->TotalInfo);
		break;
	case 4:
		printf("当前第%d页  共%d页  共%d条  w上一页  s下一页  d删除信息  b返回\n",pPage->CurrentPage,pPage->TotalPage,pPage->TotalInfo);
		break;
	case 5:
		printf("当前第%d页  共%d页  共%d条  w上一页  s下一页  u修改信息  b返回\n",pPage->CurrentPage,pPage->TotalPage,pPage->TotalInfo);
		break;
	}
	return;
}
void TurnPage(Page *pPage,Node *pHead)
{
	char c = 's';//记录输入是啥
	while(1)
	{
		switch (c)
		{
		case 's':
			if(pPage->CurrentPage >= pPage->TotalPage)
			{
				printf("已经是最后一页了\n");
			}
			else
			{
				pPage->CurrentPage++;
				ShowInfo(pHead,pPage);
				ShowMenu(pPage);
			}
			break;
		case 'w':
			if(pPage->CurrentPage <= 1)
			{
				printf("已经是第一页了\n");
			}
			else
			{
				pPage->CurrentPage--;
				ShowInfo(pHead,pPage);
				ShowMenu(pPage);
			}
			break;
		case 'b':
			return;
			break;
		case 'c':
			return;
			break;
		case 'd':
			return;
			break;
		case 'u':
			return;
			break;
		default:
			printf("按错了\n");
			break;
		}
		c = GetKey();
		g_Key = c;
	}
	return;
}
char GetKey()
{
	char c;
	char z;
	int flag = 1;
	while((c = getchar()) != '\n' || flag == 1)
	{
		z = c;
		flag = 0;
	}
	return z;
}
void Browse(Node *pHead)
{
	Page *pPage = GetPage(pHead,10);
	TurnPage(pPage,pHead);

	return;
}
Node* GetNodeIn()
{
	Node *pNode = (Node*)malloc(sizeof(Node));
	pNode->id = GetId();
	printf("请输入姓名:\n");
	pNode->name = GetString();
	printf("请输入电话:\n");
	pNode->tel = GetString();
	pNode->pNext = NULL;

	return pNode;
}
char *GetString()
{
	char c;
	int size = 5;
	int count = 0;
	char *str = (char*)malloc(size);
	char *pMark = str;
	char *newstr = NULL;

	while((c = getchar()) != '\n')
	{
		*str++ = c;
		count++;
		if(count+1 == size)
		{
			*str = '\0';
			size += 5;
			newstr = (char*)malloc(size);
			strcpy_s(newstr,size,pMark);
			free(pMark);
			pMark = newstr;
			str = newstr + count;
		}
	}
	*str = '\0';

	return pMark;
}
void Query(Node *pHead)
{
	Node *pNode = NULL;
	Node *pNewHead = NULL;
	Node *pNewEnd = NULL;
	Node *pMark = pHead;
	Node *pDel = NULL;
	char *pKeyWord = NULL;
	//1.输入关键字
	while(1)
	{
		while(1)
		{
			printf("请输入关键字:\n");
			pKeyWord = GetString();
			printf("a确认  按其他键重新输入\n");
			//确认   重新输入
			if(GetKey() == 'a')
			{
				break;
			}
			else
			{
				free(pKeyWord);//释放堆区GetKey
				pKeyWord = NULL;
			}
			
		}
		//printf("%s\n",pKeyWord);//测试好使不
		//2.在链表中去匹配输入的关键字    姓名和电话同时匹配   支持前缀模糊查找
			//遍历链表  
		pHead = pMark;
		while(pHead != NULL)
		{
			if(strncmp(pKeyWord,pHead->name,strlen(pKeyWord)) == 0 || strncmp(pKeyWord,pHead->tel,strlen(pKeyWord)) == 0)
			{
				//复制节点
				pNode = (Node*)malloc(sizeof(Node));
				pNode->id = pHead->id;
				pNode->name = pHead->name;//这里注意，只是查看可以直接指向堆区空间，别的操作（改变堆区值）需要再复制出一个空间
				pNode->tel = pHead->tel;
				pNode->pNext = NULL;//这里赋NULL；

				//建立新的链表
				AddNode(&pNewHead,&pNewEnd,pNode);
			}
			pHead = pHead->pNext;
		}
		//3.将查到匹配的复制下来添加到一个新链表  分页显示
		Browse(pNewHead);
		//4.重新查询  删除原来复制的节点
		while(pNewHead != NULL)
		{
			pDel = pNewHead;
			pNewHead = pNewHead->pNext;
			free(pDel);
			pDel = NULL;
		}
		//删除完之后链表全部删除掉了，pNewHead和pNewEnd不知道会不会变成NULL，所以赋NULL;
		pNewHead = NULL;
		pNewEnd = NULL;

		if('b' == g_Key || 'd' == g_Key || 'u' == g_Key)
		{
			break;
		}

	}
	return;
}
void DeleteNode(Node **ppHead,Node **ppEnd,int id)
{
	Node *pDel = NULL;
	Node *pMark = *ppHead;
	if((*ppHead)->id == id)
	{
		pDel = *ppHead;
		*ppHead = (*ppHead)->pNext;
		free(pDel->name);
		free(pDel->tel);
		free(pDel);
		pDel = NULL;
		return;
	}
	while(pMark->pNext != NULL)
	{
		if(pMark->pNext->id == id)
		{
			pDel = pMark->pNext;
			pMark->pNext = pMark->pNext->pNext;
			free(pDel->name);
			free(pDel->tel);
			free(pDel);
			pDel = NULL;	
			if(pMark->pNext == NULL)
			{
				*ppEnd = pMark;
			}
		}
		pMark = pMark->pNext;


	}

}
void DeleteInfo(Node **ppHead,Node **ppEnd)
{
	int id;
	char *str = NULL;
	while(1)
	{
		Query(*ppHead);

		if('b' == g_Key)
		{
			return;
		}

		printf("请输入要删除的编号:\n");
		//输入编号
		str = GetString();
		//转整形
		id = atoi(str);
		free(str);
		str = NULL;
		//删除节点
		DeleteNode(ppHead,ppEnd,id);
		//询问是否继续删除 y继续删除 其他键返回
		printf("y继续删除 其他键返回\n");
		if(GetKey() != 'y')
		{
			break;
		}
	}
}
void UpDataInfo(Node *pHead)
{
	int id;
	char *str = NULL;
	Query(pHead);

	if('b' == g_Key)
	{
		return;
	}

	printf("请输入要修改的编号:\n");

	//输入编号
	str = GetString();
	id = atoi(str);
	free(str);
	str = NULL;
	//遍历链表
	while(pHead != NULL)
	{
		//找到要修改的节点
		if(pHead->id == id)
		{
			//修改姓名
			printf("请输入姓名:\n");
			str = GetString();
			if(strlen(str) > 0)
			{
				free(pHead->name);
				pHead->name = str;
			}
			//修改电话
			printf("请输入电话:\n");
			str = GetString();
			if(strlen(str) > 0)
			{
				free(pHead->tel);
				pHead->tel = str;
			}
		}
		pHead = pHead->pNext;
	}
}