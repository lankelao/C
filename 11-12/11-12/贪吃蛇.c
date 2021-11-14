#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include "resource.h"

LRESULT CALLBACK MyWNDPROC(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

typedef struct NODE
{
	int x;
	int y;
	struct NODE *pNext;
	struct NODE *pLast;
}Snake,Apple;

enum Direction {UP,DOWN,LEFT,RIGHT};

HBITMAP hBitmap_Background;
HBITMAP hBitmap_Apple;
HBITMAP hBitmap_SnakeBody;
HBITMAP hBitmap_SnakeHead_Up;
HBITMAP hBitmap_SnakeHead_Down;
HBITMAP hBitmap_SnakeHead_Left;
HBITMAP hBitmap_SnakeHead_Right;

Snake *pHead = NULL;
Snake *pTail = NULL;
enum Direction fx = UP;
Apple apple = {5,5,NULL,NULL};
BOOL bFlag = TRUE;

void AddNode(int x,int y);
void ShowBackground(HDC hdc);
void ShowSnake(HDC hdc);
void Move();
void ShowApple(HDC hdc);
BOOL IsEatApple();
void NewApple();
BOOL IsBumpWall();
BOOL IsEatItself();

int CALLBACK WinMain(
					 HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int nCmdShow
					)
{
	HWND hWnd;
	MSG Msg;
	int i;
	//1.设计窗口
	WNDCLASSEX ex;
	ex.style = CS_HREDRAW | CS_VREDRAW;
	ex.cbSize = sizeof(ex);
	ex.cbClsExtra = 0;
	ex.cbWndExtra = 0;
	ex.hInstance = hInstance;
	ex.hIcon = NULL;
	ex.hCursor = NULL;
	ex.hbrBackground = CreateSolidBrush(RGB(0,255,0));
	ex.hIconSm = NULL;
	ex.lpfnWndProc = &MyWNDPROC;
	ex.lpszMenuName = NULL;
	ex.lpszClassName = "aa";
	//2.注册窗口
	RegisterClassEx(&ex);
	//3.创建窗口
	hWnd = CreateWindow(ex.lpszClassName,"贪吃蛇",WS_OVERLAPPEDWINDOW,50,50,615,638,NULL,NULL,hInstance,NULL);
	//4.显示窗口
	ShowWindow(hWnd,SW_SHOW);

	//加载位图      把图片加载到内存
	hBitmap_Background = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP1));
	hBitmap_Apple= LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP2));
	hBitmap_SnakeBody = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP3));
	hBitmap_SnakeHead_Up = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP5));
	hBitmap_SnakeHead_Down = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP7));
	hBitmap_SnakeHead_Left = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP6));
	hBitmap_SnakeHead_Right = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP4));

	for(i=0;i<1000;i++)
	{
		AddNode(3,3);
		AddNode(3,4);
		AddNode(3,5);
	}

	SetTimer(hWnd,1,200,NULL);

	srand((unsigned int)time(NULL));

	while(GetMessage(&Msg,NULL,0,0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}

LRESULT CALLBACK MyWNDPROC(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch(message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if(bFlag == TRUE)
		{
			if(wParam == VK_UP)
			{
				if(fx != DOWN)
				{
					fx = UP;
				}	
			}
			if(wParam == VK_DOWN)
			{
				if(fx != UP)
				{
					fx = DOWN;
				}
			}
			if(wParam == VK_LEFT)
			{
				if(fx != RIGHT)
				{
					fx = LEFT;
				}
			}if(wParam == VK_RIGHT)
			{
				if(fx != LEFT)
				{
					fx = RIGHT;
				}
			}

			bFlag = FALSE;
		}
		/*hdc = GetDC(hWnd);
		ShowSnake(hdc);
		ReleaseDC(hWnd,hdc);*/

		break;
	case WM_PAINT:			//重绘消息
		hdc = BeginPaint(hWnd,&ps);
		
		//1.显示背景
		ShowBackground(hdc);
		//2.显示蛇
		ShowSnake(hdc);
		//3.显示苹果
		ShowApple(hdc);
		EndPaint(hWnd,&ps);
		break;
	case WM_TIMER:
		hdc = GetDC(hWnd);
		//爬
		Move();

		//判断游戏是否结束   撞墙  自咬
		//if(IsBumpWall() || IsEatItself())
		//{
		//	//游戏结束
		//	KillTimer(hWnd,1);
		//	MessageBox(hWnd,"游戏结束","提示",MB_OK);
		//	
		//}
		//判断是否吃到苹果  
		if(IsEatApple())
		{
			//长个
			AddNode(-10,-10);
			//来个新苹果
			NewApple();
		}
		//显示背景
		ShowBackground(hdc);
		//显示蛇
		ShowSnake(hdc);
		//显示苹果
		ShowApple(hdc);
		ReleaseDC(hWnd,hdc);

		bFlag = TRUE;
		break;
	}



	return DefWindowProc(hWnd,message,wParam,lParam);
}

BOOL IsEatItself()
{
	Snake *pMark = pHead->pNext;

	while(pMark != NULL)
	{
		if(pMark->x == pHead->x && pMark->y == pHead->y)
		{
			return TRUE;
		}
		pMark = pMark->pNext;
	}

	return FALSE;
}

BOOL IsBumpWall()
{
	if(pHead->x == 0 || pHead->x == 19 || pHead->y == 0 || pHead->y == 19)
	{
		return TRUE;
	}

	return FALSE;
}

void NewApple()
{
	int x;
	int y;
	Snake *pMark = pHead;

	do
	{
		x = rand() % 18 + 1;
		y = rand() % 18 + 1;

		pMark = pHead;
		while(pMark != NULL)
		{
			if(x == pMark->x && y == pMark->y)
			{
				break;
			}
			pMark = pMark->pNext;
		}
	}while(pMark != NULL);
	apple.x = x;
	apple.y = y;

	return;
}

BOOL IsEatApple()
{
	if(pHead->x == apple.x && pHead->y == apple.y)
	{
		return TRUE;
	}

	return FALSE;
}

void ShowApple(HDC hdc)
{
	HDC menhdc = CreateCompatibleDC(hdc);
	SelectObject(menhdc,hBitmap_Apple);
	BitBlt(hdc,apple.x*30,apple.y*30,30,30,menhdc,0,0,SRCCOPY);
	DeleteDC(menhdc);

	return;
}

void Move()
{
	Snake *pMark = pTail;
	//1.移动蛇身
	while(pMark != pHead)
	{
		pMark->x = pMark->pLast->x;
		pMark->y = pMark->pLast->y;
		pMark = pMark->pLast;
	}
	//2.移动蛇头
	switch (fx)
	{
	case UP:
		pHead->y--;
		break;
	case DOWN:
		pHead->y++;
		break;
	case LEFT:
		pHead->x--;
		break;
	case RIGHT:
		pHead->x++;
		break;
	default:
		break;
	}

	return;
}

void ShowBackground(HDC hdc)
{
	//1.创建兼容性dc  为窗口设备创建
	HDC menhdc = CreateCompatibleDC(hdc);
	//2.选择一张位图
	SelectObject(menhdc,hBitmap_Background);
	//3.传输
	BitBlt(hdc,0,0,600,600,menhdc,0,0,SRCCOPY);
	//4.删除兼容性dc
	DeleteDC(menhdc);

	return;
}

void ShowSnake(HDC hdc)
{
	Snake *pMark = pHead->pNext;
	HDC menhdc = CreateCompatibleDC(hdc);
	//显示蛇头
	switch (fx)
	{
	case UP:
		SelectObject(menhdc,hBitmap_SnakeHead_Up);
		break;
	case DOWN:
		SelectObject(menhdc,hBitmap_SnakeHead_Down);
		break;
	case LEFT:
		SelectObject(menhdc,hBitmap_SnakeHead_Left);
		break;
	case RIGHT:
		SelectObject(menhdc,hBitmap_SnakeHead_Right);
		break;
	default:
		break;
	}
	
	BitBlt(hdc,pHead->x*30,pHead->y*30,30,30,menhdc,0,0,SRCCOPY);
	//显示蛇身
	SelectObject(menhdc,hBitmap_SnakeBody);
	while(pMark != NULL)
	{
		BitBlt(hdc,pMark->x*30,pMark->y*30,30,30,menhdc,0,0,SRCCOPY);
		pMark = pMark->pNext;
	}

	DeleteDC(menhdc);

	return;
}

void AddNode(int x,int y)
{
	Snake *pNode = (Snake*)malloc(sizeof(Snake));
	pNode->x = x;
	pNode->y = y;
	pNode->pNext = NULL;
	pNode->pLast = NULL;
	
	if(pHead == NULL)
	{
		pHead = pNode;
	}
	else
	{
		pTail->pNext = pNode;
		pNode->pLast = pTail;
	}
	pTail = pNode;

	return;
}