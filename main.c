��ʱ��
#include<Windows.h>
#include<stdio.h>
LRESULT CALLBACK MyWNDPROC(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam);
int CALLBACK WinMain(HINSTANCE hInstance,//������Է����ڴ棬�����޸�
					 HINSTANCE hPrevInstance, //Ӧ�ó���ǰһ��ʵ�����������ʵ��֮��û��Ӱ��
					 LPSTR lpCmdLine, //�����в���
					 int nCmdShow//
					 )
{
	HWND hWnd;
	MSG Msg;
	//1.��ƴ���
	WNDCLASSEX ex;
	ex.style = CS_HREDRAW | CS_VREDRAW;//ˮƽ�ʹ�ֱˢ��
	ex.cbSize = sizeof(ex); //��ǰ�ṹ���С
	ex.cbClsExtra = 0;
	ex.cbWndExtra = 0;
	ex.hInstance = hInstance;
	ex.hIcon = NULL;
	ex.hCursor = NULL;
	ex.hbrBackground =CreateSolidBrush(RGB(0,255,0));  //ָ��������ˢ���
	ex.hIconSm = NULL;//���Ͻ�Сͼ��
	ex.lpfnWndProc = &MyWNDPROC;//��Ҫ
	ex.lpszMenuName = NULL;
	ex.lpszClassName = "aaa";
	//2.ע�ᴰ��
	RegisterClassEx(&ex);
	//3.��������
	hWnd = CreateWindow(ex.lpszClassName,"��Ȼѡ��ԭ����",WS_OVERLAPPEDWINDOW,50,50,600,600,NULL,NULL,hInstance,NULL);
	//4.��ʾ����
	ShowWindow(hWnd,SW_SHOW);
	//���ö�ʱ��
	SetTimer(hWnd,1,500,NULL);

	while(GetMessage(&Msg,NULL,0,0))//�Դ��ڲ�ͣ��ȡ��Ϣ
	{
		TranslateMessage(&Msg);//����
		DispatchMessage(&Msg);//�ַ�
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
			MessageBox(hWnd,"Ҫ���������ȥ","��ϰ��ʾ",MB_YESNO);
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
		MessageBox(hWnd,str,"��ϰ��ʾ",MB_YESNO);*/
		break;
	case WM_PAINT:   //�ػ�
		/*hdc = BeginPaint(hWnd,&ps);
		Rectangle(hdc,50,50,350,350);
		EndPaint(hWnd,&ps);*/
		break;
	case WM_TIMER:
		x_a += 5;
		x_b += 10;
		hdc = GetDC(hWnd);
		/*MessageBox(hWnd,"��ɵ��","Ҫ���������ȥ",MB_OK);*/
		Rectangle(hdc,x_a,y_a,x_a+50,y_a+50);
		Rectangle(hdc,x_b,y_b,x_b+50,y_b+50);
		ReleaseDC(hWnd,hdc);
		break;
	}
	return DefWindowProc(hWnd,message,wParam,lparam);
}