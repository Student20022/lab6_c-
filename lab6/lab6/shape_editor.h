#include "windows.h" 
#include "shape.h" 
#include "editor.h"

#ifndef SHAPE_EDITOR_H
#define SHAPE_EDITOR_H
class ShapeObjectsEditor
{
private:
	Shape* shape;
	ShapeEditor* shapeeditor;
public:
	ShapeObjectsEditor();
	~ShapeObjectsEditor();

	void StartPointEditor(HWND, UINT);
	void StartLineEditor(HWND, UINT);
	void StartRectEditor(HWND, UINT);
	void StartEllipseEditor(HWND, UINT);

	void OnLBDown(HWND, LPARAM);
	void OnLBup(HWND, LPARAM);
	void OnMouseMove(HWND, LPARAM);
	void OnPaint(HWND);
};
#endif