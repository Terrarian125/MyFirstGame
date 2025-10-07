#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256] = { 0 };
	//マウスインプット
	LPDIRECTINPUTDEVICE8 pMouseDevice = nullptr;
	DIMOUSESTATE mouseState; //マウスの状態
	DIMOUSESTATE prevMouseState;//前回のマウス状態

	XMVECTOR mouseposition;
};

	void Input::Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		//マウス
		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice, nullptr);
		pMouseDevice->SetDataFormat(&c_dfDIMouse);
		pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Input::Update()
	{
		//前回のキー状態を保存
		memcpy(prevKeyState, keyState, sizeof(keyState));
		for (auto i = 0; i < 256; i++)
		{
			prevKeyState[i] = keyState[i];
		}
		pKeyDevice->Acquire(); //キーボードの制御を取得
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);

		//マウスの状態を保存
		pMouseDevice->Acquire();
		memcpy(&prevMouseState, &mouseState, sizeof(mouseState));
		pMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);
	}

	bool Input::IsKey(int keyCode)
	{
		//例：ESCキーで真を返す
		if (keyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool Input::IsKeyUp(int keyCode)
	{
		//今は押してなくて、前回は押してる 解放 = Release
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80) )
		{
			return true;
		}
		return false;
	}

	bool Input::IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない 押下 = Push
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80) )
		{
			return true;
		}
		return false;
	}

	XMVECTOR Input::GetMousePosition()
	{
		return mouseposition;
	}

	void Input::SetMousePosition(int x, int y)
	{
		mouseposition = { (float)x, (float)y, 0.0f, 1.0f };
	}

	bool Input::IsMouseButton(int btnCode)
	{
		if (mouseState.rgbButtons[btnCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool Input::IsMouseButtonUp(int btnCode)
	{
		if (!IsMouseButton(btnCode) && (prevMouseState.rgbButtons[btnCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool Input::IsMouseButtonDown(int btnCode)
	{
		if (IsMouseButton(btnCode) && !(prevMouseState.rgbButtons[btnCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	void Input::Release()
	{
		SAFE_RELEASE(pDInput);
		//SAFE_RELEASE(pKeyDevice);
	}