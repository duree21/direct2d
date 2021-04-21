#include "stdafx.h"
#include "Systems/CMouse.h"
// GetDoubleClickTime()
// 현재 운영체제에 설정되어있는 DoubleClick 시간간격을 반환

// GeTickCount()
// 함수의 원형
// DWORD GetTickCount()
// 시스템이 시작한 시점부터 이 함수가 호출된 시점까지 흘러간 시간을 1/1000초 (밀리세컨드) 단위로 반환해주는 함수
// 작업에 소요된 사간을 계산할 때 유용하다.

// GetAsyncKeyState()
// 함수의 원형
// SHORT GetAsyncKeyState(int VK) 
// 함수가 호출되기 이전에 키를 누른 상태였는지, 함수가 호출 된 시점에 키를 누른 상태인지 알 수 있는 함수
// 반환 값
// 0X0000 이전에 누른 적이 없고 호출 시점에도 눌려있지 않은 상태 
// 0X0001 이전에 누른 적이 있고 호출 시점에는 눌려있지 않은 상태 
// 0X8000 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태 
// 0X8001 이전에 누른 적이 있고 호출 시점에도 눌려있는 상태 

// GetCursor()
// 함수의 원형 
// BOOL GetCursorPos(LPPOINT lpPoint);
// 전체 화면 기준으로 커서의 좌표를 받아오는 함수

// ScreenToClient()
// 함수의 원형
// BOOL ScreenToClient(HWND hWnd, LPPOINT lpPoint);
// 전체 화면 기준의 커서 좌표를 해당 클라이언트(윈도우) 기준으로 좌표를 변환해주는 함수

// WPARAM 
// 키값이 눌려진 상태를 확인

// LPARAM
// 2바이트씩 잘라서 x,y 값 사용 
//////////////////////////////////
//				//				//
//		y		//		 x		//
//				//				//
//////////////////////////////////
//HIWORD(LPARAM)  // LOWORD(LPALRAM)

// LOWORD
// x의 값

// HIWORD
// y의 값




CMouse::CMouse(HWND handle)
	: handle(handle)
	, position(0, 0)
	, wheelValue(0), wheelPrevValue(0), wheelMoveValue(0)
{
	ZeroMemory(buttonStatus, sizeof(byte) * 8); // 포인터로 메모리 초기화
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
	if (iMessage == WM_MOUSEMOVE)	// 마우스 커서 움직임 
	{
		position.x = (float)LOWORD(lParam); // 마우스 커서 위치 X의 값
		position.y = (float)HIWORD(lParam);	// 마우스 커서 위치 Y의 값
	}

	if (iMessage == WM_MOUSEWHEEL)	// 마우스 휠 
	{
		short temp = (short)HIWORD(wParam);	// 마우스 휠 움직임?

		wheelPrevValue = wheelValue;
		wheelValue += (float)temp; // 마우스 휠의 움직임을 wheelValue에 할당 
	}
}

void CMouse::Update()
{
	memcpy(buttonPrevStatus, buttonStatus, sizeof(byte) * 8);	// 메모리 복사 함수 

	ZeroMemory(buttonStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);


	buttonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;	// 마우스 왼쪽 버튼 눌렸는지 안눌렸는지
	buttonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;	// 오른쪽			
	buttonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;	// 중간 (마우스 휠 버튼?)

	for (UINT i = 0; i < 8; i++)
	{
		byte prevStatus = buttonPrevStatus[i];
		byte status = buttonStatus[i];

		if (prevStatus == 0 && status == 1)	// 버튼을 안 눌렀다가 누르면 
			buttonMap[i] = Button::Down;	// Down
		else if (prevStatus == 1 && status == 0)	// 버튼을 눌렀다 땠으면
			buttonMap[i] = Button::Up;		//Up
		else if (prevStatus == 1 && status == 1)	// 버튼을 계속 누르고 있으면
			buttonMap[i] = Button::Press;	//Press
		else // 아무 버튼도 누르지 않으면 
			buttonMap[i] = Button::None;	//None
	}

	UINT buttonStatus = GetTickCount();	// 마우스 버튼의 작동 확인 직후의 시간을 bottonStatus에 저장 

	// 더블클릭 판별 
	for (UINT i = 0; i < 8; i++)
	{
		if (buttonMap[i] == Button::Down) // 마우스 버튼이 안 눌려있다가 눌렸을 때 
		{
			if (buttonCount[i] == 1)	// bottonCount가 1일 때 
			{
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime) // 운영체제의 더블 클릭간격 측정 시간보다 더블 클릭 속도가 느리면 
					buttonCount[i] = 0; // bottomCount 는 0
			}
			buttonCount[i]++;	// bottonCount 는 1 증가 

			if (buttonCount[i] == 1)	// bottonCount가 1일 때 
				startDoubleClickTime[i] = buttonStatus; // 다시 버튼 클릭 여부 확인 직후 시간을 저장(여기서는 버튼이 때졌다가 눌렸을때의 시간)
		}

		// 마우스 버튼이 때지는 순간에 클릭 여부를 판단해야 하므로 더블클릭 여부는 Button::Up일 때 판별
		if (buttonMap[i] == Button::Up) // 마우트 버튼이 눌려있다가 땠을 때
		{
			if (buttonCount[i] == 1)	// bottonCount가 1일 때 
			{
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime) // 운영체제의 더블클릭간격 측정 시간보다 더블 클릭 속도가 느리면 
					buttonCount[i] = 0;	// bottonCount는 0
			}
			else if (buttonCount[i] == 2)	// bottonCount가 2일 때 
			{
				if (buttonStatus - startDoubleClickTime[i] <= doubleClickTime)	// 운영체제의 더블클릭간격 측정 시간보다 더블 클릭 속도가 빠르면 
					buttonMap[i] = Button::DoubleClick;	// buttonMap 에 DoubleClick 할당 

				buttonCount[i] = 0; // buttonCount에 0 할당 
			}
		}
	}


	POINT point;

	GetCursorPos(&point);	// 마우스 커서의 좌표 
	ScreenToClient(handle, &point);	// GetCursorPos 함수로 커서의 좌표를 얻어 온 후 ScreenToClient함수로 윈도우 기준으로 변환
	//ClientToScreen(handle, &point);

	wheelPrevValue = wheelValue;
	wheelMoveValue = wheelValue - wheelPrevValue;	// 마우스 휠 움직임 지금 위치에서 이전위치 계속 빼주면 휠의 움직임 알 수 있음
}