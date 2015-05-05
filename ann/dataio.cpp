#include "dataio.hpp"
#include <iostream>

DataIO::DataIO()
{

}

void DataIO::saveBinary(Weights p_weights, Matrix<double> *p_thresholds, std::vector<int> p_layers,
                        const char *p_filename){


    //Format of header: |numberLayers|threshold x|threshold y|WeightsSize||Matrix x|Matrix y(WeightSize times)||...Data...|

    QFile f(p_filename);
    f.open(QIODevice::WriteOnly);
    QDataStream out(&f);

    //file-header
    out << (qint32)p_layers.size();
    out << (qint32)p_weights.size();
    out << p_thresholds->getRowCount();
    out << p_thresholds->getColCount();
    for(int i = 0; i < p_weights.size(); i++)
    {
        out << (qint32)p_weights.at(i)->getColCount();
        out << (qint32)p_weights.at(i)->getRowCount();
    }


    //layers
    for(int i = 0; i < p_layers.size(); i++)
    {
        out << (qint32)p_layers.at(i);
    }
    //thresholds
    //this loop causes error!!!!
    for(int x = 0; x < p_thresholds->getRowCount(); x++)
    {
        for(int y = 0; y < p_thresholds->getColCount(); y++)
        {
            out << p_thresholds->getVal(x, y);
        }
    }

    //weights
    for(int i = 0; i < p_weights.size(); i++){
        for(int x = 0; x < p_weights.at(i)->getRowCount(); x++){
            for(int y = 0; y < p_weights.at(i)->getColCount(); y++){
                out << p_weights.at(i)->getVal(x, y);
            }

        }

    }
}

FeedForwardNetwork* DataIO::loadBinary(const char *p_filename){

    //Format of header: |numberLayers|threshold x|threshold y|WeightsSize||Matrix x|Matrix y(WeightSize times)||...Data...|

    QFile f(p_filename);
    f.open(QIODevice::ReadOnly);
    QDataStream in(&f);

    std::vector<int> layers;
    Matrix<double> *thresholds;
    Weights weights;

    //file-header
    qint32 numberLayers;
    qint32 weightSize;
    qint32 thresholdX;
    qint32 thresholdY;

    std::vector<qint32> mX;
    std::vector<qint32> mY;


    in >> numberLayers;
    in >> weightSize;
    in >> thresholdX;
    in >> thresholdY;

    thresholds = new Matrix<double>(thresholdX, thresholdY);

    for(int i = 0; i < weightSize; i++){
        qint32 x;
        qint32 y;
        in >> x;
        in >> y;
        mX.push_back(x);
        mY.push_back(y);
    }

    //layers
    qint32 inInt;
    for(int i = 0; i < numberLayers; i++){
        in >> inInt;
        layers.push_back(inInt);
    }

    //thresholds
    double inDouble;
    for(int x = 0; x < thresholdX; x++){
        for(int y = 0; y < thresholdY; y++){
            in >> inDouble;
            thresholds->setVal(inDouble, x, y);
        }
    }

//    Weights
    double val;
    for(int i = 0; i < weightSize; i++){
        Matrix<double> *weight = new Matrix<double>(mY.at(i), mX.at(i));
        for(int x = 0; x < mY.at(i); x++){
            for(int y = 0; y < mX.at(i); y++){
                in >> val;
                weight->setVal(val, x, y);
            }
        }
        weights.push_back(weight);
    }


    FeedForwardNetwork* fnn = new FeedForwardNetwork(layers, weights, thresholds);
    return fnn;
}






