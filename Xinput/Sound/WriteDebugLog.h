#pragma once
#include <stdio.h>
#include <windows.h>

class WriteDebugLog
{
public:
	WriteDebugLog();
	~WriteDebugLog();

	/// <summary>
	/// <see cref="wchar_t"/>�������<see cref="char"/>�ɕϊ�����B
	/// </summary>
	/// <param name="pSrc">�ϊ���������ւ̃|�C���^</param>
	/// <returns><see cref="wchar_t"/>�ɕϊ�����������ւ̃|�C���^</returns>
	/// <remarks>
	/// <para>���\�b�h���ŕK�v�ȃT�C�Y�̃������m�ۂ��s���A�ϊ���̕�����𐶐����܂��B</para>
	/// <para>�Ăяo�����ł͕s�v�ɂȂ����^�C�~���O�ŕԋp�l�̃|�C���^�̃�����������s���ĉ������B</para>
	/// </remarks>
	static const char* ToChar(const wchar_t* pSrc);

	/// <summary>
	/// �f�o�b�O���O���o�͂���B
	/// </summary>
	/// <param name="pStr">�o�͕�����</param>
	/// <param name="args">�u�����č������ޒl</param>
	template<class... Args>
	static void OutputDebugString(const char* pStr, Args... args) {
#ifdef _DEBUG
		char c[256];
		sprintf_s(c, pStr, args...);
		::OutputDebugStringA(c);
#endif
	}
#ifdef UNICODE
	static void OutputStrWithKey(const char* pStr, const wchar_t* pKey);
#else
	static void OutputStrWithKey(const char* pStr, const char* pKey);
#endif

};

