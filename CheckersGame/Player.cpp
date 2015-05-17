#include "stdafx.h"
#include "Player.h"
#include "Resource.h"
#include "Field.h"
#include "Game.h"

Player::Player()
{
	src.x = -1;
	src.y = -1;
	dest.x = -1;
	dest.y = -1;
	wchar_t *name = new wchar_t[50];
	wchar_t *password = new wchar_t[50];
	scores = 8;
}

void Player::getData(HWND hDlg)
{}

int Player::getScores()
{
	return scores;
}

wchar_t *Player::getName()
{
	return this->name;
}

void Player::nullPoints()
{
	src.x = -1;
	src.y = -1;
	dest.x = -1;
	dest.y = -1;
}

void Player::recordButtons(int coords, HWND hWnd, int size, Field &FieldInst, bool &dir)
{}

void Player::moveFigure(HWND hWnd, int size, Field& FieldInst, bool& dir)
{
}

Player::~Player()
{
	delete[] name;
}

FirstPlayer::FirstPlayer() :Player()
{

}

void FirstPlayer::getData(HWND hDlg)
{

	GetWindowText(GetDlgItem(hDlg, MY_ID_FLOGIN), name, 50);
	scores = 0;
}

void FirstPlayer::recordButtons(int coords, HWND hWnd, int size, Field& FieldInst, bool& dir)
{

	wchar_t *str = new wchar_t[5];
	if (src.x == -1 && src.y == -1) //если еще не записано откуда - записываем
	{
		GetWindowText(GetDlgItem(hWnd, coords + MY_ID_FIELD), str, 5);
		if (!wcscmp(str, L"X"))
		{
			src.x = coords % size;
			src.y = coords / size;
		}
	}
	else if ((src.x != -1 && src.y != -1) && abs(coords / size - src.y) == 1 && abs(coords % size - src.x) == 1) //если уже записано откуда - записываем куда
	{
		if (wcscmp(str, L"X"))
		{
			dest.x = coords % size;
			dest.y = coords / size;
			moveFigure(hWnd, size, FieldInst, dir);
			nullPoints();
		}
	}
	SetFocus(hWnd);

}

void FirstPlayer::moveFigure(HWND hWnd, int size, Field& FieldInst, bool &dir)
{
	Game GameInst;
	wchar_t *str = new wchar_t[2];
	wchar_t *dst = new wchar_t[2];
	GetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + src.y * size + src.x), str, 5);
	GetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + dest.y* size + dest.x), dst, 5);
	if (!wcscmp(str, L"X")) //варианты движения для Х
	{
		if (dest.y - src.y == 1 && abs(dest.x - src.x) == 1 && !wcscmp(dst, L"")) //только вперед на пустое поле
		{
			FieldInst.swapField(MY_ID_FIELD + src.y * size + src.x, MY_ID_FIELD + dest.y* size + dest.x, L"X", hWnd);
		}
		if (abs(dest.y - src.y) == 1 && abs(dest.x - src.x) == 1 && !wcscmp(dst, L"O")) //"убийство" фигуры
		{
			eatFigure(hWnd, 8);
			FieldInst.disableField(hWnd);
			if (FieldInst.FPlayerPointScan(hWnd, 2 * dest.y - src.y, 2 * dest.x - src.x))
			{
				dir = true;
				return;
			}
		}
	}
	delete str;
	delete dst;
	dir = false;
	GameInst.STurn(hWnd);
}

void FirstPlayer::eatFigure(HWND hWnd, int size)
{
	wchar_t *str = new wchar_t[5];
	GetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + (2 * dest.y - src.y)  * size + 2 * dest.x - src.x), str, 5);
	if (!wcscmp(str, L""))
	{
		SetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + src.y * size + src.x), L"");
		SetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + (2 * dest.y - src.y) * size + 2 * dest.x - src.x), L"X");
		SetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + dest.y * size + dest.x), L"");
		scores--;
	}
}

FirstPlayer::~FirstPlayer()
{

}

SecondPlayer::SecondPlayer() :Player()
{

}

void SecondPlayer::getData(HWND hDlg)
{

	GetWindowText(GetDlgItem(hDlg, MY_ID_SLOGIN), name, 50);
	scores = 0;
}

void SecondPlayer::recordButtons(int coords, HWND hWnd, int size, Field& FieldInst, bool& dir)
{

	wchar_t *str = new wchar_t[5];
	if (src.x == -1 && src.y == -1) //если еще не записано откуда - записываем
	{
		GetWindowText(GetDlgItem(hWnd, coords + MY_ID_FIELD), str, 5);
		if (!wcscmp(str, L"O"))
		{
			src.x = coords % size;
			src.y = coords / size;
		}
	}
	else if ((src.x != -1 && src.y != -1) && abs(coords / size - src.y) == 1 && abs(coords % size - src.x) == 1) //если уже записано откуда - записываем куда
	{
		if (wcscmp(str, L"O"))
		{
			dest.x = coords % size;
			dest.y = coords / size;
			moveFigure(hWnd, size, FieldInst, dir);
			nullPoints();
		}
	}
	SetFocus(hWnd);

}

void SecondPlayer::moveFigure(HWND hWnd, int size, Field& FieldInst, bool &dir)
{
	Game GameInst;
	wchar_t *str = new wchar_t[2];
	wchar_t *dst = new wchar_t[2];
	GetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + src.y * size + src.x), str, 5);
	GetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + dest.y* size + dest.x), dst, 5);
	if (!wcscmp(str, L"O")) //варианты движения для O
	{
		if (dest.y - src.y == -1 && abs(dest.x - src.x) == 1 && !wcscmp(dst, L"")) //только вперед на пустое поле
		{
			FieldInst.swapField(MY_ID_FIELD + src.y * size + src.x, MY_ID_FIELD + dest.y* size + dest.x, L"O", hWnd);
		}
		if (abs(dest.y - src.y) == 1 && abs(dest.x - src.x) == 1 && !wcscmp(dst, L"X")) //"убийство" фигуры
		{
			eatFigure(hWnd, 8);
			FieldInst.disableField(hWnd);
			if (FieldInst.SPlayerPointScan(hWnd, 2 * dest.y - src.y, 2 * dest.x - src.x))
			{
				dir = false;
				return;
			}
		}
	}
	delete str;
	delete dst;
	dir = true;
	GameInst.FTurn(hWnd);
}

void SecondPlayer::eatFigure(HWND hWnd, int size)
{
	wchar_t *str = new wchar_t[5];
	GetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + (2 * dest.y - src.y) * size + 2 * dest.x - src.x), str, 5);
	if (!wcscmp(str, L""))
	{
		SetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + src.y * size + src.x), L"");
		SetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + (2 * dest.y - src.y)  * size + 2 * dest.x - src.x), L"O");
		SetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + dest.y * size + dest.x), L"");
		scores--;
	}
}

SecondPlayer::~SecondPlayer()
{

}