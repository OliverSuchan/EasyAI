#ifndef NEURONWIDGET_HPP
#define NEURONWIDGET_HPP

#include <iostream>
#include <atomic>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "ineuralobject.hpp"

class NeuronWidget : public INeuralObject
{
    Q_OBJECT

protected:
    std::atomic<bool> m_mouseOver;
    std::atomic<bool> m_mousePress;
    std::atomic<int> m_layer;
    std::atomic<int> m_neuronIdx;
    QColor m_neuronColor;
    QColor m_borderColor;
    void paintEvent(QPaintEvent *);
    void leaveEvent(QEvent *);
    void enterEvent(QEvent *);
    void mouseMoveEvent(QMouseEvent *p_mouseEvent);
    void mouseDoubleClickEvent(QMouseEvent *p_mouseEvent);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

public:
    explicit NeuronWidget(QWidget *parent = 0);
    void setLayer(int p_layerIdx);
    int getLayer();
    void setNeuron(int p_neuronIdx);
    int getNeuron();
    void setVal(double p_val) override;
    ~NeuronWidget();

signals:
    void dragDrop();

public slots:

};

#endif // NEURONWIDGET_HPP
