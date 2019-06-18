#include "WriteDebugLog.h"



WriteDebugLog::WriteDebugLog()
{
}


WriteDebugLog::~WriteDebugLog()
{
}


const char* WriteDebugLog::ToChar(const wchar_t* pSrc) {
	// �K�v�ȃo�C�g���̎擾
	int charStrLength = WideCharToMultiByte(CP_THREAD_ACP, 0, pSrc, -1, NULL, 0, NULL, NULL);
	char* pCharStr = new char[charStrLength];

	// �ϊ�
	WideCharToMultiByte(CP_THREAD_ACP, 0, pSrc, int(wcslen(pSrc)) + 1, pCharStr, charStrLength, NULL, NULL);

	return	pCharStr;
}

#ifdef UNICODE
void WriteDebugLog::OutputStrWithKey(const char * pStr, const wchar_t * pKey)
{
	const char* pCharKey = ToChar(pKey);
	OutputDebugString(pStr, pCharKey);
	delete[] pCharKey;
}
#else
void WriteDebugLog::OutputStrWithKey(const char* pStr, const char* pKey)
{
	OutputDebugString(pStr, pKey);
}
#endif


