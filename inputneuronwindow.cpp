#include "inputneuronwindow.hpp"
#include "ui_inputneuronwindow.h"

InputNeuronWindow::InputNeuronWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InputNeuronWindow)
{
    ui->setupUi(this);
}

InputNeuronWindow::~InputNeuronWindow()
{
    delete ui;
}
