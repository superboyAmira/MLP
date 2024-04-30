#ifndef LIB_PERCEPTRON_PERCEPTRON_H_
#define LIB_PERCEPTRON_PERCEPTRON_H_

#include <map>
#include "activationrules.h"

namespace s21 {

#define BIAS 0.0

using perceptron_general_activation_type = double;
using weight_type = double;

class BasePerceptron {
public:
    virtual ~BasePerceptron() noexcept = 0;
    virtual void handle() = 0;
    virtual perceptron_general_activation_type getVal() const noexcept = 0;
    static const double activation_level = 0.7; // честно хз пока куда это засунуть
    static const double random_weight = 1.0; //  тоже
};

class SensorPerceptron : BasePerceptron {
public:
    ~SensorPerceptron() noexcept override {};
};

class HiddenPerceptron : BasePerceptron {
public:
    HiddenPerceptron() {
        output_ptr_ = nullptr;
        input_ptrs_.clear();
        val_ = 0.0;
    };

    ~HiddenPerceptron() noexcept override {
        val_ = 0.0;
        input_ptrs_.clear();
    };

    perceptron_general_activation_type getVal() const noexcept override {
        return this->val_;
    };

    void addConnection(HiddenPerceptron* p, const weight_type& weight_of_connection) {
        input_ptrs_.insert(std::make_pair(p, weight_of_connection));
    }

    void handle() override {
        for (auto& i_perc : input_ptrs_) {
            this->val_ += i_perc.first->getVal() * i_perc.second;
        }
        ActivationRules::sigmoid(this->val_, BIAS);
        if (this->val_ <= this->activation_level) {
            output_ptr_->addConnection(this, this->random_weight);
        }
    };

private:
    HiddenPerceptron *output_ptr_;
    std::map<HiddenPerceptron*, weight_type> input_ptrs_;
    perceptron_general_activation_type val_;
    
};

class OutputPerceptron : BasePerceptron {
public:
    ~OutputPerceptron() noexcept override {};
};

}; // s21

#endif  // LIB_PERCEPTRON_PERCEPTRON_H_