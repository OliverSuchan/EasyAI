#ifndef NEURONWIDGET_HPP
#define NEURONWIDGET_HPP

#include <iostream>
#include <atomic>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class NeuronWidget : public QWidget
{
    Q_OBJECT

protected:
    std::atomic<bool> m_mouseOver;
    std::atomic<bool> m_mousePress;
    std::atomic<int> m_layer;
    std::atomic<int> m_neuronIdx;
    QColor m_neuronColor;
    void paintEvent(QPaintEvent *);
    void leaveEvent(QEvent *);
    void enterEvent(QEvent *);
    void mouseMoveEvent(QMouseEvent *p_mouseEvent);
    void mousePressEvent(QMouseEvent *p_mouseEvent);
    void mouseReleaseEvent(QMouseEvent *);

public:
    explicit NeuronWidget(QWidget *parent = 0);
    void setLayer(int p_layerIdx);
    int getLayer();
    void setNeuron(int p_neuronIdx);
    int getNeuron();
    ~NeuronWidget();

signals:
    void dragDrop();

public slots:

};

#endif // NEURONWIDGET_HPP
