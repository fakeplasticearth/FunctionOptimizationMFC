// ParametersDialog.cpp: файл реализации
//

#include "pch.h"
#include "FunctionOptimizationMFC.h"
#include "ParametersDialog.h"
#include "afxdialogex.h"


// Диалоговое окно ParametersDialog

IMPLEMENT_DYNAMIC(ParametersDialog, CDialog)

ParametersDialog::ParametersDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, func_index(0)
	, method_index(FALSE)
	, colors_num(0)
	, stop_criterion_index(0)
	, p(0)
	, delta(0)
	, steps_per_iter(0)
	, max_iter_num(0)
	, sc_int_parameter(0)
	, sc_double_parameter(0)
	, x_lower(0)
	, x_upper(0)
	, y_lower(0)
	, y_upper(0)
{

}

ParametersDialog::~ParametersDialog()
{
}

void ParametersDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, func_index);
	DDX_Control(pDX, IDC_COMBO1, combo_control);
	DDX_Radio(pDX, IDC_RADIO1, method_index);
	DDX_Text(pDX, IDC_EDIT1, colors_num);
	DDV_MinMaxUInt(pDX, colors_num, 1, 200);
	DDX_Radio(pDX, IDC_RADIO3, stop_criterion_index);
	DDX_Text(pDX, IDC_EDIT_P, p);
	DDV_MinMaxDouble(pDX, p, 0., 1.);
	DDX_Text(pDX, IDC_EDIT_DELTA, delta);
	DDV_MinMaxDouble(pDX, delta, 0., DBL_MAX);
	DDX_Text(pDX, IDC_EDIT_STEPS, steps_per_iter);
	DDV_MinMaxUInt(pDX, steps_per_iter, 1, 5000);
	DDX_Text(pDX, IDC_EDIT5, max_iter_num);
	DDV_MinMaxInt(pDX, max_iter_num, 1, 1000000);
	DDX_Text(pDX, IDC_EDIT_MAX_IT, sc_int_parameter);
	DDV_MinMaxUInt(pDX, sc_int_parameter, 1, 1000000);
	DDX_Text(pDX, IDC_EDIT_SCD, sc_double_parameter);
	DDV_MinMaxDouble(pDX, sc_double_parameter, 0., DBL_MAX);
	DDX_Text(pDX, IDC_EDIT3, x_lower);
	DDX_Text(pDX, IDC_EDIT4, x_upper);
	DDX_Text(pDX, IDC_EDIT6, y_lower);
	DDX_Text(pDX, IDC_EDIT7, y_upper);
}

BOOL ParametersDialog::OnInitDialog() {
	CDialog::OnInitDialog();
	combo_control.AddString(L"Spheric");
	combo_control.AddString(L"Rosenbrock");
	combo_control.AddString(L"Rastrigin");
	combo_control.AddString(L"Camel function");
	combo_control.SetCurSel(func_index);
	switch (method_index) {
	case 0:
		GetDlgItem(IDC_STATIC_DELTA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DELTA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_P)->SetWindowTextW(L"Probability");
		GetDlgItem(IDC_EDIT_STEPS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_P)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO3)->SetWindowTextW(L"Max iter num");
		GetDlgItem(IDC_RADIO4)->SetWindowTextW(L"Max iter num after improvement");
		GetDlgItem(IDC_RADIO5)->SetWindowTextW(L"Min norm of last improvement");

		switch (stop_criterion_index) {
		case 0:
			GetDlgItem(IDC_STATIC_SC2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_SCD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MAX_IT)->ShowWindow(SW_HIDE);
			break;
		case 1:
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Max iter num after improvement");
			GetDlgItem(IDC_EDIT_SCD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MAX_IT)->ShowWindow(SW_SHOW);
			break;
		case 2:
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Min norm of last improvement");
			break;
		}
		break;
	case 1:
		GetDlgItem(IDC_STATIC_DELTA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DELTA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_P)->SetWindowTextW(L"Steps per iteration");
		GetDlgItem(IDC_EDIT_STEPS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_P)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO3)->SetWindowTextW(L"Min grad norm");
		GetDlgItem(IDC_RADIO4)->SetWindowTextW(L"Min last improvement norm");
		GetDlgItem(IDC_RADIO5)->SetWindowTextW(L"Min relative improvement norm");

		GetDlgItem(IDC_EDIT_SCD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MAX_IT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SC2)->ShowWindow(SW_SHOW);
		switch (stop_criterion_index) {
		case 0:
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Min grad norm");
			break;
		case 1:
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Min last improvement norm");
			break;
		case 2:
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Min relative improvement norm");
			break;
		}
		break;
	}
	return TRUE; // return TRUE unless you set the focus to a control
}

void ParametersDialog::fill_values(CFunctionOptimizationMFCDoc* doc) {
	func_index = doc->get_function_index();
	method_index = doc->get_method_index();
	colors_num = doc->get_num_colors();
	stop_criterion_index = doc->get_stop_criterion_index();
	p = doc->get_p();
	delta = doc->get_delta();
	steps_per_iter = doc->get_steps_per_iter();
	max_iter_num = doc->get_max_iter_num();
	sc_int_parameter = doc->get_sc_int_parameter();
	sc_double_parameter = doc->get_sc_double_parameter();
	dimensional_limits tmp = doc->get_x_limits();
	x_lower = tmp.lower;
	x_upper = tmp.upper;
	tmp = doc->get_y_limits();
	y_lower = tmp.lower;
	y_upper = tmp.upper;
}


BEGIN_MESSAGE_MAP(ParametersDialog, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &ParametersDialog::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &ParametersDialog::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &ParametersDialog::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &ParametersDialog::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &ParametersDialog::OnBnClickedRadio5)
END_MESSAGE_MAP()


// Обработчики сообщений ParametersDialog


void ParametersDialog::OnBnClickedRadio1()
{
	if (method_index == 1) {
		GetDlgItem(IDC_STATIC_DELTA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DELTA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_P)->SetWindowTextW(L"Probability");
		GetDlgItem(IDC_EDIT_STEPS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_P)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO3)->SetWindowTextW(L"Max iter num");
		GetDlgItem(IDC_RADIO4)->SetWindowTextW(L"Max iter num after improvement");
		GetDlgItem(IDC_RADIO5)->SetWindowTextW(L"Min norm of last improvement");

		switch (stop_criterion_index) {
		case 0:
			GetDlgItem(IDC_STATIC_SC2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_SCD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MAX_IT)->ShowWindow(SW_HIDE);
			break;
		case 1:
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Max iter num after improvement");
			GetDlgItem(IDC_EDIT_SCD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MAX_IT)->ShowWindow(SW_SHOW);
			break;
		case 2:
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Min norm of last improvement");
			break;
		}
	}
	method_index = 0;
}


void ParametersDialog::OnBnClickedRadio2()
{
	if (method_index == 0) {
		GetDlgItem(IDC_STATIC_DELTA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DELTA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_P)->SetWindowTextW(L"Steps per iteration");
		GetDlgItem(IDC_EDIT_STEPS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_P)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO3)->SetWindowTextW(L"Min grad norm");
		GetDlgItem(IDC_RADIO4)->SetWindowTextW(L"Min last improvement norm");
		GetDlgItem(IDC_RADIO5)->SetWindowTextW(L"Min relative improvement norm");

		GetDlgItem(IDC_EDIT_SCD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MAX_IT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SC2)->ShowWindow(SW_SHOW);
		switch (stop_criterion_index) {
		case 0:
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Min grad norm");
			break;
		case 1:
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Min last improvement norm");
			break;
		case 2:
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Min relative improvement norm");
			break;
		}
	}
	method_index = 1;
}


void ParametersDialog::OnBnClickedRadio3()
{
	if (stop_criterion_index != 0) {
		switch (method_index) {
		case 0:
			GetDlgItem(IDC_EDIT_MAX_IT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SC2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_SCD)->ShowWindow(SW_HIDE);
			break;
		case 1:
			GetDlgItem(IDC_STATIC_SC2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Min grad norm");
			GetDlgItem(IDC_EDIT_MAX_IT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_SCD)->ShowWindow(SW_SHOW);
		}
	}
	stop_criterion_index = 0;
}


void ParametersDialog::OnBnClickedRadio4()
{
	if (stop_criterion_index != 1) {
		switch (method_index) {
		case 0:
			GetDlgItem(IDC_EDIT_MAX_IT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SC2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_SCD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Max iter num after improvement");
			break;
		case 1:
			GetDlgItem(IDC_STATIC_SC2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Min last improvement norm");
			GetDlgItem(IDC_EDIT_MAX_IT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_SCD)->ShowWindow(SW_SHOW);
		}
	}
	stop_criterion_index = 1;
}


void ParametersDialog::OnBnClickedRadio5()
{
	if (stop_criterion_index != 2) {
		switch (method_index) {
		case 0:
			GetDlgItem(IDC_EDIT_MAX_IT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SC2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_SCD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Min norm of last improvement");
			break;
		case 1:
			GetDlgItem(IDC_STATIC_SC2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SC2)->SetWindowTextW(L"Min relative improvement norm");
			GetDlgItem(IDC_EDIT_MAX_IT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_SCD)->ShowWindow(SW_SHOW);
		}
	}
	stop_criterion_index = 2;
}

