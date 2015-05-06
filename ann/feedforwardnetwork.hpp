#ifndef FEEDFORWARDNETWORK_HPP
#define FEEDFORWARDNETWORK_HPP

#include <vector>
#include <random>
#include <cmath>
#include <QTime>
#include "matrix.hpp"

#define ACTIVATE(x) (1.0 / (1.0 + std::exp(-x)))
#define ACTIVATE_DERIVED(x) (ACTIVATE(x) * (1.0 - ACTIVATE(x)))

class FeedForwardNetwork
{
    friend class MainWindow;
    friend class NeuronWidget;
    friend class Connection;

private:
    typedef std::vector<Matrix<double>*> Weights;
    Weights m_weights;
    Matrix<double> *m_thresholds;
    std::vector<int> m_layers;
    std::vector<double> m_outputs;
    double getErrorSignal(std::size_t p_idxNeuron);
    std::size_t getStartIndex(std::size_t p_layer);
    std::size_t getLayer(std::size_t p_idxNeuron);
    double getThreshold(std::size_t p_idxNeuron);
    double getOutput(std::size_t p_idxNeuron);
    double getInput(std::size_t p_idxNeuron);
    static constexpr double LEARN_RATE = 3;

public:
    FeedForwardNetwork(std::vector<int> p_layers, Weights p_weights, Matrix<double> *p_thresholds);
    FeedForwardNetwork(std::vector<int> p_layers);
    void setInput(std::vector<double> p_input);
    void setOutput(std::vector<double> p_output);
    void addLayer(int p_idxOfLayer, int p_nrNewNeurons, std::vector<double> p_thresholds);
    void addNeuron(int p_layer, int p_idxInLayer, double p_threshold);
    void optimize();
    double getError();

};

#endif // FEEDFORWARDNETWORK_HPP
