定时器
#include<Windows.h>
#include<stdio.h>
LRESULT CALLBACK MyWNDPROC(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam);
int CALLBACK WinMain(HINSTANCE hInstance,//句柄可以访问内存，不能修改
					 HINSTANCE hPrevInstance, //应用程序前一个实例句柄，两个实例之间没有影响
					 LPSTR lpCmdLine, //命令行参数
					 int nCmdShow//
					 )
{
	HWND hWnd;
	MSG Msg;
	//1.设计窗口
	WNDCLASSEX ex;
	ex.style = CS_HREDRAW | CS_VREDRAW;//水平和垂直刷新
	ex.cbSize = sizeof(ex); //当前结构体大小
	ex.cbClsExtra = 0;
	ex.cbWndExtra = 0;
	ex.hInstance = hInstance;
	ex.hIcon = NULL;
	ex.hCursor = NULL;
	ex.hbrBackground =CreateSolidBrush(RGB(0,255,0));  //指定背景画刷句柄
	ex.hIconSm = NULL;//左上角小图标
	ex.lpfnWndProc = &MyWNDPROC;//重要
	ex.lpszMenuName = NULL;
	ex.lpszClassName = "aaa";
	//2.注册窗口
	RegisterClassEx(&ex);
	//3.创建窗口
	hWnd = CreateWindow(ex.lpszClassName,"当然选择原谅他",WS_OVERLAPPEDWINDOW,50,50,600,600,NULL,NULL,hInstance,NULL);
	//4.显示窗口
	ShowWindow(hWnd,SW_SHOW);
	//设置定时器
	SetTimer(hWnd,1,500,NULL);

	while(GetMessage(&Msg,NULL,0,0))//对窗口不停获取消息
	{
		TranslateMessage(&Msg);//翻译
		DispatchMessage(&Msg);//分发
	}
	return 0;
}
LRESULT CALLBACK MyWNDPROC(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH hBrush;
	static int x_a = 50;
	static int y_a = 50;
	static int x_b = 50;
	static int y_b = 150;
	char str[20] = {0};
	switch(message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		/*if(65 == wParam)
		{
			MessageBox(hWnd,"要想生活过的去","温习提示",MB_YESNO);
		}*/
		/*hdc = GetDC(hWnd);
		hBrush = CreateSolidBrush(RGB(255,0,0));
		SelectObject(hdc,hBrush);
		Ellipse(hdc,50,50,350,350);
		ReleaseDC(hWnd,hdc);*/
		break;
	case WM_LBUTTONDOWN:
		/*x = LOWORD(lparam);
		y = HIWORD(lparam);

		hdc = GetDC(hWnd);
		Ellipse(hdc,x-15,y-15,x+15,y+15);
		ReleaseDC(hWnd,hdc);*/
		/*sprintf(str,"%d %d",x,y);
		MessageBox(hWnd,str,"温习提示",MB_YESNO);*/
		break;
	case WM_PAINT:   //重绘
		/*hdc = BeginPaint(hWnd,&ps);
		Rectangle(hdc,50,50,350,350);
		EndPaint(hWnd,&ps);*/
		break;
	case WM_TIMER:
		x_a += 5;
		x_b += 10;
		hdc = GetDC(hWnd);
		/*MessageBox(hWnd,"你傻啊","要想生活过得去",MB_OK);*/
		Rectangle(hdc,x_a,y_a,x_a+50,y_a+50);
		Rectangle(hdc,x_b,y_b,x_b+50,y_b+50);
		ReleaseDC(hWnd,hdc);
		break;
	}
	return DefWindowProc(hWnd,message,wParam,lparam);
}