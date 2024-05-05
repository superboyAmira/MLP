#ifndef LIB_NETWORK_H_
#define LIB_NETWORK_H_

#include "perceptron/perceptron.h"

namespace s21
{

#define NETWORK_SENSOR_SIZE 144
#define NETWORK_HIDDEN_SIZE 500
#define NETWORK_OUTPUT_SIZE 26

class Network {
public:
    

    Network() {};
    ~Network() noexcept {};

private:
    BasePerceptron* sensor_;

    BasePerceptron* hiden_layer_1_;
    BasePerceptron* hiden_layer_2_;
    BasePerceptron* hiden_layer_3_;
    BasePerceptron* hiden_layer_4_;
    BasePerceptron* hiden_layer_5_;

    BasePerceptron* output_;
};

} // namespace s21


#endif  // LIB_NETWORK_H_