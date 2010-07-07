#include <windows.h>

#include "graffiti.h"
#include "graffiti_data.h"

static const bool DEBUG_DRAW_APPROXIMATION = false;

/** used for sending the recognized char */
static HWND clientWindow;

static PNormalizedLetter normalizedAlfa[PREDEFINED_LETTERS_SIZE];
static PNormalizedLetter normalizedNumber[PREDEFINED_NUMBER_SIZE];
static PRecognizer recognizer;

static HPEN grayPen = NULL;
static HPEN blackPen = NULL;
/**
 * Initialize Graffiti engine with letters and numbers data
 */
void InitializeGraffiti() {
	for (int i = 0; i < PREDEFINED_LETTERS_SIZE; i++) {
		normalizedAlfa[i] = new NormalizedLetter(refAlfa[i]);
	}
	for (int i = 0; i < PREDEFINED_NUMBER_SIZE; i++) {
		normalizedNumber[i] = new NormalizedLetter(refNumber[i]);
	}

	recognizer = new Recognizer(normalizedAlfa, PREDEFINED_LETTERS_SIZE, normalizedNumber, PREDEFINED_NUMBER_SIZE,
								DOT_CHARACTERS);

	grayPen = CreatePen(PS_SOLID, 1, 0xCCCCCC);
	blackPen = CreatePen(PS_SOLID, 1, 0);
}

/**
 * used to send a char code to a window
 */
void PostCharToWindow(CHAR ch) {
	if (IsWindow(clientWindow)) {
		SetFocus(clientWindow);
		PostMessage(clientWindow, WM_SETFOCUS, 0, 0);
		PostMessage(clientWindow, WM_CHAR, ch, 0x00001);
	}
}

static List<POINT> pointsRecorder(64, 64);

static int WIN_WIDTH = 260;
static int WIN_HEIGTH = 160;
static int WIN_TRESHOLD = WIN_WIDTH * 54 / 100;

static bool IN_LBUTTON_DRAG_MODE = false;

void doLButtonDown(HWND hwnd) {
	if (!GetCapture()) {
		SetCapture(hwnd);
		InvalidateRect(hwnd, NULL, TRUE);
		pointsRecorder.count = 0;
		IN_LBUTTON_DRAG_MODE = true;
	}
}

void doMouseMove(HWND hWnd, LPARAM lParam) {
	if (IN_LBUTTON_DRAG_MODE) {
		POINT point;
		point.x = (short) (lParam & 0xFFFF);
		point.y = (short) ((lParam >> 16) & 0xFFFF);

		pointsRecorder.add(&point);

		HDC dc = GetDC(hWnd);
		long len = pointsRecorder.count - 2;
		if (len >= 0) {
			SelectObject(dc, blackPen);
			MoveToEx(dc, pointsRecorder.list[len].x, pointsRecorder.list[len].y, NULL);
			LineTo(dc, point.x, point.y);
		}
		ReleaseDC(hWnd, dc);
	}
}

void doLButtonUp(HWND hwnd) {
	if (IN_LBUTTON_DRAG_MODE) {
		ReleaseCapture();
		IN_LBUTTON_DRAG_MODE = false;
	}

	char title[2];
	title[1] = 0;
	const char ch = recognizer->recognize(&pointsRecorder, WIN_TRESHOLD);
	title[0] = ch;
	SetWindowText(hwnd, title);
	if (ch) PostCharToWindow(ch);

	if (DEBUG_DRAW_APPROXIMATION) {
		HDC dc = GetDC(hwnd);
		//dump result on last recognition
		if (recognizer->lastFoundLetter) {
			//lastRecognizedIndex =
			for (int i = 0; i < INTERLIEVE_GRANULARITY; i++) {
				SetPixel(dc, i + 50, (int) (INTERLIEVE_GRANULARITY * (0.5
								+ recognizer->lastFoundLetter->letterxInterpol[i])), 0xCC0000);
				SetPixel(dc, i + 50 + INTERLIEVE_GRANULARITY + 20, (int) (INTERLIEVE_GRANULARITY * (0.5
								+ recognizer->lastFoundLetter->letteryInterpol[i])), 0xCC0000);
			}
		}
		if (recognizer->lastLetter) {
			for (int i = 0; i < INTERLIEVE_GRANULARITY; i++) {
				SetPixel(dc, i + 50,
							(int) (INTERLIEVE_GRANULARITY * (0.5 + recognizer->lastLetter->letterxInterpol[i])),
							0x0000CC);
				SetPixel(dc, i + 50 + INTERLIEVE_GRANULARITY + 20, (int) (INTERLIEVE_GRANULARITY * (0.5
								+ recognizer->lastLetter->letteryInterpol[i])), 0x0000CC);
			}
		}
		ReleaseDC(hwnd, dc);
	}
}

static bool IN_RBUTTON_DRAG_MODE = false;

void doRButtonDown(HWND hwnd) {
	if (!GetCapture()) {
		SetCapture(hwnd);
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		IN_RBUTTON_DRAG_MODE = true;
	}
}

void doRButtonUp(HWND hwnd) {
	if (IN_RBUTTON_DRAG_MODE) {
		DWORD dwPos;
		POINTS points;
		POINT point;
		dwPos = GetMessagePos();
		points = MAKEPOINTS(dwPos);
		point.x = points.x;
		point.y = points.y;

		clientWindow = WindowFromPoint(point);
		if (!IsWindow(clientWindow)) {
			clientWindow = NULL;
		} else {
			char title[40];
			wsprintf(title, "wnd: 0x%0.8X", clientWindow);
			SetWindowText(hwnd, title);
		}
		ReleaseCapture();
	}
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	IN_RBUTTON_DRAG_MODE = false;
}

void doWMPaint(HDC hDC) {

	SelectObject(hDC, grayPen);
	MoveToEx(hDC, WIN_TRESHOLD, 0, NULL);
	LineTo(hDC, WIN_TRESHOLD, WIN_HEIGTH);

	SetTextColor(hDC, 0xCCCCCC);
	TextOut(hDC, 2, WIN_HEIGTH - 20, "abc", 3);
	TextOut(hDC, WIN_WIDTH - 30, WIN_HEIGTH - 20, "123", 3);

}

void doResize(HWND hwnd) {
	RECT rect;
	GetClientRect(hwnd, &rect);
	WIN_WIDTH = rect.right;
	WIN_HEIGTH = rect.bottom;
	WIN_TRESHOLD = WIN_WIDTH * 54 / 100;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {

		case WM_PAINT: {
			HDC hDC;
			PAINTSTRUCT Ps;
			hDC = BeginPaint(hwnd, &Ps);
			doWMPaint(hDC);
			EndPaint(hwnd, &Ps);
		}
		break;

		case WM_LBUTTONDOWN:
			doLButtonDown(hwnd);
		break;

		case WM_MOUSEMOVE:
			doMouseMove(hwnd, lParam);
		break;

		case WM_LBUTTONUP:
			doLButtonUp(hwnd);
		break;

		case WM_RBUTTONDOWN:
			doRButtonDown(hwnd);
		break;

		case WM_RBUTTONUP:
			doRButtonUp(hwnd);
		break;

		case WM_SIZE:
			doResize(hwnd);
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, int nCmdShow) {
	static char * graffiti = "Graffiti";

	InitializeGraffiti();

	MSG msg;
	HWND hwnd;
	WNDCLASS wndClass;
	if (hPrevInstance == NULL) {
		memset(&wndClass, 0, sizeof(wndClass));
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WndProc;
		wndClass.hInstance = hInstance;
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
		wndClass.lpszClassName = graffiti;
		if (!RegisterClass(&wndClass)) return FALSE;
	}
	hwnd = CreateWindowEx(WS_EX_TOPMOST, graffiti, graffiti, WS_OVERLAPPED | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU
					| WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGTH, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
