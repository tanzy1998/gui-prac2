#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <conio.h>

#pragma comment (lib, "OpenGL32.lib")
int page = 0;
float points[4][2] = {
	{ -0.1f, 0.1f },{ 0.1f, 0.1f },{ 0.1f, -0.1f },{ -0.1f, -0.1f }
};
#define WINDOW_TITLE "Practical 2"
float x = 0.0, y = 0.0;
float r = 1, g = 1, b = 1;
float x1 = 0.5, deg = 0;
void moveTriangle();
void diamond();
void dotLine();
void redRectangle();

void drawDiamond(float angle);
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CHAR:
		switch (wParam)
		{
		case 0x72:
			r = 1.0f;
			g = 0;
			b = 0;
			break;
		case 0x67:
			r = 0;
			g = 1.0f;
			b = 0;
			break;
		case 0x62:
			r = 0;
			g = 0;
			b = 1.0f;
			break;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_LEFT:
			glTranslatef(-0.1, 0, 0);
			break;
		case VK_RIGHT:
			glTranslatef(0.1, 0, 0);
			break;
		case VK_DOWN:
			glTranslatef(0, -0.1, 0);
			break;
		case VK_UP:
			glTranslatef(0, 0.1, 0);
			break;
		case VK_SPACE:
			glLoadIdentity();
			r = 1.0f;
			g = 1.0f;
			b = 1.0f;
			break;

		case VK_F1:
			page = 1;
			break;
		case VK_F2:
			page = 2;
			break;
		case VK_F3:
			page = 3;
			break;
		case VK_F4:
			page = 4;
			break;
		}
		break;
	
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void moveTriangle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(r, g, b);
	
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
}

void drawDiamond(float angle) {
	glPushMatrix();
	glRotatef(angle, 0, 0, 1);
	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(0, 0);
	glColor3ub(rand() % 85, rand() % 85, rand() % 85);
	glVertex2f(-0.11, 0.15);
	glColor3ub(rand() % 170, rand() % 170, rand() % 170);
	glVertex2f(0.0, 0.5);
	glColor3ub(rand() % 255, rand() % 255, rand() % 255);
	glVertex2f(0.11, 0.15);

	glEnd();
	glPopMatrix();
}

void diamond() {
	drawDiamond(0);
	drawDiamond(72);
	drawDiamond(144);
	drawDiamond(216);
	drawDiamond(288);
}

void dotLine() {
	x1 = 0 + (0.5 * cos(deg));
	y = 0 + (0.5 * sin(deg));
	deg += 0.001f;

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 0, 0);

	glPointSize(5); // <--- Set Dot Size
	glBegin(GL_POINTS);

	glVertex2f(x1, y);

	glEnd();
}

void redRectangle() {
	glColor3f(1, 0, 0);

	glBegin(GL_QUADS);

	glVertex2f(points[0][0], points[0][1]);
	glVertex2f(points[1][0], points[1][1]);
	glVertex2f(points[2][0], points[2][1]);
	glVertex2f(points[3][0], points[3][1]);

	glEnd();

	if (points[1][0] <= 0.95)
	{
		points[0][0] *= 1.001f;
		points[0][1] *= 1.001f;
		points[1][0] *= 1.001f;
		points[1][1] *= 1.001f;
		points[2][0] *= 1.001f;
		points[2][1] *= 1.001f;
		points[3][0] *= 1.001f;
		points[3][1] *= 1.001f;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch (page)
	{
	case 1: 
		moveTriangle();
		break;
	case 2:
		diamond();
		break;
	case 3:
		dotLine();
		break;
	case 4:
		redRectangle();
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevInstance,
	_In_ LPSTR cmdLine, _In_ int nCmdShow) // FIXED
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------