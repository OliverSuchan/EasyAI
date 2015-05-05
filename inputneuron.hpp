#ifndef INPUTNEURON_HPP
#define INPUTNEURON_HPP

#include "neuronwidget.hpp"

class InputNeuron : public NeuronWidget
{
public:
    InputNeuron(QWidget *p_parent = nullptr);
    ~InputNeuron();
};

#endif // INPUTNEURON_HPP
