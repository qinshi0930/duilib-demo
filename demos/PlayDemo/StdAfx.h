#pragma once
//#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <objbase.h>
#include <zmouse.h>
#include <commdlg.h>
#include <shlobj.h>
#include <shellapi.h>

#include "..\..\dependency\DuiLib\UIlib.h"
#include "..\..\dependency\ffplayer\ffplayer.h"

#include <vector>
#include <string>

#include "DemoPrivate.h"

using namespace DuiLib;

#ifndef CMAKE
#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "..\\..\\lib\\DuiLib_d.lib")
#       pragma comment(lib, "..\\..\\lib\\ffplayer_d.lib")
#   else
#       pragma comment(lib, "..\\..\\lib\\DuiLibA_d.lib")
#       pragma comment(lib, "..\\..\\lib\\ffplayer_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "..\\..\\lib\\DuiLib.lib")
#       pragma comment(lib, "..\\..\\lib\\ffplayer.lib")
#   else
#       pragma comment(lib, "..\\..\\lib\\DuiLibA.lib")
#       pragma comment(lib, "..\\..\\lib\\ffplayer.lib")
#   endif
#endif
#endif


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.