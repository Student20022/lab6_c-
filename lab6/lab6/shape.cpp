#include "shape.h" 

void Shape::Set(long x1, long y1, long x2, long y2) {
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

void LineShape::Show(HDC hdc){
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
}

void RectangleShape::Show(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 192, 203));

	SelectObject(hdc, hBrush);

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	SelectObject(hdc, hPen);
	Rectangle(hdc, xs1, ys1, xs2, ys2);

	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void EllipseShape::Show(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, hBrush);

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	SelectObject(hdc, hPen);
	Ellipse(hdc, xs1, ys1, xs2, ys2);

	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void PointShape::Show(HDC hdc)
{
	SetPixel(hdc, xs1, ys1, RGB(0, 0, 0));
}