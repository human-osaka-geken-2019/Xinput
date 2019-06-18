#include "Commands.h"
#include "Game.h"
#include <time.h>


Commands::Commands()
{
	m_ComandInput.resize(INIT_CMD_NUM);
	m_ComandPresentment.resize(INIT_CMD_NUM);
	for (auto& input : m_ComandInput) {
		input = IndexLIMIT;
	}
	ComandMake();
}

Commands::~Commands()
{
	std::vector<COMMAND_INDEX>().swap(m_ComandInput);
	std::vector<COMMAND_INDEX>().swap(m_ComandPresentment);

}

void Commands::Update()
{
	INPUT_RESULT checkedComand = NONE;
	if (m_ComandCount < m_ComandPresentment.size())
	{
		checkedComand = ComandCheck();
		if (SUCCESS == checkedComand)
		{
			SoundInterface::sound.OneShotSimultaneous(L"HIT");
		}
		if (MISS == checkedComand)
		{
			SoundInterface::sound.OneShotSimultaneous(L"FAUL");
		}
	}
	else
	{
		checkedComand = ComandCheck();
		if (SUCCESS == checkedComand)
		{
			m_ComandCount = 0;
			m_PrevComandCount = 0;
			++m_Turn;
			SoundInterface::sound.OneShotSimultaneous(L"SHINE");
			Game::AddScore();
			for (auto& input : m_ComandInput) {
				input = IndexLIMIT;
			}
			if (0 == m_Turn % 15 && m_Turn > 0 && 12 > m_ComandPresentment.size()) {
				m_ComandPresentment.push_back(IndexLIMIT);
				m_ComandInput.push_back(IndexLIMIT);
			}
			ComandMake();

		}
		if (MISS == checkedComand)
		{

		}
	}
	m_PrevComandCount = m_ComandCount;
}

void Commands::Render()
{
	CUSTOMVERTEX Vertex[4];
	const float buttonSize = 60.f;
	for (int i = 0; i < m_ComandPresentment.size(); ++i) {
		BASE_POSITION InputComand = { VECTOR2(100.f + (i * 100.f),300.f),VECTOR2(buttonSize,buttonSize) };
		CreateSquareVertex(Vertex, &InputComand);
		Drow(Vertex, ComandButtonTexture(m_ComandPresentment[i]));
	}

	for (int i = 0; i < m_ComandInput.size(); ++i) {
		BASE_POSITION InputComand = { VECTOR2(100.f + (i * 100.f),500.f),VECTOR2(buttonSize,buttonSize) };
		CreateSquareVertex(Vertex, &InputComand);
		Drow(Vertex, ComandButtonTexture(m_ComandInput[i]));
	}

}

char Commands::ComandButton(COMMAND_INDEX comand)
{
	switch (comand) {
	case ButtonA:
		return 'A';
	case ButtonB:
		return 'B';
	case ButtonX:
		return 'X';
	case ButtonY:
		return 'Y';
	case ButtonRB:
		return 'R';
	case ButtonLB:
		return 'L';
	}
	return ' ';
}

void Commands::ComandMake() {
	srand((unsigned int)time(NULL));
	if (m_Turn == 0)
	{
		for (auto& command : m_ComandPresentment) {
			command = static_cast<COMMAND_INDEX>(rand() % 4);
		}
	}
	else if (m_Turn <= 10 && m_Turn<20) {
		for (auto& command : m_ComandPresentment) {
			command = static_cast<COMMAND_INDEX>(rand() % 6);
		}
	}
	else if (m_Turn <= 20 && m_Turn < 30) {
		for (auto& command : m_ComandPresentment) {
			command = static_cast<COMMAND_INDEX>(rand() % 8);
		}
	}
	else if (m_Turn <= 30 && m_Turn < 40) {
		for (auto& command : m_ComandPresentment) {
			command = static_cast<COMMAND_INDEX>(rand() % 11);
		}
	}
	else {
		for (auto& command : m_ComandPresentment) {
			command = static_cast<COMMAND_INDEX>(rand() % 15);
		}
	}
}


Commands::INPUT_RESULT Commands::ComandCheck()
{
	if (m_PrevComandCount == m_ComandCount) return NONE;
	for (int i = 0; i < m_ComandCount; i++) {
		if (m_ComandInput[i] == IndexLIMIT) {
			return NONE;
		}
		else if (m_ComandPresentment[i] == m_ComandInput[i]) {
			if (i == m_ComandCount - 1) {
				return SUCCESS;
			}
		}
		else if (m_ComandPresentment[i] != m_ComandInput[i]) {
			if (i == m_ComandCount - 1) {
				m_ComandCount -= 1;
				return MISS;
			}
		}
	}
	return NONE;
}

tstring Commands::ComandButtonTexture(COMMAND_INDEX comand)
{
	switch (comand) {
	case ButtonA:
		return L"A_TEX";
	case ButtonB:
		return L"B_TEX";
	case ButtonX:
		return L"X_TEX";
	case ButtonY:
		return L"Y_TEX";
	case ButtonRB:
		return L"RB_TEX";
	case ButtonLB:
		return L"LB_TEX";
	case ButtonStart:
		return L"START_TEX";
	case ButtonBack:
		return L"BACK_TEX";
	case ButtonUP:
		return L"UP_TEX";
	case ButtonDOWN:
		return L"DOWN_TEX";
	case ButtonLEFT:
		return L"LEFT_TEX";
	case ButtonRIGHT:
		return L"RIGHT_TEX";
	case ButtonLeftThumb:
		return L"L3_TEX";
	case ButtonRightThumb:
		return L"R3_TEX";
	case LTrigger:
		return L"LT_TEX";
	case RTrigger:
		return L"RT_TEX";
	default:
		return L"NULL_BUTTON_TEX";
	}
}

void Commands::InputedCtrl(COMMAND_INDEX index) {
	static int buttonKeyID = 0;
	static int prevbuttonKeyID = 1;
	if (m_ComandCount >= m_ComandPresentment.size()) return;
	switch (index) {
	case ButtonA:
			m_ComandInput[m_ComandCount] = ButtonA;
			break;
	case ButtonB:

			m_ComandInput[m_ComandCount] = ButtonB;
			break;
	case ButtonX:

			m_ComandInput[m_ComandCount] = ButtonX;
			break;
	case ButtonY:

			m_ComandInput[m_ComandCount] = ButtonY;
			break;
	case ButtonRB:

			m_ComandInput[m_ComandCount] = ButtonRB;
			break;
	case ButtonLB:

			m_ComandInput[m_ComandCount] = ButtonLB;
			break;
	case ButtonStart:
		m_ComandInput[m_ComandCount] = ButtonStart;
		break;
	case ButtonBack:
		m_ComandInput[m_ComandCount] = ButtonBack;
		break;
	case ButtonUP:
		m_ComandInput[m_ComandCount] = ButtonUP;
		break;
	case ButtonDOWN:
		m_ComandInput[m_ComandCount] = ButtonDOWN;
		break;
	case ButtonLEFT:
		m_ComandInput[m_ComandCount] = ButtonLEFT;
		break;
	case ButtonRIGHT:
		m_ComandInput[m_ComandCount] = ButtonRIGHT;
		break;
	case ButtonLeftThumb:
		m_ComandInput[m_ComandCount] = ButtonLeftThumb;
		break;
	case ButtonRightThumb:
		m_ComandInput[m_ComandCount] = ButtonRightThumb;
		break;
	case LTrigger:
		m_ComandInput[m_ComandCount] = LTrigger;
		break;
	case RTrigger:
		m_ComandInput[m_ComandCount] = RTrigger;
		break;
	}
	if (m_ComandCount < m_ComandPresentment.size()) {
		m_ComandCount += 1;
	}

}

