#include "setvaluewindow.hpp"
#include "ui_setvaluewindow.h"

SetValueWindow::SetValueWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SetValueWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setGeometry((QApplication::primaryScreen()->size().width() - this->size().width()) / 2, (QApplication::primaryScreen()->size().height() - this->size().height()) / 2, this->size().width(), this->size().height());
}

void SetValueWindow::setCurVal(QString p_val)
{
    this->ui->label_2->setText(p_val);
}

SetValueWindow::~SetValueWindow()
{
    delete ui;
}

void SetValueWindow::on_pushButton_clicked()
{
    emit changeValue(this->ui->lineEdit->text().toDouble());
    this->ui->label_2->setText(QString::number(this->ui->lineEdit->text().toDouble()));
    QMessageBox msgBox;
    msgBox.setText("Der Wert wurde erfolgreich geändert");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Information");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void SetValueWindow::on_pushButton_2_clicked()
{
    this->close();
}
