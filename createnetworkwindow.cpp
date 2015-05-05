#include "createnetworkwindow.hpp"
#include "ui_createnetworkwindow.h"

CreateNetworkWindow::CreateNetworkWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateNetworkWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setGeometry((QApplication::primaryScreen()->size().width() - this->size().width()) / 2, (QApplication::primaryScreen()->size().height() - this->size().height()) / 2, this->size().width(), this->size().height());
}

CreateNetworkWindow::~CreateNetworkWindow()
{
    delete ui;
}

void CreateNetworkWindow::on_pushButton_2_clicked()
{
    this->close();
}

void CreateNetworkWindow::on_pushButton_clicked()
{
    if(this->ui->lineEdit->text() != "")
    {
        emit createNetwork(this->ui->lineEdit->text());
        this->close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Du musst einen Text eingeben!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Fehler!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}
