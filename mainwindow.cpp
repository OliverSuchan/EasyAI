#include "mainwindow.hpp"
#include "ui_mainwindow.h"

void MainWindow::mousePressEvent(QMouseEvent *p_mouseEvent)
{
    for(Connection& con : m_connections)
    {
        if(con.contains(p_mouseEvent->localPos()))
        {
            con.setPenWidth(Connection::MOUSE_OVER);
            repaint();
            return;
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
//    painter.eraseRect(this->geometry());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::black);
    QPen pen;
    pen.setBrush(Qt::black);
    for(Connection con : m_connections)
    {
        pen.setWidth(con.penWidth());
        painter.setPen(pen);
        painter.drawLine(con.startPos(), con.endPos());
    }
}

void MainWindow::initConnections()
{
    m_connections.clear();
    int sum = 0;
    for(std::size_t weightsIdx = 0; weightsIdx < m_FNN->m_weights.size(); weightsIdx++)
    {
        for(std::size_t xIdx = 0; xIdx < m_FNN->m_weights.at(weightsIdx)->getRowCount(); xIdx++)
        {
            for(std::size_t yIdx = 0; yIdx < m_FNN->m_weights.at(weightsIdx)->getColCount(); yIdx++)
            {
                int i = sum + xIdx;
                int j = sum + m_FNN->m_weights.at(weightsIdx)->getRowCount() + yIdx;
                NeuronWidget *firstNeuron = m_neurons.at(i);
                NeuronWidget *secondNeuron = m_neurons.at(j);

                Connection con(firstNeuron->pos() + QPoint(firstNeuron->size().width() / 2, firstNeuron->size().height() / 2), secondNeuron->pos() + QPoint(secondNeuron->size().width() / 2, secondNeuron->size().height() / 2));
                m_connections.push_back(con);
            }
        }
        sum += m_FNN->m_weights.at(weightsIdx)->getRowCount();
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_FNN = new FeedForwardNetwork({2, 4, 2, 2});
    int sum = 0;
    for(int layerIdx = 0; layerIdx < m_FNN->m_layers.size(); layerIdx++)
    {
        sum = m_FNN->getStartIndex(layerIdx);
        for(int neuronIdx = 0; neuronIdx < m_FNN->m_layers.at(layerIdx); neuronIdx++)
        {
            NeuronWidget *curNeuron;
            if(layerIdx == 0)
                curNeuron = new InputNeuron(this);
            else if(layerIdx == m_FNN->m_layers.size() - 1)
                curNeuron = new OutputNeuron(this);
            else
                curNeuron = new NeuronWidget(this);
            curNeuron->setLayer(layerIdx);
            curNeuron->setNeuron(sum + neuronIdx);
            curNeuron->setGeometry(100 + layerIdx * 90, 50 + neuronIdx * 90, 46, 46);
            curNeuron->show();
            connect(curNeuron, &NeuronWidget::dragDrop, this, &MainWindow::execDrag);
            m_neurons.push_back(curNeuron);
        }
    }
    initConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::execDrag()
{
    QWidget *dragNeuron = dynamic_cast<QWidget*>(sender());
    dragNeuron->move(this->mapFromGlobal(QCursor::pos()));
    initConnections();
    this->repaint();
}
