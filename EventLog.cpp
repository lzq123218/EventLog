#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

//
// MessageId: SVC_ERROR
//
// MessageText:
//
//  An error has occurred (%2).
//
#define		SVC_ERROR      ((DWORD)0xC0020001L)
#define		EVENT_SOURCE   TEXT("EvtSrcName07201449")

VOID LogFailureToEvtLOG(LPTSTR TargetStr) //应用程序 日志
{
	HANDLE			hEventSrc;
	LPCTSTR			lpszStrings[3];
	TCHAR			DataToRecord[120];

	hEventSrc = RegisterEventSource(NULL, EVENT_SOURCE);
	if (NULL != hEventSrc)
	{
		StringCchPrintf(DataToRecord, 80, TEXT("%s failed with %d"), TargetStr, GetLastError());

		lpszStrings[0] = TEXT("Random data......");
		lpszStrings[1] = DataToRecord;
		lpszStrings[2] = TEXT("New line to write there!");     

		ReportEvent(hEventSrc,       // event log handle
			EVENTLOG_ERROR_TYPE,		// event type
			0,							// event category
			SVC_ERROR,					// event identifier
			NULL,						// no security identifier   
			3,							// size of lpszStrings array
			0,							// no binary data
			lpszStrings,				// array of strings
			NULL);						// no binary data

		DeregisterEventSource(hEventSrc);
	}
}

int main()
{
	int a = 123;    

	printf("\nPrepare for ok!");

	LogFailureToEvtLOG(TEXT("FLAVOR......"));

	system("pause");

	return 0;
}
