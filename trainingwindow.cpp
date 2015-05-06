#include "trainingwindow.hpp"
#include "ui_trainingwindow.h"

void TrainingWindow::setNetwork(FeedForwardNetwork *p_network)
{
    m_FNN = p_network;
    this->ui->horizontalSlider->setValue(m_FNN->LEARN_RATE.load() * 100.);
    this->ui->tableWidget->insertRow(0);
    for(int i = 0; i < m_FNN->m_layers.at(0); i++)
    {
        this->ui->tableWidget->insertColumn(i);
        this->ui->tableWidget->setItem(0, i, new QTableWidgetItem(QString::number(m_FNN->getThreshold(i))));
    }
    this->ui->tableWidget_2->insertRow(0);
    for(int i = 0; i < m_FNN->m_layers.at(m_FNN->m_layers.size() - 1); i++)
    {
        this->ui->tableWidget_2->insertColumn(i);
        this->ui->tableWidget_2->setItem(0, i, new QTableWidgetItem(QString::number(m_FNN->m_outputs.at(i))));
    }
}

TrainingWindow::TrainingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrainingWindow)
{
    ui->setupUi(this);
    m_plotWidget = new PlotWidget(this->ui->tab_2);
    m_plotWidget->setGeometry(10, 10, 755, 450);
    m_plotWidget->show();
    m_train.store(false);
}

TrainingWindow::~TrainingWindow()
{
    delete ui;
}

void TrainingWindow::on_pushButton_clicked()
{
    this->ui->horizontalSlider->setValue(m_FNN->LEARN_RATE.load() * 100.);
    m_plotWidget->clearDots();
    m_train.store(true);
    m_trainingThread = new std::thread(&TrainingWindow::train, this);
}

void TrainingWindow::closeEvent(QCloseEvent *p_closeEvent)
{
    emit closed();
    p_closeEvent->accept();
}

void TrainingWindow::train()
{
    while(m_train.load())
    {
        m_mutex.lock();
        this->ui->label_2->setText(QString::number(m_FNN->LEARN_RATE.load()));
        double error = m_FNN->getError();
        m_plotWidget->addDot(error);
        m_FNN->optimize();
        m_mutex.unlock();
    }
}


void TrainingWindow::on_pushButton_2_clicked()
{
    m_train.store(false);
    m_trainingThread->join();
}

void TrainingWindow::on_horizontalSlider_valueChanged(int value)
{
    if(!m_train.load())
        m_FNN->LEARN_RATE.store(value / 100.);
}

void TrainingWindow::on_pushButton_5_clicked()
{
    this->close();
}

void TrainingWindow::on_pushButton_4_clicked()
{
    std::mt19937 mt(QTime::currentTime().msec());
    std::uniform_real_distribution<double> dist(0, 1);
    for(int i = 0; i < this->ui->tableWidget->columnCount(); i++)
        ui->tableWidget->setItem(0, i, new QTableWidgetItem(QString::number(dist(mt))));

    for(int i = 0; i < this->ui->tableWidget_2->columnCount(); i++)
        ui->tableWidget_2->setItem(0, i, new QTableWidgetItem(QString::number(dist(mt))));
}

void TrainingWindow::on_pushButton_3_clicked()
{
    std::vector<double> input;
    for(int i = 0; i < this->ui->tableWidget->columnCount(); i++)
        input.push_back(this->ui->tableWidget->item(0, i)->text().toDouble());
    m_FNN->setInput(input);

    std::vector<double> output;
    for(int i = 0; i < this->ui->tableWidget_2->columnCount(); i++)
        output.push_back(ui->tableWidget_2->item(0, i)->text().toDouble());
    m_FNN->setOutput(output);
}
