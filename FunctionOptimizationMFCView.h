
// FunctionOptimizationMFCView.h: интерфейс класса CFunctionOptimizationMFCView
//

#pragma once


class CFunctionOptimizationMFCView : public CView
{
protected: // создать только из сериализации
	CFunctionOptimizationMFCView() noexcept;
	DECLARE_DYNCREATE(CFunctionOptimizationMFCView)

// Атрибуты
public:
	CFunctionOptimizationMFCDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CFunctionOptimizationMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	UINT_PTR timer;
public:
	afx_msg void OnParameters();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // версия отладки в FunctionOptimizationMFCView.cpp
inline CFunctionOptimizationMFCDoc* CFunctionOptimizationMFCView::GetDocument() const
   { return reinterpret_cast<CFunctionOptimizationMFCDoc*>(m_pDocument); }
#endif

