#pragma once
#include "Object.h"
#include "Main.h"
#include <vector>

class Commands :public Object
{
public:
	enum INPUT_RESULT {
		NONE,
		SUCCESS,
		MISS,
	};
	enum COMMAND_INDEX
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		//! R1ボタン
		ButtonRB,
		//! L1ボタン
		ButtonLB,
		ButtonStart,
		ButtonBack,
		ButtonUP,
		ButtonDOWN,
		ButtonLEFT,
		ButtonRIGHT,
		//!L3ボタン
		ButtonLeftThumb,
		//!R3ボタン
		ButtonRightThumb,
		LTrigger,
		RTrigger,
		IndexLIMIT,
	};

	Commands();
	~Commands();
	void Update();
	void Render();
	char ComandButton(COMMAND_INDEX comand);
	void ComandMake();
	INPUT_RESULT ComandCheck();

	tstring ComandButtonTexture(COMMAND_INDEX comand);

	void InputedCtrl(COMMAND_INDEX index);
#ifdef _DEBUG
	void Turn(int num) {
		m_Turn = num;
	}
#endif
	int Turn() {
		return m_Turn;
	}

private:
	std::vector<COMMAND_INDEX> m_ComandInput;
	std::vector<COMMAND_INDEX> m_ComandPresentment;
	int m_Turn = 0;
	int m_ComandCount = 0;
	int m_PrevComandCount = 0;
	const int INIT_CMD_NUM = 5;
};

