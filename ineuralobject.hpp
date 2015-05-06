#ifndef INEURALOBJECT_HPP
#define INEURALOBJECT_HPP

#include <QWidget>
#include "feedforwardnetwork.hpp"

class INeuralObject : public QWidget
{

    Q_OBJECT

protected:
    double m_val;

public:
    INeuralObject(QWidget *p_parent = 0);
    virtual ~INeuralObject(){}
    double getVal();
    virtual void setVal(double p_val);
    FeedForwardNetwork *m_FNN;

signals:
    void clicked();

public slots:
    void changeValue(double p_val);
};

#endif // INEURALOBJECT_HPP
