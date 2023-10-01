#include <Windows.h>
#include <windowsx.h>
#include "Circle.h"

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure);
LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASS mainWindow = createWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", windowProcedure);

	if (!RegisterClassW(&mainWindow))
		return -1;

	CreateWindow(L"MainWndClass", L"MainWindow", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 800, NULL, NULL, NULL, NULL);

	MSG message = { 0 };
	while (GetMessage(&message, NULL, NULL, NULL)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure)
{
	WNDCLASS wc = { 0 };

	wc.hCursor = cursor;
	wc.hIcon = icon;
	wc.hInstance = hInstance;
	wc.lpszClassName = windowName;
	wc.hbrBackground = bgColor;
	wc.lpfnWndProc = windowProcedure;

	return wc;
}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc = NULL;
    static Circle myCircle(100, 400, 400, RGB(255, 127, 127));
    static int lastX, lastY;
    switch (msg)
    {
    case WM_CREATE:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        myCircle.draw(hdc);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
        lastX = GET_X_LPARAM(lp);
        lastY = GET_Y_LPARAM(lp);
        myCircle.startDragging(lastX, lastY);
        break;
    case WM_LBUTTONUP:
        myCircle.stopDragging(GET_X_LPARAM(lp), GET_Y_LPARAM(lp));
        break;
    case WM_MOUSEMOVE:
        if (myCircle.isDragging()) {
            myCircle.drag(GET_X_LPARAM(lp), GET_Y_LPARAM(lp));
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_RBUTTONDOWN:
        myCircle.moveTo(GET_X_LPARAM(lp), GET_Y_LPARAM(lp));
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    default:
        return DefWindowProc(hWnd, msg, wp, lp);
    }
    return 0;
}
