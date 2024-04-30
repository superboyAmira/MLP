#ifndef LIB_PERCEPTRON_ACTIVATIONRULES_H_
#define LIB_PERCEPTRON_ACTIVATIONRULES_H_

#include <cmath>

namespace s21
{

class ActivationRules {
public:
    static void sigmoid(double& x, double bias) noexcept {
        x += bias;
        x = 1 / (1 + exp(-x));
    }

    static void relu(double& x, double bias) noexcept {
        x += bias;
        x = x > 0 ? x : 0;
    }
};

} // namespace s21


#endif  // LIB_PERCEPTRON_ACTIVATIONRULES_H_