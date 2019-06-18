#pragma once
#include "DX/Dx9.h"
#include "Graphic.h"

struct VECTOR2 {
	float X = 0;
	float Y = 0;
	VECTOR2(float x, float y) :X(x), Y(y) {};
	VECTOR2() {};
};
struct BASE_POSITION {
	VECTOR2 position;
	VECTOR2 scale;
};

class Object
{
public:
	static void SetDx(DirectX9Wrapper::Dx9* dx9) {
		m_Dx9 = dx9;
	}
	void Drow(CUSTOMVERTEX* customVertex,tstring texKey) {
		m_Dx9->pD3Device->SetTexture(0, m_Dx9->pTexture[texKey]);
		m_Dx9->pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, customVertex, sizeof(CUSTOMVERTEX));
	}
	void CreateSquareVertex(CUSTOMVERTEX* Vertex, BASE_POSITION* Central, DWORD color=0xFFFFFFFF, float tu=0, float tv=0, float scaleTu=1, float scaleTv=1);
private:
	static DirectX9Wrapper::Dx9* m_Dx9;
};

