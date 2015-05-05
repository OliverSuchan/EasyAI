#ifndef CREATENETWORKWINDOW_HPP
#define CREATENETWORKWINDOW_HPP

#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <QRegExp>
#include <QMessageBox>

namespace Ui {
class CreateNetworkWindow;
}

class CreateNetworkWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::CreateNetworkWindow *ui;

public:
    explicit CreateNetworkWindow(QWidget *parent = 0);
    ~CreateNetworkWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

signals:
    void createNetwork(QString p_network);

};

#endif // CREATENETWORKWINDOW_HPP
