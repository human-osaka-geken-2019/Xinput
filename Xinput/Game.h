#pragma once
#include "Main.h"
#include "Commands.h"

class Game {
public:

	Game();
	void Update();
	void Render();
	void Register(DirectX9Wrapper::Dx9* dx9);
	void LoadTexture(LPCWSTR FilePath, tstring TextureKey);
	void LoadResource();
	void Inputed();
	static int AddScore();
private:
	XinputDevice m_XinputDevice;
	DirectX9Wrapper::Dx9* m_Dx9;
	static Commands m_Commands;
	static int m_Score;
};
