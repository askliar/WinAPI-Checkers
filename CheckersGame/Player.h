#pragma once
#include <windef.h>
#include "Field.h"

struct point
{
	int x;
	int y;
};

class Player
{
protected:
	wchar_t *name;
	wchar_t *password;
	point src;
	point dest;
	int scores;
public:
	Player();
	wchar_t *getName();
	wchar_t* getPass();
	virtual void getData(HWND hDlg);
	void recordButtons(int coords, HWND hWnd, int size);
	void moveFigure(HWND hWnd, int size, Field FieldInst);
	void nullPoints();
	virtual ~Player();
};

class FirstPlayer: public Player
{
	FirstPlayer();
	void getData(HWND hDlg) final override;
	~FirstPlayer();
};

class SecondPlayer: public Player
{
	SecondPlayer();
	void getData(HWND hDlg) final override;
	~SecondPlayer();
};