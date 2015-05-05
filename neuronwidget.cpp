#include "neuronwidget.hpp"


void NeuronWidget::paintEvent(QPaintEvent *)
{
    QColor drawColor = m_neuronColor;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if(m_mouseOver.load())
    {
        drawColor.setAlpha(200);
    }
    int border = 3;
    double rad = this->size().width() / 2. - border;
    painter.setBrush(Qt::gray);
    painter.drawEllipse(QPointF(this->size().width() / 2., this->size().height() / 2.),rad + border, rad + border);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(drawColor));
    painter.drawEllipse(QPoint(this->size().width() / 2, this->size().height() / 2), rad, rad);
}

void NeuronWidget::leaveEvent(QEvent *)
{
    m_mouseOver.store(false);
    repaint();
}

void NeuronWidget::enterEvent(QEvent *)
{
    m_mouseOver.store(true);
    repaint();
}

void NeuronWidget::mouseMoveEvent(QMouseEvent *p_mouseEvent)
{
    if(m_mousePress.load())
    {
        emit dragDrop();
    }
}

void NeuronWidget::mousePressEvent(QMouseEvent *p_mouseEvent)
{
    m_mousePress.store(true);
}

void NeuronWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePress.store(false);
}

NeuronWidget::NeuronWidget(QWidget *parent)
    : QWidget(parent)
{
    m_neuronColor = QColor(Qt::darkBlue);
    m_mouseOver.store(false);
    m_mousePress.store(true);
}

void NeuronWidget::setLayer(int p_layerIdx)
{
    m_layer.store(p_layerIdx);
}

int NeuronWidget::getLayer()
{
    return m_layer.load();
}

void NeuronWidget::setNeuron(int p_neuronIdx)
{
    m_neuronIdx.store(p_neuronIdx);
}

int NeuronWidget::getNeuron()
{
    return m_neuronIdx.load();
}

NeuronWidget::~NeuronWidget()
{

}

