#pragma once

class CMouse
{
public:
	CMouse(HWND handle);
	~CMouse();

	void WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam);

	void Update();

	D3DXVECTOR2 Position() { return position; }	// 마우스 커서의 위치를 반환

private:
	
	enum class Button	// 마우스 버튼 작동 종류 
	{
		None, Down, Up, Press, DoubleClick,	// 동작 무, 버튼 누름, 버튼 땜, 버튼 누르고 있음, 버튼 더블 클릭
	};

public:
	bool Down(UINT button)	// 마우스 버튼을 눌렀는지 아닌지를 반환
	{
		return buttonMap[button] == Button::Down;
	}

	bool Up(UINT button)	// 마우스 버튼을 땠는지 아닌지를 반환
	{
		return buttonMap[button] == Button::Up;
	}

	bool Press(UINT button)	// 마우스 버튼을 계속 누르는 중인지 아닌지를 반환
	{
		return buttonMap[button] == Button::Press;
	}

	bool DoubleClick(UINT button)	// 마우스를 더블 클릭 했는지 아닌지를 반환 
	{
		return buttonMap[button] == Button::DoubleClick;
	}

	float Wheel() { return wheelMoveValue; }	// 마우스 휠이 어떻게 작동됬는지를 반환


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