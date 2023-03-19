
// FunctionOptimizationMFCDoc.cpp: реализация класса CFunctionOptimizationMFCDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "FunctionOptimizationMFC.h"
#endif

#include "FunctionOptimizationMFCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFunctionOptimizationMFCDoc

IMPLEMENT_DYNCREATE(CFunctionOptimizationMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CFunctionOptimizationMFCDoc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение CFunctionOptimizationMFCDoc

CFunctionOptimizationMFCDoc::CFunctionOptimizationMFCDoc() noexcept
{
	function_index = 0;
	func = new Function(spheric_func, 2);
	x_limits = dimensional_limits(-5., 5.);
	y_limits = dimensional_limits(-5., 5.);
	update_box_area();
	draw_map = 1;
	draw_trace = 0;
	draw_first_point = 0;
	min_color = RGB(15, 245, 105);
	max_color = RGB(45, 35, 205);
	num_colors = 50;
	method_index = 0;
	first_call_flag = 0;
	last_start_flag = 0;
	sizing_flag = 1;
	trace_is_drawn = 0;
	was_start_point = 0;
	new_trace = 1;

	stop_criterion_index = 0;
	p = 0.5;
	delta = 1.;
	steps_per_iter = 100;
	max_iter_num = 5000;
	sc_int_parameter = 1000;
	sc_double_parameter = 1e-6;
	stop_criterion = new IterOnlySSC(max_iter_num);
}

CFunctionOptimizationMFCDoc::~CFunctionOptimizationMFCDoc()
{
}

BOOL CFunctionOptimizationMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}

unsigned int CFunctionOptimizationMFCDoc::get_function_index() const {
	return function_index;
}

dimensional_limits CFunctionOptimizationMFCDoc::get_x_limits() const {
	return x_limits;
}

dimensional_limits CFunctionOptimizationMFCDoc::get_y_limits() const {
	return y_limits;
}

void CFunctionOptimizationMFCDoc::set_function_index(unsigned int function_index_) {
	function_index = function_index_;
}

void CFunctionOptimizationMFCDoc::set_x_limits(const dimensional_limits& x_limits_) {
	x_limits = x_limits_;
}

void CFunctionOptimizationMFCDoc::set_y_limits(const dimensional_limits& y_limits_) {
	y_limits = y_limits_;
}

bool CFunctionOptimizationMFCDoc::get_draw_map_flag() const {
	return draw_map;
}

void CFunctionOptimizationMFCDoc::set_draw_map_flag(bool flag) {
	draw_map = flag;
}

bool CFunctionOptimizationMFCDoc::get_draw_trace_flag() const {
	return draw_trace;
}

void CFunctionOptimizationMFCDoc::set_draw_trace_flag(bool flag) {
	draw_trace = flag;
}

Function* CFunctionOptimizationMFCDoc::get_function() const {
	return func;
}

void CFunctionOptimizationMFCDoc::clear_function() {
	if (func)
		delete func;
	if (grad)
		delete grad;
}

void CFunctionOptimizationMFCDoc::set_function(Function* func_) {
	func = func_;
}

unsigned int CFunctionOptimizationMFCDoc::get_num_colors() const {
	return num_colors;
}

COLORREF CFunctionOptimizationMFCDoc::get_min_color() const {
	return min_color;
}

COLORREF CFunctionOptimizationMFCDoc::get_max_color() const {
	return max_color;
}

double CFunctionOptimizationMFCDoc::get_r_step() const {
	return ((double)(GetRValue(max_color) - GetRValue(min_color)) / num_colors);
}

double CFunctionOptimizationMFCDoc::get_g_step() const {
	return ((double)(GetGValue(max_color) - GetGValue(min_color)) / num_colors);
}

double CFunctionOptimizationMFCDoc::get_b_step() const {
	return ((double)(GetBValue(max_color) - GetBValue(min_color)) / num_colors);
}

bool CFunctionOptimizationMFCDoc::get_method_index() const {
	return method_index;
}

void CFunctionOptimizationMFCDoc::set_colors_num(unsigned int num_colors_) {
	num_colors = num_colors_;
}

void CFunctionOptimizationMFCDoc::set_method_index(bool method_index_) {
	method_index = method_index_;
}

double CFunctionOptimizationMFCDoc::get_start_x() const {
	return start_x;
}

void CFunctionOptimizationMFCDoc::set_start_x(double start_x_) {
	start_x = start_x_;
}

double CFunctionOptimizationMFCDoc::get_start_y() const {
	return start_y;
}

void CFunctionOptimizationMFCDoc::set_start_y(double start_y_) {
	start_y = start_y_;
}

bool CFunctionOptimizationMFCDoc::get_draw_first_point_flag() const {
	return draw_first_point;
}

void CFunctionOptimizationMFCDoc::set_draw_first_point_flag(bool flag) {
	draw_first_point = flag;
}

double CFunctionOptimizationMFCDoc::get_last_start_x() const {
	return last_start_x;
}

void CFunctionOptimizationMFCDoc::set_last_start_x(double last_start_x_) {
	last_start_x = last_start_x_;
}

double CFunctionOptimizationMFCDoc::get_last_start_y() const {
	return last_start_y;
}

void CFunctionOptimizationMFCDoc::set_last_start_y(double last_start_y_) {
	last_start_y = last_start_y_;
}

COLORREF CFunctionOptimizationMFCDoc::get_last_start_color() const {
	return last_start_color;
}

void CFunctionOptimizationMFCDoc::set_last_start_color(COLORREF last_start_color_) {
	last_start_color = last_start_color_;
}

bool CFunctionOptimizationMFCDoc::get_last_start_flag() const {
	return last_start_flag;
}

void CFunctionOptimizationMFCDoc::set_last_start_flag(bool flag) {
	last_start_flag = flag;
}

double CFunctionOptimizationMFCDoc::get_min_grid_value() const {
	return min_grid_value;
}

void CFunctionOptimizationMFCDoc::set_min_grid_value(double min_grid_value_) {
	min_grid_value = min_grid_value_;
}

double CFunctionOptimizationMFCDoc::get_max_grid_value() const {
	return max_grid_value;
}

void CFunctionOptimizationMFCDoc::set_max_grid_value(double max_grid_value_) {
	max_grid_value = max_grid_value_;
}

bool CFunctionOptimizationMFCDoc::get_first_call_flag() const {
	return first_call_flag;
}

void CFunctionOptimizationMFCDoc::set_first_call_flag(bool flag) {
	first_call_flag = flag;
}

bool CFunctionOptimizationMFCDoc::get_sizing_flag() const
{
	return sizing_flag;
}

void CFunctionOptimizationMFCDoc::set_sizing_flag(bool flag)
{
	sizing_flag = flag;
}

bool CFunctionOptimizationMFCDoc::get_trace_is_drawn_flag() const
{
	return trace_is_drawn;
}

void CFunctionOptimizationMFCDoc::set_trace_is_drawn_flag(bool flag)
{
	trace_is_drawn = flag;
}

bool CFunctionOptimizationMFCDoc::get_was_start_point() const
{
	return was_start_point;
}

void CFunctionOptimizationMFCDoc::set_was_start_point(bool flag)
{
	was_start_point = flag;
}

bool CFunctionOptimizationMFCDoc::get_new_trace_flag() const
{
	return new_trace;
}

void CFunctionOptimizationMFCDoc::set_new_trace_flag(bool flag)
{
	new_trace = flag;
}

unsigned int CFunctionOptimizationMFCDoc::get_stop_criterion_index() const
{
	return stop_criterion_index;
}

void CFunctionOptimizationMFCDoc::set_stop_criterion_index(unsigned int index)
{
	stop_criterion_index = index;
}

double CFunctionOptimizationMFCDoc::get_p() const
{
	return p;
}

void CFunctionOptimizationMFCDoc::set_p(double p_)
{
	p = p_;
}

double CFunctionOptimizationMFCDoc::get_delta() const
{
	return delta;
}

void CFunctionOptimizationMFCDoc::set_delta(double delta_)
{
	delta = delta_;
}

unsigned int CFunctionOptimizationMFCDoc::get_steps_per_iter() const
{
	return steps_per_iter;
}

void CFunctionOptimizationMFCDoc::set_steps_per_iter(unsigned int steps)
{
	steps_per_iter = steps;
}

unsigned int CFunctionOptimizationMFCDoc::get_max_iter_num() const
{
	return max_iter_num;
}

void CFunctionOptimizationMFCDoc::set_max_iter_num(unsigned int iter)
{
	max_iter_num = iter;
}

unsigned int CFunctionOptimizationMFCDoc::get_sc_int_parameter() const
{
	return sc_int_parameter;
}

void CFunctionOptimizationMFCDoc::set_sc_int_parameter(unsigned int parameter)
{
	sc_int_parameter = parameter;
}

double CFunctionOptimizationMFCDoc::get_sc_double_parameter() const
{
	return sc_double_parameter;
}

void CFunctionOptimizationMFCDoc::set_sc_double_parameter(double parameter)
{
	sc_double_parameter = parameter;
}

void CFunctionOptimizationMFCDoc::clear_stop_criterion()
{
	if (stop_criterion)
		delete stop_criterion;
}

StopCriterion* CFunctionOptimizationMFCDoc::get_stop_criterion() const
{
	return stop_criterion;
}

void CFunctionOptimizationMFCDoc::set_stop_criterion(StopCriterion* stop_criterion_)
{
	stop_criterion = stop_criterion_;
}

OptimizationMethod* CFunctionOptimizationMFCDoc::get_opt_method() const
{
	return opt_method;
}

void CFunctionOptimizationMFCDoc::set_opt_method(OptimizationMethod* opt_method_)
{
	opt_method = opt_method_;
}

void CFunctionOptimizationMFCDoc::clear_opt_method()
{
	if (opt_method)
		delete opt_method;
}

BoxArea* CFunctionOptimizationMFCDoc::get_box_area() const
{
	return box_area;
}

void CFunctionOptimizationMFCDoc::set_box_area(BoxArea* box_area_)
{
	box_area = box_area_;
}

void CFunctionOptimizationMFCDoc::clear_box_area()
{
	if (box_area)
		delete box_area;
}

void CFunctionOptimizationMFCDoc::update_box_area()
{
	std::vector<dimensional_limits> tmp_vector = {x_limits, y_limits};
	if (box_area)
		delete box_area;
	box_area = new BoxArea(2, tmp_vector);
}

void CFunctionOptimizationMFCDoc::update_opt_method()
{
	if (opt_method)
		delete opt_method;
	std::vector<double> tmp_first_point = { start_x, start_y };
	switch (method_index) {
	case 0:
		opt_method = new StohasticOptimization(func, box_area, stop_criterion, tmp_first_point, delta, p);
		break;
	case 1:
		opt_method = new GradientDescent(func, grad, box_area, stop_criterion, tmp_first_point, steps_per_iter, "l2");
		break;
	}
}

OptResult CFunctionOptimizationMFCDoc::get_opt_result() const
{
	return opt_result;
}

void CFunctionOptimizationMFCDoc::set_opt_result(OptResult opt_result_)
{
	opt_result = opt_result_;
}

void CFunctionOptimizationMFCDoc::set_grad(MDFunction* grad_)
{
	grad = grad_;
}

// Сериализация CFunctionOptimizationMFCDoc

void CFunctionOptimizationMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CFunctionOptimizationMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CFunctionOptimizationMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CFunctionOptimizationMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CFunctionOptimizationMFCDoc

#ifdef _DEBUG
void CFunctionOptimizationMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFunctionOptimizationMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CFunctionOptimizationMFCDoc
