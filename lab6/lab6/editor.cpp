#include "editor.h" 
bool drawLine = false; 
bool drawRect = false; 
bool drawEllipse = false; 
bool drawPoint = false; 

long position[4]; 

void LineEditor::OnLBup(HWND hwnd, LPARAM lParam){
    drawLine = false; 
    OnPaint(hwnd); 
}
void LineEditor::OnPaint(HWND hwnd){
    HDC hdc = GetDC(hwnd);
    HPEN hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
    SelectObject(hdc, hPen);
    SetROP2(hdc, R2_NOTXORPEN);

    MoveToEx(hdc, start_POS.x, start_POS.y, NULL);
    LineTo(hdc, end_POS.x, end_POS.y); 

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
}
void LineEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (drawLine) {
        OnPaint(hwnd);
        start_POS.x = LOWORD(lParam);
        start_POS.y = HIWORD(lParam);
        OnPaint(hwnd);
    }
}
void LineEditor::OnLBdown(HWND hwnd, LPARAM lParam)
{
    drawLine = true;
    start_POS.x = LOWORD(lParam);
    start_POS.y = HIWORD(lParam);
    end_POS = start_POS; 
    
}

void RectangleEditor::OnPaint(HWND hwnd)
{
    int c_X = (start_POS.x + end_POS.x) / 2;
    int c_Y = (start_POS.y + end_POS.y) / 2;
    int wh = abs(start_POS.x - end_POS.x);
    int ht = abs(start_POS.y - end_POS.y);

    HDC hdc = GetDC(hwnd);
    HPEN hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
    
    SelectObject(hdc, hPen);
    SetROP2(hdc, R2_NOTXORPEN);
    if (end_POS.x < start_POS.x)
    {
        if (end_POS.y < start_POS.y)
        {
            position[0] = c_X; 
            position[1] = c_Y; 
            position[2] = c_X - wh; 
            position[3] = c_Y - ht; 
            Rectangle(hdc, c_X, c_Y, c_X - wh, c_Y - ht);
        }
        else
        {
            position[0] = c_X;
            position[1] = c_Y;
            position[2] = c_X - wh;
            position[3] = c_Y + ht;
            Rectangle(hdc, c_X, c_Y, c_X - wh, c_Y + ht);
        }
    }
    else
    {
        if (end_POS.y < start_POS.y)
        {
            position[0] = c_X;
            position[1] = c_Y;
            position[2] = c_X + wh;
            position[3] = c_Y - ht;
            Rectangle(hdc, c_X, c_Y, c_X + wh, c_Y - ht);
        }
        else
        {
            position[0] = c_X;
            position[1] = c_Y;
            position[2] = c_X + wh;
            position[3] = c_Y + ht;
            Rectangle(hdc, c_X, c_Y, c_X + wh, c_Y + ht);
        }
    }

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
}

void RectangleEditor::OnLBdown(HWND hwnd, LPARAM lParam)
{
    drawRect = true;
    start_POS.x = LOWORD(lParam); 
    start_POS.y = HIWORD(lParam);
    end_POS = start_POS;
}

void RectangleEditor::OnLBup(HWND hwnd, LPARAM lParam)
{
    drawRect = false; 
    OnPaint(hwnd); 
    start_POS.x = position[0]; 
    start_POS.y = position[1]; 
    end_POS.x = position[2]; 
    end_POS.y = position[3]; 

}

void RectangleEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (drawRect){
        OnPaint(hwnd);
        end_POS.x = LOWORD(lParam);
        end_POS.y = HIWORD(lParam);
        OnPaint(hwnd);
    }
}

void EllipseEditor::OnLBdown(HWND hwnd, LPARAM lParam)
{
    drawEllipse = true; 
    start_POS.x = LOWORD(lParam);
    start_POS.y = HIWORD(lParam);
    end_POS = start_POS; 
}

void EllipseEditor::OnLBup(HWND hwnd, LPARAM lParam)
{
    drawEllipse = false; 
    OnPaint(hwnd); 
} 

void EllipseEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (drawEllipse)
    {
        OnPaint(hwnd);
        end_POS.x = LOWORD(lParam);
        end_POS.y = HIWORD(lParam);
        OnPaint(hwnd);
    }
}

void EllipseEditor::OnPaint(HWND hwnd)
{
    HDC hdc = GetDC(hwnd);
    HPEN hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
    SelectObject(hdc, hPen);

    SetROP2(hdc, R2_NOTXORPEN);

    Ellipse(hdc, start_POS.x, start_POS.y, end_POS.x, end_POS.y);

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
}

void PointEditor::OnLBup(HWND hwnd, LPARAM lParam) {
    drawPoint = false;
    OnPaint(hwnd);
}

void PointEditor::OnPaint(HWND hwnd) {

}

void PointEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (drawPoint) {
        OnPaint(hwnd);
        start_POS.x = LOWORD(lParam);
        start_POS.y = HIWORD(lParam);
        OnPaint(hwnd);
    }
}

void PointEditor::OnLBdown(HWND hwnd, LPARAM lParam){
    drawPoint = true;
    start_POS.x = LOWORD(lParam);
    start_POS.y = HIWORD(lParam);
}

void ShapeEditor::OnLBdown(HWND, LPARAM) {};
void ShapeEditor::OnLBup(HWND, LPARAM) {};
void ShapeEditor::OnMouseMove(HWND, LPARAM) {};
void ShapeEditor::OnPaint(HWND) {};