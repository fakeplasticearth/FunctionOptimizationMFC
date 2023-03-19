
// FunctionOptimizationMFC.h: основной файл заголовка для приложения FunctionOptimizationMFC
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CFunctionOptimizationMFCApp:
// Сведения о реализации этого класса: FunctionOptimizationMFC.cpp
//

class CFunctionOptimizationMFCApp : public CWinAppEx
{
public:
	CFunctionOptimizationMFCApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFunctionOptimizationMFCApp theApp;
