#include "Windows.h"
#include "vector" 

#ifndef EDITOR_H
#define EDITOR_H
class Editor
{
public:
	virtual void OnLBdown(HWND, LPARAM) = 0;
	virtual void OnLBup(HWND, LPARAM) = 0;
	virtual void OnMouseMove(HWND, LPARAM) = 0;
	virtual void OnPaint(HWND) = 0;
};

class ShapeEditor : public Editor
{
public:
	void OnLBdown(HWND, LPARAM) override;
	void OnLBup(HWND, LPARAM) override;
	void OnMouseMove(HWND, LPARAM) override;
	void OnPaint(HWND) override;
};

class LineEditor : public ShapeEditor
{
public:
	POINT start_POS;
	POINT end_POS;
	void OnLBdown(HWND, LPARAM) override;
	void OnLBup(HWND, LPARAM) override;
	void OnMouseMove(HWND, LPARAM) override;
	void OnPaint(HWND) override;
};

class RectangleEditor : public ShapeEditor
{
public:
	POINT start_POS;
	POINT end_POS;
	void OnLBdown(HWND, LPARAM) override;
	void OnLBup(HWND, LPARAM) override;
	void OnMouseMove(HWND, LPARAM) override;
	void OnPaint(HWND) override; 
}; 

class EllipseEditor : public ShapeEditor
{
public:
	POINT start_POS;
	POINT end_POS;
	void OnLBdown(HWND, LPARAM) override;
	void OnLBup(HWND, LPARAM) override;
	void OnMouseMove(HWND, LPARAM) override;
	void OnPaint(HWND) override;
};

class PointEditor : public ShapeEditor
{
public:
	POINT start_POS;
	POINT end_POS;
	void OnLBdown(HWND, LPARAM) override;
	void OnLBup(HWND, LPARAM) override;
	void OnMouseMove(HWND, LPARAM) override;
	void OnPaint(HWND) override;
};
#endif // !EDITOR_H