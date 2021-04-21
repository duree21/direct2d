#pragma once

class CMouse
{
public:
	CMouse(HWND handle);
	~CMouse();

	void WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam);

	void Update();

	D3DXVECTOR2 Position() { return position; }	// ���콺 Ŀ���� ��ġ�� ��ȯ

private:
	
	enum class Button	// ���콺 ��ư �۵� ���� 
	{
		None, Down, Up, Press, DoubleClick,	// ���� ��, ��ư ����, ��ư ��, ��ư ������ ����, ��ư ���� Ŭ��
	};

public:
	bool Down(UINT button)	// ���콺 ��ư�� �������� �ƴ����� ��ȯ
	{
		return buttonMap[button] == Button::Down;
	}

	bool Up(UINT button)	// ���콺 ��ư�� ������ �ƴ����� ��ȯ
	{
		return buttonMap[button] == Button::Up;
	}

	bool Press(UINT button)	// ���콺 ��ư�� ��� ������ ������ �ƴ����� ��ȯ
	{
		return buttonMap[button] == Button::Press;
	}

	bool DoubleClick(UINT button)	// ���콺�� ���� Ŭ�� �ߴ��� �ƴ����� ��ȯ 
	{
		return buttonMap[button] == Button::DoubleClick;
	}

	float Wheel() { return wheelMoveValue; }	// ���콺 ���� ��� �۵�������� ��ȯ


private:
	HWND handle;

	D3DXVECTOR2 position;

	byte buttonStatus[8];
	byte buttonPrevStatus[8];
	Button buttonMap[8];

	float wheelValue;
	float wheelPrevValue;
	float wheelMoveValue;

	DWORD doubleClickTime;
	DWORD startDoubleClickTime[8];
	int buttonCount[8];
};