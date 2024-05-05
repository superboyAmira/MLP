#ifndef LIB_PERCEPTRON_PERCEPTRON_H_
#define LIB_PERCEPTRON_PERCEPTRON_H_

#include <map>
#include "activationrules.h"

namespace s21 {

#define PERCEPTRON_BIAS 0.0 // честно хз пока куда это засунуть, так как макросы плохо использовать
#define PERCEPTRON_ACTIVATION_LEVEL 0.7
#define PERCEPTRON_WEIGHT 1.0

using perceptron_general_activation_type = double;
using weight_type = double;

class BasePerceptron {
public:
    virtual ~BasePerceptron() noexcept = 0;
    virtual void handle() = 0;
    virtual perceptron_general_activation_type getVal() const noexcept = 0;
};

class SensorPerceptron : BasePerceptron {
public:
    SensorPerceptron() {
        output_ptr_ = nullptr;
        val_ = 0.0;
    };

    ~SensorPerceptron() noexcept override {
        output_ptr_ = nullptr;
        val_ = 0.0;
    };

    void setOuputConnection(HiddenPerceptron* perc) noexcept {
        this->output_ptr_ = perc;
    };
    
    void setVal(perceptron_general_activation_type val) noexcept {
        this->val_ = val;
    };

    perceptron_general_activation_type getVal() const noexcept override {
        return this->val_;
    };

    void handle() override {
        ActivationRules::sigmoid(this->val_, PERCEPTRON_BIAS);
        if (this->val_ <= PERCEPTRON_ACTIVATION_LEVEL) {
            output_ptr_->addConnection(this, PERCEPTRON_WEIGHT);
        }
    };

private:
    perceptron_general_activation_type val_;
    HiddenPerceptron *output_ptr_;
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

    void addConnection(BasePerceptron* p, const weight_type& weight_of_connection) {
        input_ptrs_.insert(std::make_pair(p, weight_of_connection));
    };

    void handle() override {
        for (auto& i_perc : input_ptrs_) {
            this->val_ += i_perc.first->getVal() * i_perc.second;
        }
        ActivationRules::sigmoid(this->val_, PERCEPTRON_BIAS);
        if (this->val_ <= PERCEPTRON_ACTIVATION_LEVEL) {
            output_ptr_->addConnection(this, PERCEPTRON_WEIGHT);
        }
    };

private:
    HiddenPerceptron *output_ptr_;
    std::map<BasePerceptron*, weight_type> input_ptrs_;
    perceptron_general_activation_type val_;
    
};

class OutputPerceptron : BasePerceptron {
public:
    OutputPerceptron() {
        input_ptrs_.clear();
        val_ = 0.0;
    };

    ~OutputPerceptron() noexcept override {
        val_ = 0.0;
        input_ptrs_.clear();
    };

    perceptron_general_activation_type getVal() const noexcept override {
        return this->val_;
    };

    void handle() override {
        for (auto& i_perc : input_ptrs_) {
            this->val_ += i_perc.first->getVal() * i_perc.second;
        }
        ActivationRules::sigmoid(this->val_, PERCEPTRON_BIAS);
    };

private:
    std::map<HiddenPerceptron*, weight_type> input_ptrs_;
    perceptron_general_activation_type val_;

};

}; // s21

#endif  // LIB_PERCEPTRON_PERCEPTRON_H_