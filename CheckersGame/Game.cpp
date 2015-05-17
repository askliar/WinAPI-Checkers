#include "stdafx.h"
#include "Game.h"

Game::Game() : FieldInst(), FPlayer(), SPlayer()
{}



void Game::StartGame(HWND hWnd)
{
	FieldInst.createField(hWnd);
}

void Game::FButtonRec(HWND hWnd, int coords, bool &dir)
{
	FPlayer.recordButtons(coords, hWnd, FieldInst.getSize(), FieldInst, dir);
}

void Game::SButtonRec(HWND hWnd, int coords, bool &dir)
{
	SPlayer.recordButtons(coords, hWnd, FieldInst.getSize(), FieldInst, dir);
}

void Game::FTurn(HWND hWnd)
{
	wchar_t *str = new wchar_t[50];
	FieldInst.disableField(hWnd);
	if (!FieldInst.FPlayerEatScan(hWnd))
	{
		FieldInst.disableField(hWnd);
		FieldInst.FPlayerScan(hWnd);
	}
	MessageBox(hWnd, L"First Player Turn!", L"1st Player Turn", NULL);
}

void Game::STurn(HWND hWnd)
{
	FieldInst.disableField(hWnd);
	if (!FieldInst.SPlayerEatScan(hWnd))
	{
		FieldInst.disableField(hWnd);
		FieldInst.SPlayerScan(hWnd);
	}
	MessageBox(hWnd, L"Second Player Turn!", L"2nd Player Turn", NULL);
}

void Game::FPlayerData(HWND hDlg)
{
	FPlayer.getData(hDlg);
}

void Game::SPlayerData(HWND hDlg)
{
	SPlayer.getData(hDlg);
}