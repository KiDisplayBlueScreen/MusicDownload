#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <objbase.h>
#include <winhttp.h>

#pragma warning(disable:4996)
#pragma comment(lib,"Winhttp.lib")
#pragma comment(lib,"Ole32.lib");
using namespace std;

WCHAR SearchWord[50] = { 0 };
LPCSTR MainURL = "http://player.kuwo.cn/webmusic/getsjplayinfo?flag=6&pn=1&pr=500&type=music&key=";

BYTE HttpRequest[] =
{ 
0x55,0x73,0x65,0x72,0x2D,0x41,0x67,0x65,0x6E,0x74,0x3A,0x20,0x4D,0x6F,0x7A,0x69,
0x6C,0x6C,0x61,0x2F,0x35,0x2E,0x30,0x20,0x28,0x63,0x6F,0x6D,0x70,0x61,0x74,0x69,
0x62,0x6C,0x65,0x3B,0x20,0x4D,0x53,0x49,0x45,0x20,0x39,0x2E,0x30,0x3B,0x20,0x57,
0x69,0x6E,0x64,0x6F,0x77,0x73,0x20,0x4E,0x54,0x20,0x36,0x2E,0x31,0x3B,0x20,0x57,
0x4F,0x57,0x36,0x34,0x3B,0x20,0x54,0x72,0x69,0x64,0x65,0x6E,0x74,0x2F,0x35,0x2E,
0x30,0x29,0x0D,0x0A,0x41,0x63,0x63,0x65,0x70,0x74,0x3A,0x20,0x74,0x65,0x78,0x74,
0x2F,0x68,0x74,0x6D,0x6C,0x2C,0x20,0x61,0x70,0x70,0x6C,0x69,0x63,0x61,0x74,0x69,
0x6F,0x6E,0x2F,0x78,0x68,0x74,0x6D,0x6C,0x2B,0x78,0x6D,0x6C,0x2C,0x20,0x2A,0x2F,
0x2A,0x0D,0x0A,0x41,0x63,0x63,0x65,0x70,0x74,0x2D,0x45,0x6E,0x63,0x6F,0x64,0x69,
0x6E,0x67,0x3A,0x20,0x67,0x62,0x6B,0x2C,0x20,0x47,0x42,0x32,0x33,0x31,0x32,0x0D,
0x0A,0x41,0x63,0x63,0x65,0x70,0x74,0x2D,0x4C,0x61,0x6E,0x67,0x75,0x61,0x67,0x65,
0x3A,0x20,0x7A,0x68,0x2D,0x63,0x6E,0x0D,0x0A,0x43,0x6F,0x6E,0x74,0x65,0x6E,0x74,
0x2D,0x54,0x79,0x70,0x65,0x3A,0x20,0x61,0x70,0x70,0x6C,0x69,0x63,0x61,0x74,0x69,
0x6F,0x6E,0x2F,0x78,0x2D,0x77,0x77,0x77,0x2D,0x66,0x6F,0x72,0x6D,0x2D,0x75,0x72,
0x6C,0x65,0x6E,0x63,0x6F,0x64,0x65,0x64,0x0D,0x0A,0x43,0x61,0x63,0x68,0x65,0x2D,
0x43,0x6F,0x6E,0x74,0x72,0x6F,0x6C,0x3A,0x20,0x6E,0x6F,0x2D,0x63,0x61,0x63,0x68,
0x65,0x0D,0x0A 
};
LPWSTR lpSearchWord = SearchWord;
CHAR cSearchWord[50] = { 0 };
PBYTE EaseMultiByteToWideChar(LPSTR Target);
LPSTR EaseWideCharToMultiByte(PBYTE Target);
ULONG SendHttpRequest(LPSTR URL);
int main()
{

	
	PBYTE pBSearchWord;
	LPSTR SearchWordOutPut;
	CHAR Percent[50] = { 0 };
	wcin >> lpSearchWord;
	wcout << SearchWord << endl;
	cin >> cSearchWord;
	pBSearchWord=EaseMultiByteToWideChar(cSearchWord);

	SearchWordOutPut=EaseWideCharToMultiByte(pBSearchWord + 8);
	int Length = strlen(SearchWordOutPut);

	//sprintf(Percent, "%8X", SearchWordOutPut);
	LPSTR pPercent = Percent;
	for (int i = 0; i <Length; i++)
	{
		sprintf(pPercent, "%X", *(PBYTE)SearchWordOutPut);
		pPercent+=2;
		(PBYTE)(SearchWordOutPut)++;
	}
	pPercent = Percent;
	PBYTE pTempPercent = (PBYTE)Percent;
	CHAR Temp[3] = { 0 };
	Temp[0] = 0x25;
	BYTE Result[50] = { 0 };
	while (*pTempPercent != 0)
	{
		Temp[1] = *pTempPercent;
		Temp[2] = *(pTempPercent + 1);
		strcat_s((PCHAR)Result, 50, Temp);
		pTempPercent += 2;
	}


	
	PBYTE FinalURL = (PBYTE)malloc(strlen(MainURL) + sizeof(Result));
	memset(FinalURL, 0, strlen(MainURL) + sizeof(Result));

	strcat_s((PCHAR)FinalURL, strlen(MainURL) + sizeof(Result), MainURL);
	strcat_s((PCHAR)FinalURL, strlen(MainURL) + sizeof(Result), (PCHAR)Result);


	cout << FinalURL;
	

	



    std::cout << "Hello World!\n"; 
	system("pause");
}







PBYTE EaseMultiByteToWideChar(LPSTR Target)
{
	WCHAR OutPut[20] = { 0 };
	ULONG BytesNeed=MultiByteToWideChar(CP_ACP, 0, Target, -1, OutPut, 0);
	//BytesNeed *= 2;
	PVOID Buffer = malloc(BytesNeed*2+8);
	memset(Buffer, 0, BytesNeed * 2+8);
	*((PDWORD)Buffer) = 1;
	*((PDWORD)Buffer + 1) = BytesNeed*2;
	MultiByteToWideChar(0x3A8, 0, Target, -1, (LPWSTR)((PBYTE)Buffer+8), BytesNeed);
	return (PBYTE)Buffer;
}

LPSTR EaseWideCharToMultiByte(PBYTE Target)
{
	CHAR OutPut[20] = { 0 };
	ULONG BytesNeed = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)Target, -1, OutPut, 0,0,0);

	PVOID Buffer = malloc(BytesNeed * 2 + 1);
	memset(Buffer, 0, BytesNeed * 2 + 1);

	WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)Target, -1, (LPSTR)Buffer, BytesNeed * 2 + 1, 0, 0);

	return (LPSTR)Buffer;

}
ULONG SendHttpRequest(LPSTR URL)
{
	WCHAR wCharHttpRequest[0x200] = { 0 };
	LPCWSTR KuWo = L"player.kuwo.cn";
	CoInitialize((PVOID)NULL);
	PWCHAR wUrl = (PWCHAR)malloc(strlen(URL) * 2 + 2);
	memset(wUrl, 0, strlen(URL) * 2 + 2);
	DWORD NumberOfBytesAvailable = 0;


	MultiByteToWideChar(0x3A8, 0, URL, -1, wUrl, strlen(URL) * 2 + 2);

	MultiByteToWideChar(0x3A8, 0, (LPCCH)HttpRequest, -1, wCharHttpRequest, 0x200);

	if (WinHttpCheckPlatform() != TRUE)
	{
		return GetLastError();
	}
	URL_COMPONENTS UrlCom = { 0 };
	UrlCom.dwStructSize = sizeof(URL_COMPONENTS);
	UrlCom.dwSchemeLength = 0xFFFFFFFF;
	UrlCom.dwHostNameLength = 0xFFFFFFFF;
	UrlCom.dwUrlPathLength = 0xFFFFFFFF;
	UrlCom.dwExtraInfoLength== 0xFFFFFFFF;

	if (WinHttpCrackUrl(wUrl, wcslen(wUrl), 0, &UrlCom)!=TRUE)
	{
		return GetLastError();
	}
	LPCWSTR pszProxyW = L"";
	LPWSTR HostName = UrlCom.lpszHostName;
	DWORD HostNameLength = UrlCom.dwHostNameLength;
	HINTERNET SessionHandle = WinHttpOpen(0, WINHTTP_ACCESS_TYPE_NO_PROXY, pszProxyW, 0, 0);
	if (SessionHandle == 0)
	{
		return GetLastError();
	}

	HINTERNET ConnectHandle = WinHttpConnect(SessionHandle, KuWo, UrlCom.nPort, 0);
	if (ConnectHandle == 0)
	{
		return GetLastError();
	}
	
	BOOL FeatureDisable = 1;

	HINTERNET RequestHandle = WinHttpOpenRequest(ConnectHandle, L"GET", UrlCom.lpszUrlPath,0,0,0,0);

	WinHttpSetTimeouts(RequestHandle, 0x7530, 0x7530, 0x7530, 0x7530);

	
	WinHttpSetOption(RequestHandle, WINHTTP_OPTION_DISABLE_FEATURE, &FeatureDisable , 4);

	

	WinHttpAddRequestHeaders(RequestHandle, wCharHttpRequest, wcslen(wCharHttpRequest), 0xA0000000);


	WinHttpSendRequest(RequestHandle, 0, 0, 0, 0, 0, 0);

	if (WinHttpReceiveResponse(RequestHandle, 0) != TRUE)
	{
		return;
	}




}