#ifndef LIB_PERCEPTRON_PERCEPTRON_H_
#define LIB_PERCEPTRON_PERCEPTRON_H_

#include <map>
#include "activationrules.h"

namespace s21 {

#define PERCEPTRON_BIAS 1.0 // честно хз пока куда это засунуть, так как макросы плохо использовать
#define PERCEPTRON_ACTIVATION_LEVEL 0.7
#define PERCEPTRON_WEIGHT 1.0

using perceptron_general_activation_type = double;
using weight_type = double;

class BasePerceptron {
public:
    BasePerceptron() {
        input_ptrs_.clear();
        val_ = 0.0;
    };

    virtual ~BasePerceptron() noexcept {
        this->val_ = 0.0;
        input_ptrs_.clear();
    };
    
    virtual void handle() = 0;
    
    perceptron_general_activation_type getVal() const noexcept {
        return this->val_;
    };

    void setVal(perceptron_general_activation_type val) noexcept {
        this->val_ = val;
    };

    void addConnection(BasePerceptron* p, const weight_type& weight_of_connection) {
        input_ptrs_.insert(std::make_pair(p, weight_of_connection));
    };

protected:
    perceptron_general_activation_type val_;
    std::map<BasePerceptron*, weight_type> input_ptrs_;
};

class HiddenPerceptron : public BasePerceptron {
public:
    void handle() override {
        for (auto& i_perc : input_ptrs_) {
            this->val_ += i_perc.first->getVal() * i_perc.second;
        }
        ActivationRules::sigmoid(this->val_, PERCEPTRON_BIAS);
        if (this->val_ <= PERCEPTRON_ACTIVATION_LEVEL) {
            val_ = 0.0;
        }
    };
};


class SensorPerceptron : public BasePerceptron {
public:
    void addConnection(BasePerceptron* p, const weight_type& weight_of_connection) = delete;
    
    void handle() override {
        ActivationRules::sigmoid(this->val_, PERCEPTRON_BIAS);
        if (this->val_ <= PERCEPTRON_ACTIVATION_LEVEL) {
            val_ = 0.0;
        }
    };
};


class OutputPerceptron : public BasePerceptron {
public:
    void handle() override {
        for (auto& i_perc : input_ptrs_) {
            this->val_ += i_perc.first->getVal() * i_perc.second;
        }
        ActivationRules::sigmoid(this->val_, PERCEPTRON_BIAS);
        if (this->val_ <= PERCEPTRON_ACTIVATION_LEVEL) {
            val_ = 0.0;
        }
    };
};

}; // s21

#endif  // LIB_PERCEPTRON_PERCEPTRON_H_