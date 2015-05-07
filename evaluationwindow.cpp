#include "evaluationwindow.hpp"
#include "ui_evaluationwindow.h"

void EvaluationWindow::setNetwork(FeedForwardNetwork *p_network)
{
    m_FNN = p_network;
    for(int i = 0; i < m_FNN->m_layers.at(0); i++)
    {
        this->ui->tableWidget->insertColumn(i);
    }

    for(int i = 0; i < m_FNN->m_layers.at(m_FNN->m_layers.size() - 1); i++)
    {
        this->ui->tableWidget_2->insertColumn(i);
    }
}

EvaluationWindow::EvaluationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EvaluationWindow)
{
    ui->setupUi(this);
}

EvaluationWindow::~EvaluationWindow()
{
    delete ui;
}

void EvaluationWindow::on_pushButton_clicked()
{
    this->ui->tableWidget->insertRow(this->ui->tableWidget->rowCount());
}

void EvaluationWindow::on_pushButton_2_clicked()
{
    this->ui->tableWidget->removeRow(this->ui->tableWidget_2->currentRow());
}

void EvaluationWindow::on_pushButton_3_clicked()
{
    this->ui->tableWidget_2->clear();
    this->ui->tableWidget_2->setRowCount(0);
    for(int rowIdx = 0; rowIdx < this->ui->tableWidget->rowCount(); rowIdx++)
    {
        std::vector<double> input;
        for(int colIdx = 0; colIdx < this->ui->tableWidget->columnCount(); colIdx++)
        {
            input.push_back(this->ui->tableWidget->item(rowIdx, colIdx)->text().toDouble());
        }
        m_FNN->setInput(input);

        this->ui->tableWidget_2->insertRow(this->ui->tableWidget_2->rowCount());
        for(int outputIdx = 0; outputIdx < this->ui->tableWidget_2->columnCount(); outputIdx++)
        {

            int neuronIdx = outputIdx + m_FNN->getStartIndex(m_FNN->m_layers.size() - 1);
            this->ui->tableWidget_2->setItem(rowIdx, outputIdx, new QTableWidgetItem(QString::number(m_FNN->getOutput(neuronIdx))));
        }
    }
}
