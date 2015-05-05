#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <vector>
#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include "feedforwardnetwork.hpp"
#include "connection.hpp"
#include "neuronwidget.hpp"
#include "inputneuron.hpp"
#include "outputneuron.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    std::vector<Connection> m_connections;
    FeedForwardNetwork *m_FNN;
    std::vector<NeuronWidget*> m_neurons;
    Ui::MainWindow *ui;
    void mousePressEvent(QMouseEvent *p_mouseEvent);
    void paintEvent(QPaintEvent *);
    void initConnections();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void execDrag();


};

#endif // MAINWINDOW_HPP
