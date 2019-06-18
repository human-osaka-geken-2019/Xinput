#include "Game.h"
#include "Object.h"

using DirectX9Wrapper::Dx9;
using namespace Xinput;

int Game::m_Score = 0;
Commands Game::m_Commands;
Game::Game()
{

}

void Game::Update()
{
	Inputed();
	m_Commands.Update();
}

void Game::Render()
{
	static float bgTu = 0;
	static float bgTv = 0;

	CUSTOMVERTEX customVertex[4]{
		{0,					0,					0,1,0xFFFFFFFF,bgTu,		bgTv},
		{WindowSize::WIDTH,	0,					0,1,0xFF00FFFF,bgTu + 1.0f, bgTv},
		{WindowSize::WIDTH,	WindowSize::HEIGHT,	0,1,0xFFFF00FF,bgTu + 1.0f, bgTv + 1.f},
		{0,					WindowSize::HEIGHT,	0,1,0xFFFFFF00,bgTu,		bgTv + 1.f}
	};
	m_Dx9->pD3Device->SetTexture(0, m_Dx9->pTexture[L"BG_TEX"]);
	m_Dx9->pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, customVertex, sizeof(CUSTOMVERTEX));

	bgTu += 0.01f;
	//bgTv -= 0.01f;
	RECT turnPos = { 0, 100, 1250, 720 };
	WCHAR turn[64];
	swprintf_s(turn, 64, L"Turn:%d\nScore:%d", m_Commands.Turn(),m_Score);
	m_Dx9->pFont[L"TURN"]->DrawText(
		NULL,		// NULL
		turn,		// 描画テキスト
		-1,			// 全て表示
		&turnPos,		// 表示範囲
		DT_RIGHT,	// 文字の寄り
		0xFFFFFFFF		// color
	);	m_Commands.Render();
}

void Game::Register(Dx9* dx9)
{
	m_Dx9 = dx9;
}

void Game::LoadTexture(LPCWSTR FilePath, tstring TextureKey)
{
	D3DXCreateTextureFromFile(
		m_Dx9->pD3Device,
		FilePath,
		&m_Dx9->pTexture[TextureKey]);

}

void Game::LoadResource()
{
	Object::SetDx(m_Dx9);
	LoadTexture(L"Resource/Texture/button/a.png", L"A_TEX");
	LoadTexture(L"Resource/Texture/button/b.png", L"B_TEX");
	LoadTexture(L"Resource/Texture/button/x.png", L"X_TEX");
	LoadTexture(L"Resource/Texture/button/y.png", L"Y_TEX");
	LoadTexture(L"Resource/Texture/button/rb.png",L"RB_TEX");
	LoadTexture(L"Resource/Texture/button/lb.png",L"LB_TEX");
	LoadTexture(L"Resource/Texture/button/button.png", L"NULL_BUTTON_TEX");
	LoadTexture(L"Resource/Texture/button/lt.png", L"LT_TEX");
	LoadTexture(L"Resource/Texture/button/rt.png", L"RT_TEX");
	LoadTexture(L"Resource/Texture/button/l3.png", L"L3_TEX");
	LoadTexture(L"Resource/Texture/button/r3.png", L"R3_TEX");
	LoadTexture(L"Resource/Texture/button/start.png", L"START_TEX");
	LoadTexture(L"Resource/Texture/button/back.png", L"BACK_TEX");
	LoadTexture(L"Resource/Texture/button/up.png", L"UP_TEX");
	LoadTexture(L"Resource/Texture/button/down.png", L"DOWN_TEX");
	LoadTexture(L"Resource/Texture/button/left.png", L"LEFT_TEX");
	LoadTexture(L"Resource/Texture/button/right.png", L"RIGHT_TEX");

	LoadTexture(L"Resource/Texture/starRain.jpg", L"BG_TEX");

	D3DXCreateFont(
		m_Dx9->pD3Device,
		50,//高さ
		30,//幅
		FW_DEMIBOLD,//文字の太さ
		NULL,//ミップマップレベル
		FALSE,//イタリックであるか？
		SHIFTJIS_CHARSET,//文字セット
		OUT_DEFAULT_PRECIS,//出力精度
		DEFAULT_QUALITY,//出力品質
		FIXED_PITCH | FF_SCRIPT,//ピッチとファミリ
		L"ＭＳ　ゴシック",//フォント名
		&m_Dx9->pFont[L"TURN"]);

	SoundInterface::sound.AddSimultaneousFile(L"Resource/Sound/correct5.mp3",L"HIT",Sound::SE);
	SoundInterface::sound.AddSimultaneousFile(L"Resource/Sound/incorrect1.mp3", L"FAUL", Sound::SE);
	SoundInterface::sound.AddSimultaneousFile(L"Resource/Sound/eye-shine1.mp3", L"SHINE", Sound::SE);
}

void Game::Inputed() {
	static int buttonKeyID = 0;
	static int prevbuttonKeyID = 1;
	m_XinputDevice.DeviceUpdate();
	if (m_XinputDevice.GetButton(ButtonA) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonA);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonB) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonB);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonX) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonX);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonY) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonY);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonRB) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonRB);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonLB) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonLB);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonStart) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonStart);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonBack) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonBack);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonUP) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonUP);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonDOWN) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonDOWN);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonLEFT) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonLEFT);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonRIGHT) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonRIGHT);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonLeftThumb) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonLeftThumb);
		return;
	}
	if (m_XinputDevice.GetButton(ButtonRightThumb) == PadPush)
	{
		m_Commands.InputedCtrl(Commands::ButtonRightThumb);
		return;
	}
	if (m_XinputDevice.GetLeftTriggerState() == PadPush)
	{
		m_Commands.InputedCtrl(Commands::LTrigger);
		return;
	}
	if (m_XinputDevice.GetRightTriggerState() == PadPush)
	{
		m_Commands.InputedCtrl(Commands::RTrigger);
#ifdef _DEBUG
		m_Commands.Turn(14);
#endif
		return;
	}

}

int Game::AddScore()
{
	int scoreLevel = 100;
	int turn = m_Commands.Turn();
	if (turn > 10) scoreLevel = 125;
	if (turn > 20) scoreLevel = 150;
	if (turn > 30) scoreLevel = 175;
	if (turn > 40) scoreLevel = 200;
	if (turn > 50) scoreLevel = 250;
	if (turn > 60) scoreLevel = 300;
	if (turn > 100) scoreLevel = 1000;
	m_Score += scoreLevel;
	return 0;
}
