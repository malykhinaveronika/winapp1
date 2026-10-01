
#include <windows.h>
#include <cmath>
#include <string>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Variant11";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc))
        return 0;

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Variant 11",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 900, 650,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hwnd)
        return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

void DrawTextAt(HDC hdc, int x, int y, const wchar_t* text)
{
    TextOut(hdc, x, y, text, lstrlen(text));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT rect;
        GetClientRect(hwnd, &rect);

        int width = rect.right;
        int height = rect.bottom;

        int left = 90;
        int right = width - 50;
        int top = 60;
        int bottom = height - 80;

        FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

        SetBkMode(hdc, TRANSPARENT);
        DrawTextAt(hdc, left, 15,
            L"Variant 11: y = sqrt(sin^2(x) + cos^2(x))");

        HPEN axisPen = CreatePen(PS_SOLID, 2, RGB(30, 30, 30));
        HPEN oldPen = (HPEN)SelectObject(hdc, axisPen);

        int yZero = bottom;
        int xZero = left;

        MoveToEx(hdc, left, top, nullptr);
        LineTo(hdc, left, bottom);
        MoveToEx(hdc, left, yZero, nullptr);
        LineTo(hdc, right, yZero);

        MoveToEx(hdc, right, yZero, nullptr);
        LineTo(hdc, right - 10, yZero - 5);
        MoveToEx(hdc, right, yZero, nullptr);
        LineTo(hdc, right - 10, yZero + 5);

        MoveToEx(hdc, left, top, nullptr);
        LineTo(hdc, left - 5, top + 10);
        MoveToEx(hdc, left, top, nullptr);
        LineTo(hdc, left + 5, top + 10);

        SelectObject(hdc, oldPen);
        DeleteObject(axisPen);

        auto screenX = [&](double x) {
            return left + (int)(x / 3.0 * (right - left));
            };

        auto screenY = [&](double y) {
            return bottom - (int)(y / 2.0 * (bottom - top));
            };

        for (int i = 0; i <= 6; i++)
        {
            double x = i * 0.5;
            int px = screenX(x);

            MoveToEx(hdc, px, yZero - 4, nullptr);
            LineTo(hdc, px, yZero + 4);

            wchar_t label[20];
            swprintf_s(label, L"%.1f", x);
            DrawTextAt(hdc, px - 12, yZero + 10, label);
        }

        for (int i = 0; i <= 4; i++)
        {
            double y = i * 0.5;
            int py = screenY(y);

            MoveToEx(hdc, xZero - 4, py, nullptr);
            LineTo(hdc, xZero + 4, py);

            wchar_t label[20];
            swprintf_s(label, L"%.1f", y);
            DrawTextAt(hdc, xZero - 42, py - 8, label);
        }

        DrawTextAt(hdc, right + 12, yZero - 20, L"X");
        DrawTextAt(hdc, left - 25, top - 20, L"Y");


        HPEN graphPen = CreatePen(PS_SOLID, 3, RGB(220, 40, 40));
        oldPen = (HPEN)SelectObject(hdc, graphPen);

        bool first = true;
        for (int i = 0; i <= 300; i++)
        {
            double x = 3.0 * i / 300.0;
            double y = sqrt(pow(sin(x), 2) + pow(cos(x), 2));

            int px = screenX(x);
            int py = screenY(y);

            if (first)
            {
                MoveToEx(hdc, px, py, nullptr);
                first = false;
            }
            else
            {
                LineTo(hdc, px, py);
            }
        }

        SelectObject(hdc, oldPen);
        DeleteObject(graphPen);

        DrawTextAt(hdc, left + 10, top + 10,
            L"y = 1");

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_SIZE:
        InvalidateRect(hwnd, nullptr, TRUE);
        return 0;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            DestroyWindow(hwnd);
        return 0;

    case WM_LBUTTONDOWN:
        MessageBox(hwnd, L"Function graph: Variant 11",
            L"Information", MB_OK | MB_ICONINFORMATION);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}