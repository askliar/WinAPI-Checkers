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
	point src;
	point dest;
	int scores;
public:
	Player();
	wchar_t *getName();
	virtual void getData(HWND hDlg);
	int getScores();
	virtual void recordButtons(int coords, HWND hWnd, int size, Field &FieldInst, bool &dir);
	virtual void moveFigure(HWND hWnd, int size, Field &FieldInst, bool &dir);
	void nullPoints();
	virtual ~Player();
};

class FirstPlayer: public Player
{
public:
	FirstPlayer();
	void getData(HWND hDlg) final override;
	void recordButtons(int coords, HWND hWnd, int size, Field &FieldInst, bool &dir) override;
	void moveFigure(HWND hWnd, int size, Field &FieldInst, bool &dir) override;
	void eatFigure(HWND hWnd, int size);
	~FirstPlayer();
};

class SecondPlayer: public Player
{
public:
	SecondPlayer();
	void getData(HWND hDlg) final override;
	void recordButtons(int coords, HWND hWnd, int size, Field &FieldInst, bool &dir) override;
	void moveFigure(HWND hWnd, int size, Field &FieldInst, bool &dir) override;
	void eatFigure(HWND hWnd, int size);
	~SecondPlayer();
};