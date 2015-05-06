#include "neuronwidget.hpp"


void NeuronWidget::paintEvent(QPaintEvent *)
{
    QColor drawColor = m_neuronColor;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(m_mouseOver.load())
    {
        drawColor.setAlpha(170);
    }

    if(m_mousePress.load())
    {
        m_borderColor = Qt::white;
    }
    else
    {
        m_borderColor = Qt::gray;
    }

    int border = 3;
    double rad = this->size().width() / 2. - border;
    painter.setBrush(m_borderColor);
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

void NeuronWidget::mouseDoubleClickEvent(QMouseEvent *p_mouseEvent)
{
    if(p_mouseEvent->button() == Qt::LeftButton)
        emit clicked();
}

void NeuronWidget::mousePressEvent(QMouseEvent *)
{
    m_mousePress.store(true);
    repaint();
}

void NeuronWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePress.store(false);
    repaint();
}

NeuronWidget::NeuronWidget(QWidget *parent)
    : INeuralObject(parent)
{
    m_neuronColor = Qt::darkBlue;
    m_borderColor = Qt::gray;
    m_mouseOver.store(false);
    m_mousePress.store(false);
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

void NeuronWidget::setVal(double p_val)
{
    INeuralObject::setVal(p_val);
    m_FNN->m_thresholds->setVal(p_val, m_layer, (m_neuronIdx - m_FNN->getStartIndex(m_layer)));
}

NeuronWidget::~NeuronWidget()
{

}

