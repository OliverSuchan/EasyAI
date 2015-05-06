#include "connection.hpp"


int Connection::penWidth()
{
    return m_penWidth;
}

QColor Connection::drawColor()
{
    return m_drawColor;
}

void Connection::setPenWidth(PenType p_penType)
{
    switch(p_penType)
    {
    case NORMAL:
        m_penWidth = Connection::m_penNormalWidth;
        m_drawColor = Qt::black;
        break;

    case MOUSE_OVER:
        m_penWidth = Connection::m_penMouseOverWidth;
        m_drawColor = Qt::red;
        break;
    }
}

QPoint Connection::endPos()
{
    return m_endNeuron->pos() + QPoint(m_endNeuron->size().width() / 2., m_endNeuron->size().height() / 2.);
}

QPoint Connection::startPos()
{
    return m_startNeuron->pos() + QPoint(m_startNeuron->size().width() / 2., m_startNeuron->size().height() / 2.);
}

void Connection::setIndices(int p_weightIdx, int p_xIdx, int p_yIdx)
{
    m_weightIdx = p_weightIdx;
    m_xIdx = p_xIdx;
    m_yIdx = p_yIdx;
}
void Connection::setVal(double p_val)
{
    INeuralObject::setVal(p_val);
    m_FNN->m_weights.at(m_weightIdx)->setVal(p_val, m_xIdx, m_yIdx);
}

Connection::Connection(NeuronWidget *firstNeuron, NeuronWidget *secondNeuron)
    : INeuralObject()
{
    m_startNeuron = firstNeuron;
    m_endNeuron = secondNeuron;
    m_drawColor = Qt::black;
    m_penWidth = Connection::m_penNormalWidth;
}


Connection::~Connection()
{

}

bool Connection::contains(QPointF p_pos)
{
    QPoint startPosi = startPos();
    QPoint endPosi = endPos();
    QRect rect(startPosi, endPosi);
    double m = (double)rect.height() / (double)rect.width();
    double b = startPosi.y() - m * startPosi.x(); // m * x + b = y <=> b = y - m * x
    if(p_pos.x() >= rect.x() && p_pos.x() <= rect.x() + rect.width())
    {
        double result = m * p_pos.x() + b;
        if(p_pos.y() >= result - m_penWidth && p_pos.y() <= result + m_penWidth)
        {
            setPenWidth(MOUSE_OVER);
            emit clicked();
            return true;
        }
    }
    return false;
}

