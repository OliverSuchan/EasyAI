#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <iostream>
#include <QPoint>
#include <QRect>
#include "ineuralobject.hpp"
#include "neuronwidget.hpp"

class Connection : public INeuralObject
{

    Q_OBJECT

private:
    NeuronWidget *m_startNeuron;
    NeuronWidget *m_endNeuron;
    QColor m_drawColor;
    int m_penWidth;
    int m_weightIdx;
    int m_xIdx;
    int m_yIdx;
    static constexpr int m_penMouseOverWidth = 5;
    static constexpr int m_penNormalWidth = 3;

public:
    enum PenType
    {
        NORMAL,
        MOUSE_OVER
    };

    Connection(NeuronWidget *firstNeuron, NeuronWidget *secondNeuron);
    ~Connection();
    bool contains(QPointF p_pos);
    int penWidth();
    QColor drawColor();
    void setPenWidth(PenType p_penType);
    void setIndices(int p_weightIdx, int p_xIdx, int p_yIdx);
    void setVal(double p_val) override;
    QPoint endPos();
    QPoint startPos();
};

#endif // CONNECTION_HPP
