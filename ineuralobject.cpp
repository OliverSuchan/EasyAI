#include "ineuralobject.hpp"

INeuralObject::INeuralObject(QWidget *p_parent)
    : QWidget(p_parent)
{

}

double INeuralObject::getVal()
{
    return m_val;
}

void INeuralObject::setVal(double p_val)
{
    m_val = p_val;
}

void INeuralObject::changeValue(double p_val)
{
    setVal(p_val);
}
