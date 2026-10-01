
#include <windows.h>
#include <cmath>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void FillEllipse(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
    HBRUSH brush = CreateSolidBrush(color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

    HPEN pen = CreatePen(PS_SOLID, 1, color);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);

    Ellipse(hdc, x1, y1, x2, y2);

    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);
    DeleteObject(brush);
    DeleteObject(pen);
}

void FillRectangle(HDC hdc, int x1, int y1, int x2, int y2,
    COLORREF color)
{
    HBRUSH brush = CreateSolidBrush(color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

    HPEN pen = CreatePen(PS_SOLID, 1, color);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);

    Rectangle(hdc, x1, y1, x2, y2);

    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);
    DeleteObject(brush);
    DeleteObject(pen);
}

class Cloud
{
public:
    void Draw(HDC hdc, int x, int y)
    {
        COLORREF white = RGB(255, 255, 255);

        FillEllipse(hdc, x, y + 15, x + 55, y + 55, white);
        FillEllipse(hdc, x + 25, y, x + 80, y + 50, white);
        FillEllipse(hdc, x + 55, y + 15, x + 105, y + 55, white);
        FillEllipse(hdc, x + 20, y + 25, x + 85, y + 60, white);
    }
};

class Sun
{
public:
    void Draw(HDC hdc, int x, int y)
    {
        HPEN pen = CreatePen(PS_SOLID, 4, RGB(255, 170, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, pen);

        for (int i = 0; i < 8; i++)
        {
            double angle = i * 3.14159265 / 4.0;
            int x1 = x + (int)(48 * cos(angle));
            int y1 = y + (int)(48 * sin(angle));
            int x2 = x + (int)(65 * cos(angle));
            int y2 = y + (int)(65 * sin(angle));

            MoveToEx(hdc, x1, y1, nullptr);
            LineTo(hdc, x2, y2);
        }

        SelectObject(hdc, oldPen);
        DeleteObject(pen);

        FillEllipse(hdc, x - 38, y - 38, x + 38, y + 38,
            RGB(255, 220, 0));
    }
};

class Lighthouse
{
public:
    void Draw(HDC hdc, int x, int y)
    {
        POINT tower[] = {
            {x + 35, y + 65},
            {x + 115, y + 65},
            {x + 100, y + 235},
            {x + 50, y + 235}
        };

        HBRUSH towerBrush = CreateSolidBrush(RGB(245, 235, 210));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, towerBrush);
        HPEN towerPen = CreatePen(PS_SOLID, 2, RGB(70, 60, 55));
        HPEN oldPen = (HPEN)SelectObject(hdc, towerPen);

        Polygon(hdc, tower, 4);

        SelectObject(hdc, oldBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(towerBrush);
        DeleteObject(towerPen);

        FillRectangle(hdc, x + 44, y + 115, x + 106, y + 140,
            RGB(210, 55, 45));
        FillRectangle(hdc, x + 48, y + 175, x + 101, y + 200,
            RGB(210, 55, 45));

        FillRectangle(hdc, x + 30, y + 35, x + 120, y + 65,
            RGB(65, 100, 120));
        FillRectangle(hdc, x + 25, y + 28, x + 125, y + 37,
            RGB(60, 60, 60));

        POINT roof[] = {
            {x + 22, y + 29},
            {x + 75, y},
            {x + 128, y + 29}
        };

        HBRUSH roofBrush = CreateSolidBrush(RGB(190, 45, 40));
        oldBrush = (HBRUSH)SelectObject(hdc, roofBrush);
        towerPen = CreatePen(PS_SOLID, 2, RGB(80, 45, 40));
        oldPen = (HPEN)SelectObject(hdc, towerPen);

        Polygon(hdc, roof, 3);

        SelectObject(hdc, oldBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(roofBrush);
        DeleteObject(towerPen);

        FillRectangle(hdc, x + 67, y + 200, x + 87, y + 235,
            RGB(90, 55, 35));

        FillRectangle(hdc, x + 57, y + 78, x + 72, y + 98,
            RGB(100, 190, 220));
        FillRectangle(hdc, x + 83, y + 78, x + 98, y + 98,
            RGB(100, 190, 220));

        FillRectangle(hdc, x + 35, y + 235, x + 115, y + 245,
            RGB(110, 100, 90));
    }
};

class Flower
{
public:
    void Draw(HDC hdc, int x, int y, COLORREF petalColor)
    {
        HPEN stemPen = CreatePen(PS_SOLID, 4, RGB(30, 130, 45));
        HPEN oldPen = (HPEN)SelectObject(hdc, stemPen);

        MoveToEx(hdc, x, y + 15, nullptr);
        LineTo(hdc, x, y + 65);

        SelectObject(hdc, oldPen);
        DeleteObject(stemPen);

        FillEllipse(hdc, x - 22, y + 35, x, y + 48,
            RGB(40, 160, 55));
        FillEllipse(hdc, x, y + 45, x + 22, y + 58,
            RGB(40, 160, 55));

        FillEllipse(hdc, x - 17, y - 12, x + 5, y + 10,
            petalColor);
        FillEllipse(hdc, x + 5, y - 12, x + 27, y + 10,
            petalColor);
        FillEllipse(hdc, x - 17, y + 5, x + 5, y + 27,
            petalColor);
        FillEllipse(hdc, x + 5, y + 5, x + 27, y + 27,
            petalColor);

        FillEllipse(hdc, x - 3, y, x + 13, y + 16,
            RGB(255, 210, 0));
    }
};

void DrawScene(HDC hdc, int width, int height)
{
    RECT sky = { 0, 0, width, height };
    FillRect(hdc, &sky, CreateSolidBrush(RGB(135, 206, 235)));

    FillRectangle(hdc, 0, height - 155, width, height,
        RGB(95, 175, 75));

    FillRectangle(hdc, 0, height - 185, width, height - 155,
        RGB(65, 160, 205));

    Sun sun;
    sun.Draw(hdc, width - 115, 100);

    Cloud cloud;
    cloud.Draw(hdc, 100, 65);
    cloud.Draw(hdc, 300, 105);
    cloud.Draw(hdc, width - 350, 55);

    Lighthouse lighthouse;
    lighthouse.Draw(hdc, width / 2 - 75, height - 405);

    Flower flower;
    flower.Draw(hdc, 100, height - 105, RGB(255, 100, 160));
    flower.Draw(hdc, 180, height - 95, RGB(180, 100, 220));
    flower.Draw(hdc, 280, height - 110, RGB(255, 100, 160));
    flower.Draw(hdc, width - 180, height - 105, RGB(255, 100, 160));
    flower.Draw(hdc, width - 100, height - 95, RGB(180, 100, 220));

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(30, 50, 70));
    TextOut(hdc, 20, 15, L"Variant 11",
        lstrlen(L"Variant 11"));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"LighthouseVariant11";

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
        CW_USEDEFAULT, CW_USEDEFAULT, 1000, 700,
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
        DrawScene(hdc, rect.right, rect.bottom);

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
        MessageBox(hwnd,
            L"На цій сцені зображено маяк, хмари, сонце та квіти.",
            L"Variant 11", MB_OK | MB_ICONINFORMATION);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}