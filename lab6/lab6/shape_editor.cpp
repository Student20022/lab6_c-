#include "shape_editor.h"

Shape** pshape = new Shape * [127];

bool line_edit = false; 
bool rect_edit = false; 
bool ellipse_edit = false; 
bool point_edit = false; 
long count_objects = 0; 

void ShapeObjectsEditor::StartLineEditor(HWND hwnd, UINT uint_item_menu)
{
	CheckMenuItem(GetMenu(hwnd), 32773, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32772, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32774, MF_UNCHECKED);

	rect_edit = false; 
	ellipse_edit = false; 
	point_edit = false;

	if (CheckMenuItem(GetMenu(hwnd), uint_item_menu, NULL) == MF_CHECKED){
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_UNCHECKED);
	}
	else {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_CHECKED); 
	}
	line_edit =! line_edit;
	delete shapeeditor; shapeeditor = new LineEditor();
	delete shape; shape = new LineShape(); 
}

void ShapeObjectsEditor::StartRectEditor(HWND hwnd, UINT uint_item_menu)
{
	CheckMenuItem(GetMenu(hwnd), 32773, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32771, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32774, MF_UNCHECKED);

	line_edit = false;
	ellipse_edit = false;
	point_edit = false;

	if (CheckMenuItem(GetMenu(hwnd), uint_item_menu, NULL) == MF_CHECKED) {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_UNCHECKED);
	}
	else {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_CHECKED);
	}
	rect_edit =! rect_edit;
	delete shapeeditor; shapeeditor = new RectangleEditor();
	delete shape; shape = new RectangleShape();
}

void ShapeObjectsEditor::StartEllipseEditor(HWND hwnd, UINT uint_item_menu)
{
	CheckMenuItem(GetMenu(hwnd), 32772, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32771, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32774, MF_UNCHECKED);

	line_edit = false;
	rect_edit = false;
	point_edit = false;

	if (CheckMenuItem(GetMenu(hwnd), uint_item_menu, NULL) == MF_CHECKED) {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_UNCHECKED);
	}
	else {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_CHECKED);
	}
	ellipse_edit = !ellipse_edit;
	delete shapeeditor; shapeeditor = new EllipseEditor();
	delete shape; shape = new EllipseShape();
}

void ShapeObjectsEditor::StartPointEditor(HWND hwnd, UINT uint_item_menu)
{
	CheckMenuItem(GetMenu(hwnd), 32773, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32771, MF_UNCHECKED);
	CheckMenuItem(GetMenu(hwnd), 32772, MF_UNCHECKED);

	line_edit = false;
	ellipse_edit = false;
	rect_edit = false; 

	if (CheckMenuItem(GetMenu(hwnd), uint_item_menu, NULL) == MF_CHECKED) {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_UNCHECKED);
	}
	else {
		CheckMenuItem(GetMenu(hwnd), uint_item_menu, MF_CHECKED);
	}
	point_edit = !point_edit;
	delete shapeeditor; shapeeditor = new PointEditor();
	delete shape; shape = new PointShape();
}

void ShapeObjectsEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
	if (line_edit){
		shapeeditor->OnMouseMove(hwnd, lParam); 
	}
	if (rect_edit) {
		shapeeditor->OnMouseMove(hwnd, lParam); 
	}
	if (ellipse_edit) {
		shapeeditor->OnMouseMove(hwnd, lParam); 
	}
	if (point_edit) {
		shapeeditor->OnMouseMove(hwnd, lParam); 
	}
}

void ShapeObjectsEditor::OnLBup(HWND hwnd, LPARAM lParam) {
	if (line_edit) {
		shapeeditor->OnLBup(hwnd, lParam); 
		shapeeditor->OnLBup(hwnd, lParam);
		long x1, y1, x2, y2;
		x1 = dynamic_cast<LineEditor*>(shapeeditor)->start_POS.x;
		y1 = dynamic_cast<LineEditor*>(shapeeditor)->start_POS.y;
		x2 = dynamic_cast<LineEditor*>(shapeeditor)->end_POS.x;
		y2 = dynamic_cast<LineEditor*>(shapeeditor)->end_POS.y; 
		shape->Set(x1, y1, x2, y2);
		pshape[count_objects] = shape;
		count_objects++;
		InvalidateRect(hwnd, NULL, TRUE);
	}
	if (rect_edit) {
		shapeeditor->OnLBup(hwnd, lParam); 
		long x1, y1, x2, y2;
		x1 = dynamic_cast<RectangleEditor*>(shapeeditor)->start_POS.x; 
		y1 = dynamic_cast<RectangleEditor*>(shapeeditor)->start_POS.y; 
		x2 = dynamic_cast<RectangleEditor*>(shapeeditor)->end_POS.x;
		y2 = dynamic_cast<RectangleEditor*>(shapeeditor)->end_POS.y; 
		shape->Set(x1, y1, x2, y2); 
		pshape[count_objects] = shape;
		count_objects++; 
		InvalidateRect(hwnd, NULL, TRUE); 
	}
	if (ellipse_edit) {
		shapeeditor->OnLBup(hwnd, lParam); 
		long x1, y1, x2, y2;
		x1 = dynamic_cast<EllipseEditor*>(shapeeditor)->start_POS.x;
		y1 = dynamic_cast<EllipseEditor*>(shapeeditor)->start_POS.y;
		x2 = dynamic_cast<EllipseEditor*>(shapeeditor)->end_POS.x;
		y2 = dynamic_cast<EllipseEditor*>(shapeeditor)->end_POS.y;
		shape->Set(x1, y1, x2, y2);
		pshape[count_objects] = shape;
		count_objects++; 
		InvalidateRect(hwnd, NULL, TRUE);
	}
	if (point_edit) {
		shapeeditor->OnLBup(hwnd, lParam); 
		long x1, y1; 
		x1 = dynamic_cast<PointEditor*>(shapeeditor)->start_POS.x;
		y1 = dynamic_cast<PointEditor*>(shapeeditor)->start_POS.y; 
		shape->Set(x1, y1, 0, 0); 
		pshape[count_objects] = shape;
		count_objects++; 
		InvalidateRect(hwnd, NULL, TRUE);
	}
}

void ShapeObjectsEditor::OnLBDown(HWND hwnd, LPARAM lParam) {
	if (line_edit) {
		shapeeditor->OnLBdown(hwnd, lParam); 
	}
	if (rect_edit) {
		shapeeditor->OnLBdown(hwnd, lParam); 
	}
	if (ellipse_edit) {
		shapeeditor->OnLBdown(hwnd, lParam); 
	}
	if (point_edit) {
		shapeeditor->OnLBdown(hwnd, lParam); 
	}
}

void ShapeObjectsEditor::OnPaint(HWND hwnd) {
	HDC hdc = GetDC(hwnd);
	if (count_objects < 127)
	{
		for (std::uint32_t i = 0; i < count_objects; i++)
		{
			if (pshape[i] != nullptr)
			{
				pshape[i]->Show(hdc);
				pshape[i] = nullptr;
			}
		}
	}
	else
	{
		MessageBox(hwnd, L"Limit objects", MB_OK, NULL); 
	}
	ReleaseDC(hwnd, hdc);
}

ShapeObjectsEditor::ShapeObjectsEditor() {
	shapeeditor = nullptr; 
	shape = nullptr; 
}; 
ShapeObjectsEditor::~ShapeObjectsEditor() {
	delete shape; 
	delete shapeeditor; 
	delete[] pshape;
}