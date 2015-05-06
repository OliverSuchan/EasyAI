#include "feedforwardnetwork.hpp"

std::atomic<double> FeedForwardNetwork::LEARN_RATE;

double FeedForwardNetwork::getErrorSignal(std::size_t p_idxNeuron)
{
    double firstFactor = ACTIVATE_DERIVED(getInput(p_idxNeuron));
    double secondFactor;
    std::size_t layerNum = getLayer(p_idxNeuron);
    if(layerNum >= m_layers.size() - 1)
    {
        secondFactor = m_outputs.at(p_idxNeuron - getStartIndex(layerNum)) - getOutput(p_idxNeuron);
    }
    else
    {
        int startIdx = getStartIndex(layerNum + 1);
        int weightIdx = (layerNum + 2) / 2.;
        for(int idx = 0; idx < m_weights.at(weightIdx)->getColCount(); idx++)
        {
            secondFactor += getErrorSignal(startIdx + idx) * m_weights.at(weightIdx)->getVal(p_idxNeuron - getStartIndex(layerNum), idx);
        }
    }
    return firstFactor * secondFactor;
}

std::size_t FeedForwardNetwork::getStartIndex(std::size_t p_layer)
{
    std::size_t startIndex = 0;
    for(std::size_t idx = 0; idx < p_layer; idx++)
        startIndex += m_weights.at(idx)->getRowCount();
    return startIndex;
}


std::size_t FeedForwardNetwork::getLayer(std::size_t p_idxNeuron)
{
    int sum = 0;
    for(std::size_t idx = 0; idx < m_layers.size(); idx++)
    {
        if(p_idxNeuron >= sum && p_idxNeuron < (sum + m_layers.at(idx)))
        {
            return idx;
        }
        sum += m_layers.at(idx);
    }
}

double FeedForwardNetwork::getThreshold(std::size_t p_idxNeuron)
{
    std::size_t layerNumber = getLayer(p_idxNeuron);
    return m_thresholds->getVal(layerNumber, p_idxNeuron - getStartIndex(layerNumber));
}

double FeedForwardNetwork::getOutput(std::size_t p_idxNeuron)
{

    double net = getInput(p_idxNeuron);
    double threshold = getThreshold(p_idxNeuron);
    return ACTIVATE((net - threshold));
}

double FeedForwardNetwork::getInput(std::size_t p_idxNeuron)
{
    double net = .0;
    int curLayerNum = getLayer(p_idxNeuron);
    int layerNum = curLayerNum - 1;
    if(layerNum < 0)
        return getThreshold(p_idxNeuron);
    int startIdx = getStartIndex(layerNum);
    int weightIdx = layerNum / 2;
    if((curLayerNum + 1) % 2 != 0)
        weightIdx = curLayerNum / 2;
    for(int idx = 0; idx < m_weights.at(weightIdx)->getRowCount(); idx++)
    {
        double output = getOutput(startIdx + idx);
        double weight = m_weights.at(weightIdx)->getVal(idx, p_idxNeuron - (startIdx + m_weights.at(weightIdx)->getRowCount()));
        net += output * weight;
    }
    return net;
}

FeedForwardNetwork::FeedForwardNetwork(std::vector<int> p_layers, FeedForwardNetwork::Weights p_weights, Matrix<double> *p_thresholds)
{
    LEARN_RATE.store(0.7);

    m_layers = p_layers;

    for(int idx = 0; idx < p_weights.size(); idx++)
    {
        Matrix<double> *weight = new Matrix<double>(p_weights.at(idx)->getRowCount(), p_weights.at(idx)->getColCount());
        for(int x = 0; x < p_weights.at(idx)->getRowCount(); x++)
        {
            for(int y = 0; y < p_weights.at(idx)->getColCount(); y++)
            {
                weight->setVal(p_weights.at(idx)->getVal(x, y), x, y);
            }
        }
        m_weights.push_back(weight);
    }

    m_thresholds = new Matrix<double>(p_thresholds->getRowCount(), p_thresholds->getColCount());
    for(int layerIdx = 0; layerIdx < p_thresholds->getRowCount(); layerIdx++)
    {
        for(int layer = 0; layer < p_thresholds->getColCount(); layer++)
        {
            m_thresholds->setVal(p_thresholds->getVal(layerIdx, layer), layerIdx, layer);
        }
    }
}

FeedForwardNetwork::FeedForwardNetwork(std::vector<int> p_layers)
{
    LEARN_RATE.store(0.7);
    std::mt19937 mt(QTime::currentTime().msec());
    std::uniform_real_distribution<double> dist(0, 1);
    std::uniform_real_distribution<double> dist2(0, 5);
    if(p_layers.size() > 1)
    {
        m_layers = p_layers;
        int biggestLayer = p_layers.at(0);
        for(std::size_t i = 1; i < p_layers.size(); i++)
        {
            if(p_layers.at(i) > biggestLayer)
                biggestLayer = p_layers.at(i);
            Dimension dim = Dimension();
            dim.m_rowCount = p_layers.at(i - 1);
            dim.m_colCount = p_layers.at(i);
            Matrix<double>* m = new Matrix<double>(dim);

            for(std::size_t j = 0; j < dim.m_rowCount; j++)
            {
                for(std::size_t k = 0; k < dim.m_colCount; k++)
                {
                    m->setVal(dist(mt), j, k);
//                    std::cout << m->getVal(j, k) << " ";
                }
//                std::cout << std::endl;
            }
            m_weights.push_back(m);
//            std::cout << std::endl;
        }

        m_thresholds = new Matrix<double>(p_layers.size(), biggestLayer);
        for(std::size_t layer = 0; layer < p_layers.size(); layer++)
        {
            for(std::size_t neuron = 0; neuron < p_layers.at(layer); neuron++)
            {
                m_thresholds->setVal(dist2(mt), layer, neuron);
//                std::cout << m_thresholds->getVal(layer, neuron) << " ";
            }
//            std::cout << std::endl;
        }

        for(int i = 0; i < p_layers.at(p_layers.size() - 1); i++)
        {
            m_outputs.push_back(dist(mt));
        }
    }
}

void FeedForwardNetwork::setInput(std::vector<double> p_input)
{
    for(std::size_t idx = 0; idx < p_input.size(); idx++)
    {
        m_thresholds->setVal(p_input.at(idx), 0, idx);
    }
}

void FeedForwardNetwork::setOutput(std::vector<double> p_output)
{
    m_outputs = p_output;
}

void FeedForwardNetwork::optimize()
{
    int sum = 0;
    for(std::size_t weightsIdx = 0; weightsIdx < m_weights.size(); weightsIdx++)
    {
        for(std::size_t xIdx = 0; xIdx < m_weights.at(weightsIdx)->getRowCount(); xIdx++)
        {
            for(std::size_t yIdx = 0; yIdx < m_weights.at(weightsIdx)->getColCount(); yIdx++)
            {
                int i = sum + xIdx;
                int j = sum + m_weights.at(weightsIdx)->getRowCount() + yIdx;
                double curWeight = m_weights.at(weightsIdx)->getVal(xIdx, yIdx);
                double deltaWeight = LEARN_RATE.load() * getErrorSignal(j) * getOutput(i);
                m_weights.at(weightsIdx)->setVal(curWeight + deltaWeight, xIdx, yIdx);
            }
        }
        sum += m_weights.at(weightsIdx)->getRowCount();
    }
}

double FeedForwardNetwork::getError()
{
    double sum = .0;
    for(int idx = 0; idx < m_outputs.size(); idx++)
    {
        sum += std::pow((m_outputs.at(idx) - (getOutput(getStartIndex(m_layers.size() - 1) + idx))), 2);
    }
    return sum * .5;
}
