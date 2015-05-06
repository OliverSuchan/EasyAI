#ifndef SETVALUEWINDOW_HPP
#define SETVALUEWINDOW_HPP

#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <QMessageBox>

namespace Ui {
class SetValueWindow;
}

class SetValueWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SetValueWindow(QWidget *parent = 0);
    void setCurVal(QString p_val);
    ~SetValueWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void changeValue(double p_val);

private:
    Ui::SetValueWindow *ui;
};

#endif // SETVALUEWINDOW_HPP
