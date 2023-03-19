#include "pch.h"
#include "MDFunction.h"

MDFunction::MDFunction() {

};

MDFunction::MDFunction(std::vector<double>(*func_)(std::vector<double>),
    unsigned int arg_n_dim_) : func(func_), arg_n_dim(arg_n_dim_) {

}

MDFunction::MDFunction(const MDFunction& other) : func(other.func), arg_n_dim(other.arg_n_dim) {

}

MDFunction::MDFunction(MDFunction&& other) noexcept : func(other.func), arg_n_dim(other.arg_n_dim) {
    other.func = nullptr;
    other.arg_n_dim = 0;
}

std::vector<double> MDFunction::operator()(const std::vector<double>& args) const {
    return func(args);
}

MDFunction& MDFunction::operator=(MDFunction other) {
    this->swap(other);
    return *this;
}

void MDFunction::swap(MDFunction& other) noexcept {
    std::swap(arg_n_dim, other.arg_n_dim);
    std::swap(func, other.func);
}

unsigned int MDFunction::get_arg_n_dim() const {
    return arg_n_dim;
}

void MDFunction::set_func(std::vector<double>(*new_func)(std::vector<double>), unsigned int new_arg_n_dim) {
    arg_n_dim = new_arg_n_dim;
    func = new_func;
}

MDFunction::~MDFunction() {
    func = nullptr;
    arg_n_dim = 0;
}