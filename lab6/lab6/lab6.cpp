#include "Windows.h" 
#include "lab6.h"
#include "shape_editor.h"
#include "CommCtrl.h" 
#pragma comment(lib, "comctl32.lib") 

LRESULT __stdcall WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

TBBUTTON tbButtons[4];
HIMAGELIST g_hImageList = NULL;

ShapeObjectsEditor obj;

const long idRectangle = 1;
const long idEllipse = 2;
const long idLine = 3;
const long idPoint = 4;

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"NewClassName";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(WS_EX_LEFT, L"NewClassName", L"HomeWork/C++/6", WS_OVERLAPPEDWINDOW, 200, 200, 1000, 700, NULL, NULL, hInstance, NULL);

    const int bitmapSize = 16;

    const DWORD buttonStyles = BTNS_AUTOSIZE;

    HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
        WS_CHILD | TBSTYLE_WRAPABLE | TBSTYLE_TOOLTIPS, 0, 0, 0, 0,
        hWnd, NULL, hInstance, NULL);

    HBITMAP hBitMapRectangle = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
    HBITMAP hBitMapEllipse = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));
    HBITMAP hBitMapLine = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3));
    HBITMAP hBitMapPoint = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP4));

    g_hImageList = ImageList_Create(bitmapSize, bitmapSize,
        ILC_COLOR32 | ILC_MASK,
        4, 0);

    int indexRectangle = ImageList_Add(g_hImageList, hBitMapRectangle, NULL);
    int indexEllipse = ImageList_Add(g_hImageList, hBitMapEllipse, NULL);
    int indexLine = ImageList_Add(g_hImageList, hBitMapLine, NULL);
    int indexPoint = ImageList_Add(g_hImageList, hBitMapPoint, NULL);

    SendMessage(hWndToolbar, TB_SETIMAGELIST,
        (WPARAM)0,
        (LPARAM)g_hImageList);


    SendMessage(hWndToolbar, TB_LOADIMAGES,
        (WPARAM)IDB_STD_SMALL_COLOR,
        (LPARAM)HINST_COMMCTRL);

    tbButtons[0] = { MAKELONG(indexRectangle,  0), idRectangle,  TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Прямокутник" };
    tbButtons[1] = { MAKELONG(1,  0), idEllipse,  TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Еліпс" };
    tbButtons[2] = { MAKELONG(2, 0), idLine, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Лінія" };
    tbButtons[3] = { MAKELONG(3, 0), idPoint, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Точка" };

    SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
    SendMessage(hWndToolbar, TB_ADDBUTTONS, (WPARAM)4, (LPARAM)&tbButtons);

    SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
    ShowWindow(hWndToolbar, TRUE);


    ShowWindow(hWnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT __stdcall WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_NOTIFY:
        switch (((LPNMHDR)lParam)->code)
        {
        case TTN_NEEDTEXT:
        {
            LPNMTTDISPINFO lpttdi = (LPNMTTDISPINFO)lParam;
            switch (lpttdi->hdr.idFrom)
            {
            case idRectangle:
                lstrcpy(lpttdi->szText, L"Інструмент малювання прямокутника");
                break;
            case idEllipse:
                lstrcpy(lpttdi->szText, L"Інструмент малювання еліпса");
                break;
            case idLine:
                lstrcpy(lpttdi->szText, L"Інструмент малювання лінії");
                break;
            case idPoint:
                lstrcpy(lpttdi->szText, L"Інструмент малювання точки");
                break;
            default:
                lstrcpy(lpttdi->szText, L"Undefined");
                break;
            }
        }
        break;
        }
        break;
    case WM_PAINT:
        obj.OnPaint(hwnd);
        break;
    case WM_LBUTTONUP:
        obj.OnLBup(hwnd, lParam);
        break;
    case WM_MOUSEMOVE:
        obj.OnMouseMove(hwnd, lParam);
        break;
    case WM_LBUTTONDOWN:
        obj.OnLBDown(hwnd, lParam);
        break;
    case WM_CREATE:
        break;
    case WM_COMMAND:
        switch (wParam)
        {
        case idRectangle:
        {
            obj.StartRectEditor(hwnd, idRectangle);
            break;
        }
        case idEllipse:
        {
            obj.StartEllipseEditor(hwnd, idEllipse);
            break;
        }
        case idLine:
        {
            obj.StartLineEditor(hwnd, idLine);
            break;
        }
        case idPoint:
            obj.StartPointEditor(hwnd, idPoint);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}