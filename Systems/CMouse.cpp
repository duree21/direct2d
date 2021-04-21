#include "stdafx.h"
#include "Systems/CMouse.h"
// GetDoubleClickTime()
// ���� �ü���� �����Ǿ��ִ� DoubleClick �ð������� ��ȯ

// GeTickCount()
// �Լ��� ����
// DWORD GetTickCount()
// �ý����� ������ �������� �� �Լ��� ȣ��� �������� �귯�� �ð��� 1/1000�� (�и�������) ������ ��ȯ���ִ� �Լ�
// �۾��� �ҿ�� �簣�� ����� �� �����ϴ�.

// GetAsyncKeyState()
// �Լ��� ����
// SHORT GetAsyncKeyState(int VK) 
// �Լ��� ȣ��Ǳ� ������ Ű�� ���� ���¿�����, �Լ��� ȣ�� �� ������ Ű�� ���� �������� �� �� �ִ� �Լ�
// ��ȯ ��
// 0X0000 ������ ���� ���� ���� ȣ�� �������� �������� ���� ���� 
// 0X0001 ������ ���� ���� �ְ� ȣ�� �������� �������� ���� ���� 
// 0X8000 ������ ���� ���� ���� ȣ�� �������� �����ִ� ���� 
// 0X8001 ������ ���� ���� �ְ� ȣ�� �������� �����ִ� ���� 

// GetCursor()
// �Լ��� ���� 
// BOOL GetCursorPos(LPPOINT lpPoint);
// ��ü ȭ�� �������� Ŀ���� ��ǥ�� �޾ƿ��� �Լ�

// ScreenToClient()
// �Լ��� ����
// BOOL ScreenToClient(HWND hWnd, LPPOINT lpPoint);
// ��ü ȭ�� ������ Ŀ�� ��ǥ�� �ش� Ŭ���̾�Ʈ(������) �������� ��ǥ�� ��ȯ���ִ� �Լ�

// WPARAM 
// Ű���� ������ ���¸� Ȯ��

// LPARAM
// 2����Ʈ�� �߶� x,y �� ��� 
//////////////////////////////////
//				//				//
//		y		//		 x		//
//				//				//
//////////////////////////////////
//HIWORD(LPARAM)  // LOWORD(LPALRAM)

// LOWORD
// x�� ��

// HIWORD
// y�� ��




CMouse::CMouse(HWND handle)
	: handle(handle)
	, position(0, 0)
	, wheelValue(0), wheelPrevValue(0), wheelMoveValue(0)
{
	ZeroMemory(buttonStatus, sizeof(byte) * 8); // �����ͷ� �޸� �ʱ�ȭ
	ZeroMemory(buttonPrevStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);
	ZeroMemory(buttonCount, sizeof(int) * 8);
	

	doubleClickTime = GetDoubleClickTime();		
	
	startDoubleClickTime[0] = GetTickCount();

	for (int i = 1; i < 8; i++)
		startDoubleClickTime[i] = startDoubleClickTime[0];
}

CMouse::~CMouse()
{

}

void CMouse::WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (iMessage == WM_MOUSEMOVE)	// ���콺 Ŀ�� ������ 
	{
		position.x = (float)LOWORD(lParam); // ���콺 Ŀ�� ��ġ X�� ��
		position.y = (float)HIWORD(lParam);	// ���콺 Ŀ�� ��ġ Y�� ��
	}

	if (iMessage == WM_MOUSEWHEEL)	// ���콺 �� 
	{
		short temp = (short)HIWORD(wParam);	// ���콺 �� ������?

		wheelPrevValue = wheelValue;
		wheelValue += (float)temp; // ���콺 ���� �������� wheelValue�� �Ҵ� 
	}
}

void CMouse::Update()
{
	memcpy(buttonPrevStatus, buttonStatus, sizeof(byte) * 8);	// �޸� ���� �Լ� 

	ZeroMemory(buttonStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);


	buttonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;	// ���콺 ���� ��ư ���ȴ��� �ȴ��ȴ���
	buttonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;	// ������			
	buttonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;	// �߰� (���콺 �� ��ư?)

	for (UINT i = 0; i < 8; i++)
	{
		byte prevStatus = buttonPrevStatus[i];
		byte status = buttonStatus[i];

		if (prevStatus == 0 && status == 1)	// ��ư�� �� �����ٰ� ������ 
			buttonMap[i] = Button::Down;	// Down
		else if (prevStatus == 1 && status == 0)	// ��ư�� ������ ������
			buttonMap[i] = Button::Up;		//Up
		else if (prevStatus == 1 && status == 1)	// ��ư�� ��� ������ ������
			buttonMap[i] = Button::Press;	//Press
		else // �ƹ� ��ư�� ������ ������ 
			buttonMap[i] = Button::None;	//None
	}

	UINT buttonStatus = GetTickCount();	// ���콺 ��ư�� �۵� Ȯ�� ������ �ð��� bottonStatus�� ���� 

	// ����Ŭ�� �Ǻ� 
	for (UINT i = 0; i < 8; i++)
	{
		if (buttonMap[i] == Button::Down) // ���콺 ��ư�� �� �����ִٰ� ������ �� 
		{
			if (buttonCount[i] == 1)	// bottonCount�� 1�� �� 
			{
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime) // �ü���� ���� Ŭ������ ���� �ð����� ���� Ŭ�� �ӵ��� ������ 
					buttonCount[i] = 0; // bottomCount �� 0
			}
			buttonCount[i]++;	// bottonCount �� 1 ���� 

			if (buttonCount[i] == 1)	// bottonCount�� 1�� �� 
				startDoubleClickTime[i] = buttonStatus; // �ٽ� ��ư Ŭ�� ���� Ȯ�� ���� �ð��� ����(���⼭�� ��ư�� �����ٰ� ���������� �ð�)
		}

		// ���콺 ��ư�� ������ ������ Ŭ�� ���θ� �Ǵ��ؾ� �ϹǷ� ����Ŭ�� ���δ� Button::Up�� �� �Ǻ�
		if (buttonMap[i] == Button::Up) // ����Ʈ ��ư�� �����ִٰ� ���� ��
		{
			if (buttonCount[i] == 1)	// bottonCount�� 1�� �� 
			{
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime) // �ü���� ����Ŭ������ ���� �ð����� ���� Ŭ�� �ӵ��� ������ 
					buttonCount[i] = 0;	// bottonCount�� 0
			}
			else if (buttonCount[i] == 2)	// bottonCount�� 2�� �� 
			{
				if (buttonStatus - startDoubleClickTime[i] <= doubleClickTime)	// �ü���� ����Ŭ������ ���� �ð����� ���� Ŭ�� �ӵ��� ������ 
					buttonMap[i] = Button::DoubleClick;	// buttonMap �� DoubleClick �Ҵ� 

				buttonCount[i] = 0; // buttonCount�� 0 �Ҵ� 
			}
		}
	}


	POINT point;

	GetCursorPos(&point);	// ���콺 Ŀ���� ��ǥ 
	ScreenToClient(handle, &point);	// GetCursorPos �Լ��� Ŀ���� ��ǥ�� ��� �� �� ScreenToClient�Լ��� ������ �������� ��ȯ
	//ClientToScreen(handle, &point);

	wheelPrevValue = wheelValue;
	wheelMoveValue = wheelValue - wheelPrevValue;	// ���콺 �� ������ ���� ��ġ���� ������ġ ��� ���ָ� ���� ������ �� �� ����
}