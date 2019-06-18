#pragma once
#include "DX/Dx9.h"
#include "Xinput/XinputDevice.h"

#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#include "Sound/Sound.h"

#include "Graphic.h"
class SoundInterface {
public:
	static Sound sound;
};
class WindowSize {
public:
	static const int WIDTH = 1280;
	static const int HEIGHT = 720;
};
