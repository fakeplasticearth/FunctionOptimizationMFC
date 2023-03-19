
// FunctionOptimizationMFCView.cpp: реализация класса CFunctionOptimizationMFCView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "FunctionOptimizationMFC.h"
#endif

#include "FunctionOptimizationMFCDoc.h"
#include "FunctionOptimizationMFCView.h"

#include "ParametersDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFunctionOptimizationMFCView

IMPLEMENT_DYNCREATE(CFunctionOptimizationMFCView, CView)

BEGIN_MESSAGE_MAP(CFunctionOptimizationMFCView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFunctionOptimizationMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PARAMETERS, &CFunctionOptimizationMFCView::OnParameters)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_SIZING()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// Создание или уничтожение CFunctionOptimizationMFCView

CFunctionOptimizationMFCView::CFunctionOptimizationMFCView() noexcept
{
	// TODO: добавьте код создания
}

CFunctionOptimizationMFCView::~CFunctionOptimizationMFCView()
{
}

BOOL CFunctionOptimizationMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CFunctionOptimizationMFCView

void CFunctionOptimizationMFCView::OnDraw(CDC* pDC)
{
	CFunctionOptimizationMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!pDoc->get_first_call_flag()) {
		pDoc->set_first_call_flag(1);
		return;
	}

	CRect rc;
	GetClientRect(&rc);
	unsigned int rc_width = rc.Width(), rc_height = rc.Height();
	CBitmap bit;
	CDC dc2;
	dc2.CreateCompatibleDC(pDC);
	bit.CreateCompatibleBitmap(pDC, rc_width, rc_height);

	dc2.SelectObject(&bit);
	if (pDoc->get_sizing_flag()) {
		pDoc->set_draw_map_flag(1);
		if (pDoc->get_was_start_point()) {
			pDoc->set_last_start_flag(0);
			pDoc->set_draw_first_point_flag(1);
		}
	}

	if (pDoc->get_draw_trace_flag())
		pDoc->set_draw_map_flag(1);

	if (pDoc->get_draw_map_flag()) {

		Function* func = pDoc->get_function();
		unsigned int num_squares_x = rc_width / 2, num_squares_y = rc_height / 2; // Количество крупных пикселей
		dimensional_limits x_limits = pDoc->get_x_limits(), y_limits = pDoc->get_y_limits();
		double step_x = (x_limits.upper - x_limits.lower) / (num_squares_x - 1),
			step_y = (y_limits.upper - y_limits.lower) / (num_squares_y - 1);

		double min_value = DBL_MAX, max_value = -DBL_MAX, curr_value;
		std::vector<double> arg;
		arg.resize(2);

		// Получаем минимум и максимум по сетке. Это нужно только для определения цветов для пикселей.
		for (int i_x = 0; i_x < num_squares_x; ++i_x) {
			for (int i_y = 0; i_y < num_squares_y; ++i_y) {
				arg[0] = x_limits.lower + i_x * step_x;
				arg[1] = y_limits.lower + i_y * step_y;
				curr_value = (*func)(arg);
				if (curr_value > max_value)
					max_value = curr_value;
				if (curr_value < min_value)
					min_value = curr_value;
			}
		}
		pDoc->set_min_grid_value(min_value);
		pDoc->set_max_grid_value(max_value);

		unsigned int num_colors = pDoc->get_num_colors();
		double step_per_color = (max_value - min_value) / num_colors; // Дельта по значениям функции за один цвет
		double r_step = pDoc->get_r_step(), g_step = pDoc->get_g_step(), b_step = pDoc->get_b_step();
		unsigned int color_index;
		COLORREF min_color = pDoc->get_min_color();
		unsigned int min_r_color = GetRValue(min_color), 
			min_g_color = GetGValue(min_color), min_b_color = GetBValue(min_color);

		for (int i_x = 0; i_x < num_squares_x; ++i_x) {
			for (int i_y = 0; i_y < num_squares_y; ++i_y) {
				arg[0] = x_limits.lower + i_x * step_x;
				arg[1] = y_limits.lower + i_y * step_y;
				curr_value = (*func)(arg);
				color_index = int((curr_value - min_value) / step_per_color);
				dc2.FillSolidRect(2 * i_x, 2 * (num_squares_y - i_y), 2, 2, RGB(int(min_r_color + color_index * r_step), 
					int(min_g_color + color_index * g_step), int(min_b_color + color_index * b_step)));
			}
		}
		
	}
	if (pDoc->get_draw_first_point_flag()) {
		if (pDoc->get_trace_is_drawn_flag()) {
			pDoc->set_draw_trace_flag(0);
			pDoc->set_trace_is_drawn_flag(0);
			pDoc->set_last_start_flag(0);
			pDoc->set_draw_map_flag(1);
			Invalidate(0);
			return;
		}
		pDoc->set_was_start_point(1);

		unsigned int num_squares_x = rc_width / 2, num_squares_y = rc_height / 2; // Количество крупных пикселей
		dimensional_limits x_limits = pDoc->get_x_limits(), y_limits = pDoc->get_y_limits();
		double step_x = (x_limits.upper - x_limits.lower) / (num_squares_x - 1),
			step_y = (y_limits.upper - y_limits.lower) / (num_squares_y - 1); // Сколько по оси приходится на квадрат

		if (pDoc->get_last_start_flag() && (!pDoc->get_draw_trace_flag()) && (!pDoc->get_sizing_flag())) {
			int square_index_last_x = int((pDoc->get_last_start_x() - x_limits.lower) / step_x),
				square_index_last_y = int((pDoc->get_last_start_y() - y_limits.lower) / step_y);
			COLORREF last_start_color = pDoc->get_last_start_color();

			if (pDoc->get_draw_map_flag())
				dc2.FillSolidRect(2 * square_index_last_x, 2 * (num_squares_y - square_index_last_y), 2, 2, last_start_color);
			else
				pDC->FillSolidRect(2 * square_index_last_x, 2 * (num_squares_y - square_index_last_y), 2, 2, last_start_color);
		}
		pDoc->set_last_start_flag(1);
		int square_index_x = int((pDoc->get_start_x() - x_limits.lower) / step_x),
			square_index_y = int((pDoc->get_start_y() - y_limits.lower) / step_y);
		pDoc->set_last_start_x(pDoc->get_start_x());
		pDoc->set_last_start_y(pDoc->get_start_y());

		std::vector<double> arg;
		arg.resize(2);
		arg[0] = x_limits.lower + square_index_x * step_x;
		arg[1] = y_limits.lower + square_index_y * step_y;
		Function* func = pDoc->get_function();
		double curr_value = (*func)(arg);
		double min_value = pDoc->get_min_grid_value(), max_value = pDoc->get_max_grid_value();
		unsigned int num_colors = pDoc->get_num_colors();
		double step_per_color = (max_value - min_value) / num_colors; // Дельта по значениям функции за один цвет
		unsigned int color_index = int((curr_value - min_value) / step_per_color);
		COLORREF min_color = pDoc->get_min_color();
		double r_step = pDoc->get_r_step(), g_step = pDoc->get_g_step(), b_step = pDoc->get_b_step();

		pDoc->set_last_start_color(RGB(GetRValue(min_color) + color_index * r_step, GetGValue(min_color) + color_index * g_step,
			GetBValue(min_color) + color_index * b_step));
		
		if (!pDoc->get_draw_map_flag())
			pDC->FillSolidRect(2 * square_index_x, 2 * (num_squares_y - square_index_y), 2, 2, RGB(0, 0, 0));
		else
			dc2.FillSolidRect(2 * square_index_x, 2 * (num_squares_y - square_index_y), 2, 2, RGB(0, 0, 0));
		if (!pDoc->get_draw_map_flag())
			timer = SetTimer(1, 2000, 0);
		else {
			if (pDoc->get_sizing_flag())
				pDoc->set_draw_trace_flag(1);
			else
				timer = SetTimer(1, 2000, 0);
		}
	}
	if (pDoc->get_draw_trace_flag()) {
		pDoc->set_trace_is_drawn_flag(1);
		
		pDoc->set_last_start_flag(0);
		pDoc->set_draw_first_point_flag(0);
		KillTimer(timer);

		if (pDoc->get_new_trace_flag()) {
			pDoc->update_opt_method();
			OptResult tmp_result = pDoc->get_opt_method()->optimize();
			pDoc->set_opt_result(tmp_result);
		}
		OptResult tmp_res = pDoc->get_opt_result();
		std::vector<double> min_point = tmp_res.get_min_point();
		dimensional_limits x_limits = pDoc->get_x_limits(), y_limits = pDoc->get_y_limits();
		unsigned int num_squares_x = rc_width / 2, num_squares_y = rc_height / 2; // Количество крупных пикселей
		double step_x = (x_limits.upper - x_limits.lower) / (num_squares_x - 1),
			step_y = (y_limits.upper - y_limits.lower) / (num_squares_y - 1);
		int square_index_x = int((min_point[0] - x_limits.lower) / step_x),
			square_index_y = int((min_point[1] - y_limits.lower) / step_y);
		int frame_x = max(2 * square_index_x - 2, 0), 
			frame_y = max(2 * (num_squares_y - square_index_y) - 2, 0);
		int frame_size = min(6, min(rc_width - 1 - frame_x, rc_height - 1 - frame_y));
		dc2.FillSolidRect(frame_x, frame_y, frame_size, frame_size, RGB(255, 255, 255));
		dc2.FillSolidRect(2 * square_index_x, 2 * (num_squares_y - square_index_y), 2, 2, RGB(245, 20, 35));

		square_index_x = int((pDoc->get_start_x() - x_limits.lower) / step_x);
		square_index_y = int((pDoc->get_start_y() - y_limits.lower) / step_y);
		frame_x = max(2 * square_index_x - 2, 0);
		frame_y = max(2 * (num_squares_y - square_index_y) - 2, 0);
		frame_size = min(6, min(rc_width - 1 - frame_x, rc_height - 1 - frame_y));
		dc2.FillSolidRect(frame_x, frame_y, frame_size, frame_size, RGB(20, 20, 20));

		int quarter = 0;
		if (min_point[0] < (x_limits.upper + x_limits.lower) / 2) {
			if (min_point[1] < (y_limits.upper + y_limits.lower) / 2)
				quarter = 3;
			else
				quarter = 2;
		}
		else {
			if (min_point[1] < (y_limits.upper + y_limits.lower) / 2)
				quarter = 4;
			else
				quarter = 1;
		}

		int x_result, y_result;
		int result_width = 200, result_height = 105;
		int v_shift = 0, h_shift = 0;
		switch (quarter) {
		case 1:
			x_result = rc_width - 1 - result_width - h_shift;
			y_result = v_shift;
			break;
		case 2:
			x_result = h_shift;
			y_result = v_shift;
			break;
		case 3:
			x_result = h_shift;
			y_result = rc_height - 1 - result_height - v_shift;
			break;
		case 4:
			x_result = rc_width - 1 - result_width - h_shift;
			y_result = rc_height - 1 - result_height - v_shift;
		}
		dc2.FillSolidRect(x_result, y_result, result_width, result_height, RGB(0, 0, 0));
		dc2.FillSolidRect(x_result + 2, y_result + 2, result_width - 4, result_height - 4, RGB(255, 255, 255));
		dc2.TextOut(x_result + 10, y_result + 10, L"Min point coordinates:");
		CString tmp;
		tmp.Format(L"%.5g", min_point[0]);
		dc2.TextOut(x_result + 10, y_result + 30, L"x: " + tmp);
		tmp.Format(L"%.5g", min_point[1]);
		dc2.TextOut(x_result + 10, y_result + 50, L"y: " + tmp);
		tmp.Format(L"%.5g", tmp_res.get_min_value());
		dc2.TextOutW(x_result + 10, y_result + 70, L"f(x,y)=" + tmp);
		
		std::vector<std::vector<double>> point_history = pDoc->get_opt_method()->get_point_history();
		int point_num = point_history.size();
		if (point_num > 1) {
			CPen penRed;
			penRed.CreatePen(PS_SOLID, 2, RGB(235, 25, 100));
			dc2.SelectObject(penRed);
			int lstart_x, lstart_y, lend_x, lend_y;
			for (int i = 0; i < point_num - 2; ++i) {
				lstart_x = int((point_history[i][0] - x_limits.lower) / step_x),
					lstart_y = int((point_history[i][1] - y_limits.lower) / step_y),
					lend_x = int((point_history[i + 1][0] - x_limits.lower) / step_x),
					lend_y = int((point_history[i + 1][1] - y_limits.lower) / step_y);
				dc2.MoveTo(2 * lstart_x, 2 * (num_squares_y - lstart_y));
				dc2.LineTo(2 * lend_x, 2 * (num_squares_y - lend_y));
			}
		}

		pDoc->set_new_trace_flag(0);
	}
	if (pDoc->get_draw_map_flag())
		pDC->BitBlt(0, 0, rc_width, rc_height, &dc2, 0, 0, SRCCOPY);
	pDoc->set_sizing_flag(0);
}


// Печать CFunctionOptimizationMFCView


void CFunctionOptimizationMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFunctionOptimizationMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CFunctionOptimizationMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CFunctionOptimizationMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CFunctionOptimizationMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFunctionOptimizationMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CFunctionOptimizationMFCView

#ifdef _DEBUG
void CFunctionOptimizationMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CFunctionOptimizationMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFunctionOptimizationMFCDoc* CFunctionOptimizationMFCView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFunctionOptimizationMFCDoc)));
	return (CFunctionOptimizationMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CFunctionOptimizationMFCView


void CFunctionOptimizationMFCView::OnParameters()
{
	ParametersDialog d;
	CFunctionOptimizationMFCDoc* doc = GetDocument();
	d.fill_values(doc);

	while (d.DoModal() == IDOK) {
		bool pass_flag = 1;
		CString error_message = L"";

		if (d.p < 1e-4 && d.method_index == 0) {
			pass_flag = 0;
			error_message += L"Probability must be greater than 1e-4.\n";
		}
		if (d.x_lower - d.x_upper > 1e-9 || d.y_lower - d.y_upper > 1e-9) {
			pass_flag = 0;
			error_message += L"Upper limit must be greater than lower limit.\n";
		}
		if (d.delta < 1e-9 && d.method_index == 0) {
			pass_flag = 0;
			error_message += L"Delta must be greater than 1e-9.\n";
		}

		if (pass_flag) {
			doc->clear_function();
			doc->set_function_index(d.func_index);
			doc->set_method_index(d.method_index);
			doc->set_colors_num(d.colors_num);
			doc->set_new_trace_flag(1);

			doc->set_stop_criterion_index(d.stop_criterion_index);
			doc->set_p(d.p);
			doc->set_delta(d.delta);
			doc->set_steps_per_iter(d.steps_per_iter);
			doc->set_max_iter_num(d.max_iter_num);
			doc->set_sc_int_parameter(d.sc_int_parameter);
			doc->set_sc_double_parameter(d.sc_double_parameter);
			doc->set_x_limits(dimensional_limits(d.x_lower, d.x_upper));
			doc->set_y_limits(dimensional_limits(d.y_lower, d.y_upper));
			doc->update_box_area();

			Function* tmp = nullptr;
			MDFunction* tmp_grad = nullptr;
			switch (d.func_index) {
			case 0:
				tmp = new Function(spheric_func, 2);
				tmp_grad = new MDFunction(spheric_func_grad, 2);
				break;
			case 1:
				tmp = new Function(rosenbrock_func, 2);
				tmp_grad = new MDFunction(rosenbrock_func_grad, 2);
				break;
			case 2:
				tmp = new Function(rastrigin_func, 2);
				tmp_grad = new MDFunction(rastrigin_func_grad, 2);
				break;
			case 3:
				tmp = new Function(camel_func, 2);
				tmp_grad = new MDFunction(camel_func_grad, 2);
				break;
			}
			doc->set_function(tmp);
			doc->set_grad(tmp_grad);

			doc->clear_stop_criterion();
			StopCriterion* tmp2 = nullptr;
			switch (d.method_index) {
			case 0:
				switch (d.stop_criterion_index) {
				case 0:
					tmp2 = new IterOnlySSC(d.max_iter_num);
					break;
				case 1:
					tmp2 = new IterAfterImpSSC(d.max_iter_num, d.sc_int_parameter);
					break;
				case 2:
					tmp2 = new NormDiffSSC(d.max_iter_num, d.sc_double_parameter);
					break;
				}
				break;
			case 1:
				switch (d.stop_criterion_index) {
				case 0:
					tmp2 = new MinGradNormGDSC(d.max_iter_num, d.sc_double_parameter);
					break;
				case 1:
					tmp2 = new MinStepNormGDSC(d.max_iter_num, d.sc_double_parameter);
					break;
				case 2:
					tmp2 = new MinRelImpNormGDSC(d.max_iter_num, d.sc_double_parameter);
					break;
				}
				break;
			}
			doc->set_stop_criterion(tmp2);

			doc->set_was_start_point(0);
			doc->set_draw_trace_flag(0);
			doc->set_draw_first_point_flag(0);

			doc->UpdateAllViews(0);
			break;
		}
		else
			AfxMessageBox(error_message);
		
	}
}


void CFunctionOptimizationMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CFunctionOptimizationMFCDoc* doc = GetDocument();

	CRect rc;
	GetClientRect(&rc);
	unsigned int rc_width = rc.Width(), rc_height = rc.Height();

	unsigned int num_squares_x = rc_width / 2, num_squares_y = rc_height / 2; // Количество крупных пикселей
	dimensional_limits x_limits = doc->get_x_limits(), y_limits = doc->get_y_limits();
	double step_x = (x_limits.upper - x_limits.lower) / (num_squares_x - 1),
		step_y = (y_limits.upper - y_limits.lower) / (num_squares_y - 1);
	doc->set_start_x(x_limits.lower + int(point.x / 2) * step_x);
	doc->set_start_y(y_limits.upper - int(point.y / 2) * step_y);
	doc->set_draw_first_point_flag(1);
	CView::OnLButtonDown(nFlags, point);
	doc->set_draw_map_flag(0);
	Invalidate(0);
}


void CFunctionOptimizationMFCView::OnTimer(UINT_PTR nIDEvent)
{
	CFunctionOptimizationMFCDoc* doc = GetDocument();
	doc->set_draw_trace_flag(1);
	doc->set_draw_first_point_flag(1);
	doc->set_last_start_flag(0);
	doc->set_draw_map_flag(0);
	doc->set_new_trace_flag(1);
	CView::OnTimer(nIDEvent);
	Invalidate(0);
}


void CFunctionOptimizationMFCView::OnSize(UINT nType, int cx, int cy)
{
	CFunctionOptimizationMFCDoc* doc = GetDocument();
	doc->set_sizing_flag(1);
	CView::OnSize(nType, cx, cy);

	// TODO: добавьте свой код обработчика сообщений
}
