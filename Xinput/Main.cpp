﻿#include "Main.h"

#include "Game.h"

//	メモリリーク確認用マクロ
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
Sound SoundInterface::sound;
/**
* @brief コールバック関数
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

/**
* @brief ウィンドウ枠の設定
*/
void SettingWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow);

/**
* @brief メッセージループ
*/
int MessageLoop();


using DirectX9Wrapper::Dx9;

const TCHAR API_NAME[10] = _T("Sample");

static HWND hWnd;
Dx9 dx9;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	//	メモリリーク確認用マクロ
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SettingWindow(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
	dx9.BuildDXDevice(hWnd,_T("Blank.jpg"));

	//	テクスチャの読み込み
	D3DXCreateTextureFromFile(
		dx9.pD3Device,
		_T("Blank.jpg"),
		&dx9.pTexture[_T("test")]);
	MessageLoop();

	dx9.Release();
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		//! Alt + 特殊キーの処理に使う
	case WM_SYSKEYDOWN:
		switch (wp) {
			//! Alt + Enterを押すと切り替え
		case VK_RETURN:
			return 0;
			//! Alt + F4を押すと実行終了
		case VK_F4:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;
		default:
			return 0;
		}
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}


void SettingWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS Wndclass;

	//Window初期化情報の設定
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = API_NAME;	//クラス名
	//Windowの登録
	RegisterClass(&Wndclass);
	//Windowの生成
	hWnd = CreateWindow(
		API_NAME,					//ウィンドウのクラス名
		API_NAME, 					//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの横方向の位置x
		CW_USEDEFAULT,						// ウィンドウの縦方向の位置y
		WindowSize::WIDTH,						// Width（幅）
		WindowSize::HEIGHT,						// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
	);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}

int MessageLoop()
{
	Game game;
	game.Register(&dx9);
	game.LoadResource();
	//	システム時間を取得
	DWORD SyncPrev = timeGetTime();
	DWORD SyncCurr;

	//	Windowsのメッセージの保存先
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	timeBeginPeriod(1);
	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncCurr = timeGetTime();
			//1秒間に60回この中に入る
			if (SyncCurr - SyncPrev >= 1000 / 60)
			{
				dx9.pD3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
				dx9.pD3Device->BeginScene();
				dx9.UpdateKeyStatus();

				game.Update();
				game.Render();

				dx9.pD3Device->EndScene();
				dx9.pD3Device->Present(0, 0, 0, 0);

				SyncPrev = SyncCurr;
			}
		}
	}
	timeEndPeriod(1);
	return (int)msg.wParam;
}

