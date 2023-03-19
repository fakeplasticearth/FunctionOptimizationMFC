#pragma once
#include "FunctionOptimizationMFCDoc.h"

// Диалоговое окно ParametersDialog

class ParametersDialog : public CDialog
{
	DECLARE_DYNAMIC(ParametersDialog)

public:
	ParametersDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~ParametersDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()

public:
	int func_index;
	CComboBox combo_control;
	BOOL OnInitDialog();
	void fill_values(CFunctionOptimizationMFCDoc* doc);
	BOOL method_index;
	unsigned int colors_num;
	int stop_criterion_index;
	double p;
	double delta;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	unsigned int steps_per_iter;
	afx_msg void OnBnClickedRadio3();
	int max_iter_num;
	unsigned int sc_int_parameter;
	double sc_double_parameter;
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	double x_lower;
	double x_upper;
	double y_lower;
	double y_upper;
};
