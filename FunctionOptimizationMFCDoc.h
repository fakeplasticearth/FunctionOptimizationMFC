
// FunctionOptimizationMFCDoc.h: интерфейс класса CFunctionOptimizationMFCDoc 
//

#include "StohasticOptimization.h"
#include "GradientDescent.h"


#pragma once


class CFunctionOptimizationMFCDoc : public CDocument
{
protected: // создать только из сериализации
	CFunctionOptimizationMFCDoc() noexcept;
	DECLARE_DYNCREATE(CFunctionOptimizationMFCDoc)

// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CFunctionOptimizationMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	unsigned int get_function_index() const;
	dimensional_limits get_x_limits() const;
	dimensional_limits get_y_limits() const;
	void set_function_index(unsigned int function_index_);
	void set_x_limits(const dimensional_limits& x_limits_);
	void set_y_limits(const dimensional_limits& y_limits_);
	bool get_draw_map_flag() const;
	void set_draw_map_flag(bool flag);
	bool get_draw_trace_flag() const;
	void set_draw_trace_flag(bool flag);
	Function* get_function() const;
	void clear_function();
	void set_function(Function* func_);
	unsigned int get_num_colors() const;
	COLORREF get_min_color() const;
	COLORREF get_max_color() const;
	double get_r_step() const;
	double get_g_step() const;
	double get_b_step() const;
	bool get_method_index() const;
	void set_colors_num(unsigned int num_colors_);
	void set_method_index(bool method_index_);
	double get_start_x() const;
	void set_start_x(double start_x_);
	double get_start_y() const;
	void set_start_y(double start_y_);
	bool get_draw_first_point_flag() const;
	void set_draw_first_point_flag(bool flag);
	double get_last_start_x() const;
	void set_last_start_x(double last_start_x_);
	double get_last_start_y() const;
	void set_last_start_y(double last_start_y_);
	COLORREF get_last_start_color() const;
	void set_last_start_color(COLORREF last_start_color_);
	bool get_last_start_flag() const;
	void set_last_start_flag(bool flag);
	double get_min_grid_value() const;
	void set_min_grid_value(double min_grid_value_);
	double get_max_grid_value() const;
	void set_max_grid_value(double max_grid_value_);
	bool get_first_call_flag() const;
	void set_first_call_flag(bool flag);
	bool get_sizing_flag() const;
	void set_sizing_flag(bool flag);
	bool get_trace_is_drawn_flag() const;
	void set_trace_is_drawn_flag(bool flag);
	bool get_was_start_point() const;
	void set_was_start_point(bool flag);
	bool get_new_trace_flag() const;
	void set_new_trace_flag(bool flag);

	unsigned int get_stop_criterion_index() const;
	void set_stop_criterion_index(unsigned int index);
	double get_p() const;
	void set_p(double p_);
	double get_delta() const;
	void set_delta(double delta_);
	unsigned int get_steps_per_iter() const;
	void set_steps_per_iter(unsigned int steps);
	unsigned int get_max_iter_num() const;
	void set_max_iter_num(unsigned int iter);
	unsigned int get_sc_int_parameter() const;
	void set_sc_int_parameter(unsigned int parameter);
	double get_sc_double_parameter() const;
	void set_sc_double_parameter(double parameter);
	void clear_stop_criterion();
	StopCriterion* get_stop_criterion() const;
	void set_stop_criterion(StopCriterion* stop_criterion_);
	OptimizationMethod* get_opt_method() const;
	void set_opt_method(OptimizationMethod* opt_method_);
	void clear_opt_method();
	BoxArea* get_box_area() const;
	void set_box_area(BoxArea* box_area_);
	void clear_box_area();
	void update_box_area();
	void update_opt_method();
	OptResult get_opt_result() const;
	void set_opt_result(OptResult opt_result_);
	void set_grad(MDFunction* grad_);

protected:
	unsigned int function_index;
	dimensional_limits x_limits, y_limits;
	bool draw_map;
	bool draw_trace;
	bool draw_first_point;
	OptimizationMethod* opt_method = nullptr;
	Function* func = nullptr;
	MDFunction* grad = nullptr;
	StopCriterion* stop_criterion = nullptr;
	BoxArea* box_area = nullptr;
	OptResult opt_result;
	unsigned int num_colors;
	COLORREF min_color, max_color;
	double r_step, g_step, b_step;
	bool method_index;
	double start_x, start_y;
	double last_start_x, last_start_y;
	COLORREF last_start_color;
	bool last_start_flag;
	double min_grid_value, max_grid_value;
	bool first_call_flag;
	bool sizing_flag;
	bool trace_is_drawn;
	bool was_start_point;
	bool new_trace;

	unsigned int stop_criterion_index;
	double p;
	double delta;
	unsigned int steps_per_iter;
	unsigned int max_iter_num;
	unsigned int sc_int_parameter;
	double sc_double_parameter;

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
