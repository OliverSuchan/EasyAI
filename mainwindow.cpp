#include "mainwindow.hpp"
#include "ui_mainwindow.h"

void MainWindow::mousePressEvent(QMouseEvent *p_mouseEvent)
{
    for(Connection* con : m_connections)
    {
        if(con->contains(p_mouseEvent->localPos()))
        {
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
    for(Connection* con : m_connections)
    {
        pen.setBrush(con->drawColor());
        pen.setWidth(con->penWidth());
        painter.setPen(pen);
        painter.drawLine(con->startPos(), con->endPos());
    }
}

void MainWindow::initNetwork()
{
    for(NeuronWidget* neuron : m_neurons)
    {
        delete neuron;
        neuron = nullptr;
    }
    m_neurons.clear();
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

            curNeuron->m_FNN = m_FNN;
            curNeuron->setLayer(layerIdx);
            curNeuron->setNeuron(sum + neuronIdx);
            curNeuron->setVal(m_FNN->getThreshold(sum + neuronIdx));
            curNeuron->setGeometry(100 + layerIdx * 90, 50 + neuronIdx * 90, 46, 46);
            curNeuron->show();

            connect(curNeuron, &NeuronWidget::dragDrop, this, &MainWindow::execDrag);
            connect(curNeuron, &INeuralObject::clicked, this, &MainWindow::neuralObjectClicked);
            m_neurons.push_back(curNeuron);
        }
    }
    initConnections();
}

void MainWindow::initConnections()
{
    for(Connection* con : m_connections)
    {
        delete con;
        con = nullptr;
    }
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

                Connection* con = new Connection(firstNeuron, secondNeuron);
                con->m_FNN = m_FNN;
                con->setIndices(weightsIdx, xIdx, yIdx);
                con->setVal(m_FNN->m_weights.at(weightsIdx)->getVal(xIdx, yIdx));
                connect(con, &INeuralObject::clicked, this, &MainWindow::neuralObjectClicked);
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
    m_dataIO = new DataIO();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::execDrag()
{
    QWidget *dragNeuron = dynamic_cast<QWidget*>(sender());
    dragNeuron->move(this->mapFromGlobal(QCursor::pos()));
    //initConnections();
    this->repaint();
}

void MainWindow::createNetwork(QString p_network)
{
    QStringList layerCount = p_network.split(";");
    std::vector<int> layers;
    for(int i = 0; i < layerCount.size(); i++)
        layers.push_back(layerCount[i].toInt());
    m_FNN = new FeedForwardNetwork(layers);
    initNetwork();
    repaint();
}

void MainWindow::neuralObjectClicked()
{
    SetValueWindow *setValWin = new SetValueWindow(this);
    INeuralObject *neuralObj = dynamic_cast<INeuralObject*>(sender());
    setValWin->setCurVal(QString::number(neuralObj->getVal()));
    connect(setValWin, &SetValueWindow::changeValue, neuralObj, &INeuralObject::changeValue);
    setValWin->show();
}

void MainWindow::updateNetwork()
{
    initNetwork();
}

void MainWindow::on_actionLaden_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Lade Künstliches Neuronales Netzwerk", QDir::currentPath(), "Neuronales Netzwerk (*.knn)");
    m_FNN = m_dataIO->loadBinary(fileName.toStdString().c_str());
    initNetwork();
    repaint();
}

void MainWindow::on_actionSpeichern_triggered()
{
   QString fileName = QFileDialog::getSaveFileName(this, "Speichere Künstliches Neuronales Netzwerk", QDir::currentPath(), "Neuronales Netzwerk (*.knn)");
   m_dataIO->saveBinary(m_FNN->m_weights, m_FNN->m_thresholds, m_FNN->m_layers, fileName.toStdString().c_str());
}

void MainWindow::on_actionNeues_Netzwerk_triggered()
{
    CreateNetworkWindow *networkWindow = new CreateNetworkWindow(this);
    connect(networkWindow, &CreateNetworkWindow::createNetwork, this, &MainWindow::createNetwork);
    networkWindow->show();
}

void MainWindow::on_actionNetzwerk_trainieren_triggered()
{
    TrainingWindow *tw = new TrainingWindow(this);
    tw->setNetwork(m_FNN);
    tw->show();
    connect(tw, &TrainingWindow::closed, this, &MainWindow::updateNetwork);
}
