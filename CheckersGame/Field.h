#pragma once
#include <windef.h>

class Field
{
private:
	int size;
public:
	Field();

	void createField(HWND hWnd);

	void createButton(int xpos, int ypos, int ID, HWND hWnd, wchar_t *str = L"");

	void createStatic(int xpos, int ypos, int ID, HWND hWnd, wchar_t *str = L"");

	void swapField(int srcId, int destId, wchar_t *str, HWND hWnd);

	int getSize();

	~Field();
};
