//*****************************************************************************
//
// Main.cpp : Defines the entry point for the application.
// Used to read in a standard RGB image and display it.
// Two images are displayed on the screen.
// Left Pane: Input Image, Right Pane: Modified Image
//
// Author - Parag Havaldar
// Code used by students as a starter code to display and modify images
//
//*****************************************************************************


// Include class files
#include "Image.h"
#include <iostream>

#define MAX_LOADSTRING 100

// Global Variables:
MyImage			inImage, outImage;				// image objects
HINSTANCE		hInst;							// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// The title bar text

												// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


// Main entry point for a windows application
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;

	// Read in the image and its copy
	int w, h;
	char ImagePath[_MAX_PATH];
	int anti_alias;
	float scale;
	int no_of_lines;
	sscanf(lpCmdLine, "%d %f %d", &no_of_lines, &scale, &anti_alias);
	inImage.setWidth(512);
	inImage.setHeight(512);

	inImage.setImagePath(ImagePath);
	//outImage.setImagePath(ImagePath);
	if (!inImage.CreatImageCanv())
	{
		AfxMessageBox("Could not create image\nUsage - Image.exe image.rgb w h");
		//return FALSE;
	}
	else
	{
		int x = 511;
		int y = 0;
		int newx = 511, newy = 0;
		//no_of_lines = 16;
		float angle = (float)360 / no_of_lines;
		
		inImage.CreateLines(0, 0, 0, 511);
		inImage.CreateLines(0, 0, 511, 0);
		inImage.CreateLines(0, 511, 511, 511);
		inImage.CreateLines(511, 0, 511, 511);

		for (int i = 1; i < no_of_lines; i++)
		{
			int x1 = 256, y1 = 256, x2 = 511, y2 = 0;
			float angle_rad = (angle * 22.0) / (7.0 * 180);
			newx = 511; newy = 0;
			inImage.rotate_point(x1, y1, angle_rad, &newx, &newy);
			if (newx == 255)
			{
				newx = 256;
			}
			if (newy == 255)
			{
				newy = 256;
			}
			if (newx == 511)
			{
				newx = 512;
			}
			if (newy == 511)
			{
				newy = 512;
			}
			inImage.intersection(x1, y1, &newx, &newy, x2, y2, 511, 511, angle);
			if (newx == 255)
			{
				newx = 256;
			}
			if (newy == 255)
			{
				newy = 256;
			}
			inImage.CreateLines(x1, y1, newx, newy);
			angle += (float)360 / no_of_lines;
			
		}
		outImage.setWidth(512 / scale);
		outImage.setHeight(512 / scale);
		outImage.ScaleImage(inImage, scale, anti_alias);
		//outImage = inImage;
	}
	//}

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_IMAGE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_IMAGE);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_IMAGE);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = (LPCSTR)IDC_IMAGE;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}


//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// TO DO: part useful to render video frames, may place your own code here in this function
	// You are free to change the following code in any way in order to display the video

	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	RECT rt;
	GetClientRect(hWnd, &rt);

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case ID_MODIFY_IMAGE:
			outImage.Modify();
			InvalidateRect(hWnd, &rt, false);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		// TO DO: Add any drawing code here...
		char text[1000];
		strcpy(text, "Original image (Left)  Image after modification (Right)\n");
		DrawText(hdc, text, strlen(text), &rt, DT_LEFT);
		strcpy(text, "\nUpdate program with your code to modify input image");
		DrawText(hdc, text, strlen(text), &rt, DT_LEFT);

		BITMAPINFO bmi;
		CBitmap bitmap;
		memset(&bmi, 0, sizeof(bmi));
		bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
		bmi.bmiHeader.biWidth = inImage.getWidth();
		bmi.bmiHeader.biHeight = -inImage.getHeight();  // Use negative height.  DIB is top-down.
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = inImage.getWidth()*inImage.getHeight();

		SetDIBitsToDevice(hdc,
			0, 100, inImage.getWidth(), inImage.getHeight(),
			0, 0, 0, inImage.getHeight(),
			inImage.getImageData(), &bmi, DIB_RGB_COLORS);


		BITMAPINFO bmi1;
		CBitmap bitmap1;
		memset(&bmi1, 0, sizeof(bmi1));
		bmi1.bmiHeader.biSize = sizeof(bmi1.bmiHeader);
		bmi1.bmiHeader.biWidth = outImage.getWidth();
		bmi1.bmiHeader.biHeight = -outImage.getHeight();  // Use negative height.  DIB is top-down.
		bmi1.bmiHeader.biPlanes = 1;
		bmi1.bmiHeader.biBitCount = 24;
		bmi1.bmiHeader.biCompression = BI_RGB;
		bmi1.bmiHeader.biSizeImage = outImage.getWidth()*outImage.getHeight();


		SetDIBitsToDevice(hdc,
			inImage.getWidth() + 50, 100, outImage.getWidth(), outImage.getHeight(),
			0, 0, 0, outImage.getHeight(),
			outImage.getImageData(), &bmi1, DIB_RGB_COLORS);


		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}




// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}


