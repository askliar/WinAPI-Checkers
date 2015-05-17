#pragma once
#include "stdafx.h"

class Game
{
	Field FieldInst;
	FirstPlayer FPlayer;
	SecondPlayer SPlayer;
public:
	Game();
	void StartGame(HWND hWNd);
	void FButtonRec(HWND hWnd, int coords, bool &dir);
	void SButtonRec(HWND hWnd, int coords, bool &dir);
	void FTurn(HWND hWnd);
	void STurn(HWND hWnd);
	void FPlayerData(HWND hDlg);
	void SPlayerData(HWND hDlg);
};
