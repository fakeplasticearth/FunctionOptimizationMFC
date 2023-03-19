#pragma once
#define _USE_MATH_DEFINES
#include "StopCriterion.h"
#include <stdexcept>
#include <cmath>
#include <stdexcept>
#include "BoxArea.h"
#include "Function.h"
#include "OptInfo.h"
#include "OptResult.h"
#include <string>
#include <math.h>


class OptimizationMethod
{
protected:
    OptimizationMethod();
    OptimizationMethod(Function* func_, BoxArea* box_area_, StopCriterion* stop_criterion_);
    OptimizationMethod(const OptimizationMethod& other);
    OptimizationMethod(OptimizationMethod&& other) noexcept;

    void swap(OptimizationMethod& other) noexcept;
    std::vector <std::vector<double> > point_history;
    unsigned int n_iter = 0;
    unsigned int n_dim = 0;
    BoxArea* box_area = nullptr;
    Function* func = nullptr;
    StopCriterion* stop_criterion = nullptr;
    virtual void make_step() = 0;
public:
    virtual OptInfo* get_opt_info() const = 0;
    virtual OptResult optimize() = 0;
    virtual ~OptimizationMethod();
    unsigned int get_n_dim() const;
    unsigned int get_n_iter() const;
    std::vector<std::vector<double>>& get_point_history();
};

double spheric_func(std::vector<double> arg);
double rosenbrock_func(std::vector<double> arg);
double rastrigin_func(std::vector<double> arg);
double camel_func(std::vector<double> arg);

std::vector<double> spheric_func_grad(std::vector<double> arg);
std::vector<double> rosenbrock_func_grad(std::vector<double> arg);
std::vector<double> rastrigin_func_grad(std::vector<double> arg);
std::vector<double> camel_func_grad(std::vector<double> arg);

