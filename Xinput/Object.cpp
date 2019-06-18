#include "Object.h"
DirectX9Wrapper::Dx9* Object::m_Dx9 = nullptr;


void Object::CreateSquareVertex(CUSTOMVERTEX* Vertex, BASE_POSITION* Central, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {
	Vertex[0] = { Central->position.X - Central->scale.X, Central->position.Y - Central->scale.Y, 1.f, 1.f, color, tu, tv };
	Vertex[1] = { Central->position.X + Central->scale.X, Central->position.Y - Central->scale.Y, 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { Central->position.X + Central->scale.X, Central->position.Y + Central->scale.Y, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { Central->position.X - Central->scale.X, Central->position.Y + Central->scale.Y, 1.f, 1.f, color, tu, tv + scaleTv };
}
//void Object::CreateSquareVertex(CUSTOMVERTEX* Vertex, float x, float y, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {
//	Vertex[0] = { 0,  0, 1.f, 1.f, color, tu, tv };
//	Vertex[1] = { x, 0, 1.f, 1.f, color, tu + scaleTu, tv };
//	Vertex[2] = { x, y, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
//	Vertex[3] = { 0,  y, 1.f, 1.f, color, tu, tv + scaleTv };
//}
//void Object::CreateSquareVertex(CUSTOMVERTEX* Vertex, float x, float y, float xScale, float yScale, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {
//	Vertex[0] = { x,  y, 1.f, 1.f, color, tu, tv };
//	Vertex[1] = { xScale, y, 1.f, 1.f, color, tu + scaleTu, tv };
//	Vertex[2] = { xScale, yScale, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
//	Vertex[3] = { x,  yScale, 1.f, 1.f, color, tu, tv + scaleTv };
//}
//void Object::CreateSquareVertex(CUSTOMVERTEX* Vertex, RECT rect, DWORD color, float tu, float tv, float scaleTu, float scaleTv) {
//
//	Vertex[0] = { static_cast<float>(rect.left), static_cast<float>(rect.top),    1.f, 1.f, color, tu, tv };
//	Vertex[1] = { static_cast<float>(rect.right),static_cast<float>(rect.top),    1.f, 1.f, color, tu + scaleTu, tv };
//	Vertex[2] = { static_cast<float>(rect.right),static_cast<float>(rect.bottom), 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
//	Vertex[3] = { static_cast<float>(rect.left), static_cast<float>(rect.bottom), 1.f, 1.f, color, tu, tv + scaleTv };
//
//}

