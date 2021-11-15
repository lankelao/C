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

Node* GetNode();//1.������   ��ýڵ㣬����id�ڲ����ɣ�����������绰��������Բ��ò���
void AddNode(Node **ppHead,Node **ppEnd,Node *pNode);//2.�������  (ͷ   β    ��ӵ�˭)
int GetId();//3.�Զ����ɱ��
char* GetName();//4.�����绰ԭ�������ַ�����������������Ҫ������Ҫ���ڶ���
char* GetTel();//5.�绰
int main()
{
	Node *pHead = NULL;
	Node *pEnd = NULL;
    int i;

	srand((unsigned int)time(NULL));//��������������ӣ��������ֻ����һ�Σ�

	for(i=0;i<100;i++)//������
	{
		AddNode(&pHead,&pEnd,GetNode());
	}
	while(pHead != NULL)
	{
		printf("%d\t%s\t%s\n",pHead->id,pHead->name,pHead->tel);
		pHead = pHead->pNext;
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