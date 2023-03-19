#include "pch.h"
#include "OptimizationMethod.h"

OptimizationMethod::OptimizationMethod() {

}

OptimizationMethod::OptimizationMethod(Function* func_, BoxArea* box_area_, StopCriterion* stop_criterion_) : func(func_),
box_area(box_area_), stop_criterion(stop_criterion_) {
    n_dim = box_area->get_n_dim();
}

OptimizationMethod::OptimizationMethod(const OptimizationMethod& other) : func(other.func), box_area(other.box_area),
stop_criterion(other.stop_criterion) {

}

OptimizationMethod::OptimizationMethod(OptimizationMethod&& other) noexcept : func(std::move(other.func)), box_area(std::move(other.box_area)),
stop_criterion(std::move(other.stop_criterion)), n_dim(other.n_dim), n_iter(other.n_iter)
{
    other.n_dim = 0;
    other.n_iter = 0;
}

void OptimizationMethod::swap(OptimizationMethod& other) noexcept {
    std::swap(other.func, func);
    std::swap(box_area, other.box_area);
    std::swap(stop_criterion, other.stop_criterion);
    std::swap(n_iter, other.n_iter);
    std::swap(n_dim, other.n_dim);
}

unsigned int OptimizationMethod::get_n_dim() const {
    return n_dim;
}

unsigned int OptimizationMethod::get_n_iter() const {
    return n_iter;
}

std::vector<std::vector<double>>& OptimizationMethod::get_point_history()
{
    return point_history;
}

OptimizationMethod::~OptimizationMethod() {
    point_history.resize(0);
    box_area = nullptr;
    func = nullptr;
    stop_criterion = nullptr;
}

double spheric_func(std::vector<double> arg) {
    return pow(arg[0], 2) + pow(arg[1], 2);
}

//https://en.wikipedia.org/wiki/Rosenbrock_function
// Minimum point: {1, 1}
double rosenbrock_func(std::vector<double> arg) {
    return pow(1 - arg[0], 2) + 100 * pow(arg[1] - pow(arg[0], 2), 2);
}

//https://en.wikipedia.org/wiki/Rastrigin_function
// Minimum point: {0, 0}
double rastrigin_func(std::vector<double> arg) {
    return 10 * 2 + pow(arg[0], 2) - 10 * cos(2 * M_PI * arg[0]) + pow(arg[1], 2) - 10 * cos(2 * M_PI * arg[1]);
}

// Three hump camel function https://en.wikipedia.org/wiki/Test_functions_for_optimization
// Minimum point: {0, 0}
double camel_func(std::vector<double> arg) {
    return 2 * pow(arg[0], 2) - 1.05 * pow(arg[0], 4) + pow(arg[0], 6) / 6 + arg[0] * arg[1] + pow(arg[1], 2);
}

//Gradients

std::vector<double> spheric_func_grad(std::vector<double> arg) {
    return std::vector<double>({ 2 * arg[0], 2 * arg[1] });
}

std::vector<double> rosenbrock_func_grad(std::vector<double> arg) {
    return std::vector<double>({ 2 * (200 * pow(arg[0], 3) - 200 * arg[0] * arg[1] + arg[0] - 1), 200 * (arg[1] - pow(arg[0], 2)) });
}

std::vector<double> rastrigin_func_grad(std::vector<double> arg) {
    return std::vector<double>({ 2 * arg[0] + 20 * M_PI * sin(2 * M_PI * arg[0]),
        2 * arg[1] + 20 * M_PI * sin(2 * M_PI * arg[1]) });
}

std::vector<double> camel_func_grad(std::vector<double> arg) {
    return std::vector<double>({ 4 * arg[0] - 4.2 * pow(arg[0], 3) + pow(arg[0], 5) + arg[1],
        arg[0] + 2 * arg[1] });
}