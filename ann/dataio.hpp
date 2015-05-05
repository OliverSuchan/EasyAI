#ifndef DATAIO_HPP
#define DATAIO_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <QString>
#include <QTextStream>
#include <QFile>
#include "matrix.hpp"
#include "feedforwardnetwork.hpp"

class FeedForwardNetwork;

class DataIO
{
private:
    typedef std::vector<Matrix<double>*> Weights;

public:
    DataIO();

    void saveBinary(Weights p_weights, Matrix<double> *p_thresholds, std::vector<int> p_layers, const char *p_filename);
    FeedForwardNetwork* loadBinary(const char *p_filename);
};

#endif // DATAIO_HPP
