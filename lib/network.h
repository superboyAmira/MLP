#ifndef LIB_NETWORK_H_
#define LIB_NETWORK_H_

#include "perceptron/perceptron.h"

namespace s21
{

#define NETWORK_SENSOR_SIZE 144
#define NETWORK_HIDDEN_COUNT 2
#define NETWORK_HIDDEN_SIZE 240
#define NETWORK_OUTPUT_SIZE 26

class Network {
public:
    Network() {
        sensor_ = new SensorPerceptron[NETWORK_SENSOR_SIZE];
        hidden_ = new HiddenPerceptron*[NETWORK_HIDDEN_COUNT];
        output_ = new OutputPerceptron[NETWORK_OUTPUT_SIZE];
        for (size_t layer = 0; layer < NETWORK_HIDDEN_COUNT; ++layer) {
            hidden_[layer] = new HiddenPerceptron[NETWORK_HIDDEN_SIZE];
        }
    };
    ~Network() noexcept {
        delete[] sensor_;
        for (size_t layer = 0; layer < NETWORK_HIDDEN_COUNT; ++layer) {
            delete hidden_[layer];
        }
        delete[] hidden_;
        delete[] output_;
    };

    void loadData(); // геттер для будующего фасада

    vo

private:
    BasePerceptron* sensor_;
    BasePerceptron** hidden_;
    BasePerceptron* output_;
};

} // namespace s21


#endif  // LIB_NETWORK_H_