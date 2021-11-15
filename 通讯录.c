#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct NODE
{
	int id;
	char *name;
	char *tel;
	struct NODE *pNext;//��������������Ҫ��ͷβָ��
}Node;

typedef struct PAGE
{
	int TotalInfo; //������
	int TotalPage;  //��ҳ��
	int CurrentPage;  //��ǰҳ
	int OnePageInfo; //ÿҳ��ʾ������
}Page;

int g_menu_type;//Ϊ�����²�ѯ��ť
char g_Key; //��b���ز��ˣ�����Ӧ���ô�����������ɶ�������Ѷ���ȫ�ֱ���

Node* GetNode();//1.������   ��ýڵ㣬����id�ڲ����ɣ�����������绰��������Բ��ò���
void AddNode(Node **ppHead,Node **ppEnd,Node *pNode);//2.�������  (ͷ   β    ��ӵ�˭)
int GetId();//3.�Զ����ɱ��
char* GetName();//4.�����绰ԭ�������ַ�����������������Ҫ������Ҫ���ڶ���
char* GetTel();//5.�绰
void InitInfo(Node **ppHead,Node **ppEnd,int n);//6.��ʼ������ ȥ����������
Page* GetPage(Node *pHead,int n);//7.
void ShowInfo(Node *pHead,Page *pPage);//8.��ʾ��ҳ��Ϣ
void ShowMenu(Page *pPage);//9.��ʾ�˵�
void TurnPage(Page *pPage,Node *pHead);//10.��ҳ
char GetKey();//11.ȥ���س�'\n'�����Ĵ���
void Browse(Node *pHead);//12.�Ѳ鿴���ܷ�װ����
Node* GetNodeIn(); //13.���ͨѶ¼
char *GetString();//14.������ֺ͵绰
void Query(Node *pHead);//15.��ѯͨѶ¼

int main()
{
	Node *pHead = NULL;
	Node *pEnd = NULL;
	char c;

	InitInfo(&pHead,&pEnd,101);


	while(1)
	{
		printf("1.�鿴ͨѶ¼\n");
		printf("2.�����Ϣ\n");
		printf("3.��ѯ��Ϣ\n");
		printf("4.ɾ����Ϣ\n");
		printf("5.�޸���Ϣ\n");
		printf("q.�˳�\n");

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
		case 'q':
			return;
			break;
		}
	}
	return 0;
}
Node* GetNode()
{
	Node *pNode = (Node*)malloc(sizeof(Node));//��������ռ䣬���������Ե���
	//pNode->id = 1; //�ȸ�1�������ٸ�
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
	static int id = 1;//��Ҫ��̬���ֲ�����,�ֲ�ÿ�ζ��������ͷ�
	return id++;//id++��һ�η���1��idֵ��2��û������
}
char* GetName()
{
	char *pName = (char*)malloc(sizeof(char)*6);//���ֿ���6���ַ��Ŀռ�
	 int i;
	 for(i=0;i<5;i++)
	 {
		 pName[i] = rand()%26 + 'a';//rand�������ȡa--z�ַ�������
	 }
	 pName[i] = '\0';

	 return pName;
}
char* GetTel()
{
	char *pTel = (char*)malloc(sizeof(char)*12);//11λ����
	int i;
	switch (rand()%4)//ȡ�ĸ�����Ŷ�
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
void InitInfo(Node **ppHead,Node **ppEnd,int n)//ppHead��ľ���pHead�ĵ�ַ,��ʼ��n��
{
	int i;
	srand((unsigned int)time(NULL));//��������������ӣ��������ֻ����һ�Σ�
	for(i=0;i<n;i++)//������
	{
		AddNode(ppHead,ppEnd,GetNode());
	}
}
Page* GetPage(Node *pHead,int n)
{
	//1.���ṹ������ռ�
	Page *pPage = (Page*)malloc(sizeof(Page));
	pPage->CurrentPage = 0;
	pPage->OnePageInfo = n;
	pPage->TotalInfo = 0;
	//2.ͨ������ѽṹ�����ֵ������
	while(pHead != NULL)//ֻ�Ǳ�������ֵ���ݣ�����ֻ��ҪNode*pHead
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
		printf("��ǰ��%dҳ  ��%dҳ  ��%d��  w��һҳ  s��һҳ  b����\n",pPage->CurrentPage,pPage->TotalPage,pPage->TotalInfo);
		break;
	case 3:
		printf("��ǰ��%dҳ  ��%dҳ  ��%d��  w��һҳ  s��һҳ  c���²�ѯ  b����\n",pPage->CurrentPage,pPage->TotalPage,pPage->TotalInfo);
		break;
	}
	return;
}
void TurnPage(Page *pPage,Node *pHead)
{
	char c = 's';//��¼������ɶ
	while(1)
	{
		switch (c)
		{
		case 's':
			if(pPage->CurrentPage >= pPage->TotalPage)
			{
				printf("�Ѿ������һҳ��\n");
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
				printf("�Ѿ��ǵ�һҳ��\n");
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
		default:
			printf("������\n");
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
	printf("����������:\n");
	pNode->name = GetString();
	printf("������绰:\n");
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
	//1.����ؼ���
	while(1)
	{
		while(1)
		{
			printf("������ؼ���:\n");
			pKeyWord = GetString();
			printf("aȷ��  ����������������\n");
			//ȷ��   ��������
			if(GetKey() == 'a')
			{
				break;
			}
			else
			{
				free(pKeyWord);//�ͷŶ���GetKey
				pKeyWord = NULL;
			}
			
		}
		//printf("%s\n",pKeyWord);//���Ժ�ʹ��
		//2.��������ȥƥ������Ĺؼ���    �����͵绰ͬʱƥ��   ֧��ǰ׺ģ������
			//��������  
		pHead = pMark;
		while(pHead != NULL)
		{
			if(strncmp(pKeyWord,pHead->name,strlen(pKeyWord)) == 0 || strncmp(pKeyWord,pHead->tel,strlen(pKeyWord)) == 0)
			{
				//���ƽڵ�
				pNode = (Node*)malloc(sizeof(Node));
				pNode->id = pHead->id;
				pNode->name = pHead->name;//����ע�⣬ֻ�ǲ鿴����ֱ��ָ������ռ䣬��Ĳ������ı����ֵ����Ҫ�ٸ��Ƴ�һ���ռ�
				pNode->tel = pHead->tel;
				pNode->pNext = NULL;//���︳NULL��

				//�����µ�����
				AddNode(&pNewHead,&pNewEnd,pNode);
			}
			pHead = pHead->pNext;
		}
		//3.���鵽ƥ��ĸ���������ӵ�һ��������  ��ҳ��ʾ
		Browse(pNewHead);
		//4.���²�ѯ  ɾ��ԭ�����ƵĽڵ�
		while(pNewHead != NULL)
		{
			pDel = pNewHead;
			pNewHead = pNewHead->pNext;
			free(pDel);
			pDel = NULL;
		}
		//ɾ����֮������ȫ��ɾ�����ˣ�pNewHead��pNewEnd��֪���᲻����NULL�����Ը�NULL;
		pNewHead = NULL;
		pNewEnd = NULL;

		if('b' == g_Key)
		{
			break;
		}

	}
	return;
}