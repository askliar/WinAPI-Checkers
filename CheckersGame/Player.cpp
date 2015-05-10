#include "stdafx.h"
#include "Player.h"
#include "Resource.h"
#include "Field.h"

Player::Player()
{
	src.x = -1;
	src.y = -1;
	dest.x = -1;
	dest.y = -1;
	wchar_t *name = new wchar_t[50];
	wchar_t *password = new wchar_t[50];
	scores = 0;
}

void Player::getData(HWND hDlg)
{}

wchar_t *Player::getName()
{
	return this->name;
}

wchar_t *Player::getPass()
{
	return password;
}

void Player::nullPoints()
{
	src.x = -1;
	src.y = -1;
	dest.x = -1;
	dest.y = -1;
}

void Player::recordButtons(int coords, HWND hWnd, int size)
{
	if (src.x == -1 && src.y == -1) //если еще не записано откуда - записываем
	{
		src.x = coords % size;
		src.y = coords / size;
	}
	else if (src.x != -1 && src.y != -1 && dest.x == -1 && dest.y == -1) //если уже записано откуда - записываем куда
	{
		dest.x = coords % size;
		dest.y = coords / size;
		moveFigure(hWnd,size);
	}
	SetFocus(hWnd);
}

void Player::moveFigure(HWND hWnd, int size, Field FieldInst) //перемещение шашек по полю
{
	wchar_t *str = new wchar_t[2];
	wchar_t *dst = new wchar_t[2];
	GetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + src.y * size + src.x), str, 5);
	GetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + dest.y* size + dest.x), dst, 5);
	if (!wcscmp(str, L"X")) //варианты движения для Х
	{
		if (dest.y - src.y == 1 && abs(dest.x - src.x) == 1 && !wcscmp(dst, L"")) //только вперед на пустое поле
		{
			FieldInst.swapField(MY_ID_FIELD + src.y * size + src.x, MY_ID_FIELD + dest.y* size + dest.x, L"X", hWnd);
			/*SetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + dest.y* size + dest.x), L"X");
			SetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + src.y * size + src.x), L"");*/
		}
		//if (abs(dest.y - src.y) == 1 && abs(dest.x - src.x) == 1 && !wcscmp(dst, L"O")) //"убийство" фигуры
		//{
		//	eatFigure(hWnd, true);
		//}
	}
	if (!wcscmp(str, L"O")) //варианты движения для О
	{
		if (dest.y - src.y == -1 && abs(dest.x - src.x) == 1 && !wcscmp(dst, L"")) //только вперед на пустое поле
		{
			FieldInst.swapField(MY_ID_FIELD + src.y * size + src.x, MY_ID_FIELD + dest.y* size + dest.x, L"O", hWnd);
			/*SetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + dest.y* size + dest.x), L"O");
			SetWindowText(GetDlgItem(hWnd, MY_ID_FIELD + src.y * size + src.x), L"");*/
		}
		//if (abs(dest.y - src.y) == 1 && abs(dest.x - src.x) == 1 && !wcscmp(dst, L"X")) //"убийство" фигуры
		//{
		//	eatFigure(hWnd, false);
		//}
	}
	nullPoints();
	delete str;
	delete dst;
}

Player::~Player()
{
	delete[] name;
	delete[] password;
}

FirstPlayer::FirstPlayer() :Player()
{

}

void FirstPlayer::getData(HWND hDlg)
{

	GetWindowText(GetDlgItem(hDlg, MY_ID_FLOGIN), name, 50);
	GetWindowText(GetDlgItem(hDlg, MY_ID_FPASS), password, 50);
	scores = 0;
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
	GetWindowText(GetDlgItem(hDlg, MY_ID_SPASS), password, 50);
	scores = 0;
}

SecondPlayer::~SecondPlayer()
{

}





