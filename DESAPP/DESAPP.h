
// DESAPP.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDESAPPApp:
// �йش����ʵ�֣������ DESAPP.cpp
//

class CDESAPPApp : public CWinApp
{
public:
	CDESAPPApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDESAPPApp theApp;