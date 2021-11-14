//#include <Windows.h>
//#include <stdio.h>
//
//LRESULT CALLBACK MyWNDPROC(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
//
//int CALLBACK WinMain(
//					 HINSTANCE hInstance,
//					 HINSTANCE hPrevInstance,
//					 LPSTR lpCmdLine,
//					 int nCmdShow
//					)
//{
//	HWND hWnd;
//	MSG Msg;
//	//1.设计窗口
//	WNDCLASSEX ex;
//	ex.style = CS_HREDRAW | CS_VREDRAW;
//	ex.cbSize = sizeof(ex);
//	ex.cbClsExtra = 0;
//	ex.cbWndExtra = 0;
//	ex.hInstance = hInstance;
//	ex.hIcon = NULL;
//	ex.hCursor = NULL;
//	ex.hbrBackground = CreateSolidBrush(RGB(0,255,0));
//	ex.hIconSm = NULL;
//	ex.lpfnWndProc = &MyWNDPROC;
//	ex.lpszMenuName = NULL;
//	ex.lpszClassName = "aa";
//	//2.注册窗口
//	RegisterClassEx(&ex);
//	//3.创建窗口
//	hWnd = CreateWindow(ex.lpszClassName,"当然选择原谅他",WS_OVERLAPPEDWINDOW,50,50,600,600,NULL,NULL,hInstance,NULL);
//	//4.显示窗口
//	ShowWindow(hWnd,SW_SHOW);
//
//	SetTimer(hWnd,1,500,NULL);
//	SetTimer(hWnd,2,200,NULL);
//
//	while(GetMessage(&Msg,NULL,0,0))
//	{
//		TranslateMessage(&Msg);
//		DispatchMessage(&Msg);
//	}
//
//	return 0;
//}
//
//LRESULT CALLBACK MyWNDPROC(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
//{
//	PAINTSTRUCT ps;
//	HDC hdc;
//	HBRUSH hBrush;
//	static int x_a = 50;
//	static int y_a = 50;
//	static int x_b = 50;
//	static int y_b = 150;
//	char str[20] = {0};
//	switch(message)
//	{
//	case WM_CLOSE:
//		PostQuitMessage(0);
//		break;
//	case WM_KEYDOWN:
//		/*if(65 == C)
//		{
//			MessageBox(hWnd,"要想生活过得去","温馨提示",MB_YESNO);
//		}*/
//
//		/*hdc = GetDC(hWnd);
//		hBrush = CreateSolidBrush(RGB(255,0,0));
//		SelectObject(hdc,hBrush);
//		Ellipse(hdc,50,50,350,350);
//		ReleaseDC(hWnd,hdc);*/
//
//		if(65 == wParam)
//		{
//			KillTimer(hWnd,1);
//		}
//
//		if(66 == wParam)
//		{
//			KillTimer(hWnd,2);
//		}
//		break;
//	case WM_LBUTTONDOWN:
//		/*x = LOWORD(lParam);
//		y = HIWORD(lParam);
//		
//		hdc = GetDC(hWnd);
//		Ellipse(hdc,x-15,y-15,x+15,y+15);
//		ReleaseDC(hWnd,hdc);*/
//
//		/*sprintf(str,"%d,%d",x,y);
//		MessageBox(hWnd,str,"温馨提示",MB_YESNO);*/
//		break;
//	case WM_PAINT:			//重绘消息
//		/*hdc = BeginPaint(hWnd,&ps);
//		Rectangle(hdc,50,50,350,350);
//		EndPaint(hWnd,&ps);*/
//		break;
//	case WM_TIMER:
//		//MessageBox(hWnd,"你傻啊","温馨提示",MB_OK);
//		hdc = GetDC(hWnd);
//		if(1 == wParam)
//		{
//			x_a += 5;
//			Rectangle(hdc,x_a,y_a,x_a+50,y_a+50);
//		}
//
//		if(2 == wParam)
//		{
//			x_b += 5;
//			Rectangle(hdc,x_b,y_b,x_b+50,y_b+50);
//		}
//		
//		ReleaseDC(hWnd,hdc);
//		break;
//	}
//
//	return DefWindowProc(hWnd,message,wParam,lParam);
//}